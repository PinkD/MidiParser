#include <stdio.h>
#include "print_util.h"
#include "log.h"
#include "midi_common.h"

static char buff[1024];

void print_midi_header(MidiHeader *header) {
    sprintf(buff, "{\n\tformat: %d, \n\ttrack: %d, \n\tdivision: %d\n}\n",
            header->format, header->track, header->division);
    log_v(buff);
}

void print_time_signature(TimeSignature *timeSignature) {
    sprintf(buff, "{\n\tbeat: %d/%d, \n\tclock: %d, \n\tnotate: %d\n}\n",
            timeSignature->numerator, timeSignature->denominator, timeSignature->clock, timeSignature->notate);
    log_v(buff);
}

void print_note(Note *note) {
    sprintf(buff, "{\n\toffset: %d, \n\ttype: %d, \n\ttrack: %d\n\tnote: %d\n\tvelocity: %d\n}\n",
            note->offset, note->type, note->track, note->note, note->velocity);
    log_v(buff);
}

void print_track(MidiTrack *track) {
    TrackEvent *event = track->trackEvent;
    while (event) {
        switch (event->type) {
            case TRACK_EVENT_TYPE_TEXT:
                sprintf(buff, "{\n\toffset: %d, \n\ttext: %s, \n\tlen: %d, \n\ttype: %d\n}\n",
                        event->offset, ((TextEvent *) event->event)->text, ((TextEvent *) event->event)->len,
                        ((TextEvent *) event->event)->type);
                log_v(buff);
                break;
            case TRACK_EVENT_TYPE_SET_TEMPO:
                sprintf(buff, "{\n\toffset: %d, \n\ttempo: %.02f\n}\n",
                        event->offset, ((TempoEvent *) event->event)->tempo);
                log_v(buff);
                break;
            case TRACK_EVENT_TYPE_TIME_SIGNATURE:
                print_time_signature(((TimeSignatureEvent *) event->event)->timeSignature);
                break;
            case TRACK_EVENT_TYPE_NOTE:
                print_note(((NoteEvent *) event->event)->note);
                break;
            case TRACK_EVENT_TYPE_END:
                sprintf(buff, "{\n\ttrack end\n}\n");
                log_v(buff);
                break;
            default:
                printf("Bad type, skipped\n");
                event = event->next;
                continue;
        }
        event = event->next;
    }
}

void print_midi(Midi *midi) {
    print_midi_header(midi->header);
    MidiTrack *track = midi->track;
    while (track) {
        print_track(track);
        track = track->next;
        return;
    }
}