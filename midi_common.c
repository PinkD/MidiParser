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
