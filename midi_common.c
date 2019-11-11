#include "midi_common.h"
#include <stdlib.h>

void free_midi_text_event(TextEvent *textEvent) {
    free(textEvent->text);
    free(textEvent);
}


void free_midi_time_signature_event(TimeSignatureEvent *timeSignatureEvent) {
    free(timeSignatureEvent->timeSignature);
    free(timeSignatureEvent);
}

void free_midi_note_event(NoteEvent *noteEvent) {
    free(noteEvent->note);
    free(noteEvent);
}

void free_midi_event(TrackEvent *event) {
    TrackEvent *e;
    while (event) {
        e = event->next;
        switch (event->type) {
            case TRACK_EVENT_TYPE_NOTE:
                free_midi_note_event(event->event);
                free(event);
                break;
            case TRACK_EVENT_TYPE_TIME_SIGNATURE:
                free_midi_time_signature_event(event->event);
                free(event);
                break;
            case TRACK_EVENT_TYPE_TEXT:
                free_midi_text_event(event->event);
                free(event);
                break;
            default:
                free(event->event);
                free(event);
                break;
        }
        event = e;
    }
}

void free_midi_header(MidiHeader *header) {
    free(header);
}

void free_midi_track(MidiTrack *track) {
    MidiTrack *t;
    while (track) {
        t = track->next;
        free_midi_event(track->trackEvent);
        free(track);
        track = t;
    }
}

void free_midi(Midi *midi) {
    free_midi_header(midi->header);
    free_midi_track(midi->track);
    free(midi);
}

double get_midi_tempo(Midi *midi) {
    MidiTrack *track = midi->track;
    while (track) {
        if (track->trackEvent->type == TRACK_EVENT_TYPE_SET_TEMPO) {
            TempoEvent *e = track->trackEvent->event;
            return e->tempo;
        }
        track = track->next;
    }
    return 120;
}

uint32 get_midi_track_time(MidiTrack *track) {
    uint32 offset = 0;
    TrackEvent *trackEvent = track->trackEvent;
    while (trackEvent) {
        offset += trackEvent->offset;
        trackEvent = trackEvent->next;
    }
    return offset;
}

double get_division_time(Midi *midi) {
    return (double) midi->header->division * get_midi_tempo(midi) / 60;
}