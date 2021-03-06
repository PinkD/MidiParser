#include "midi_writer.h"
#include "common_util.h"
#include "log.h"
#include <math.h>

int write_midi(char *path, Midi *midi) {
    FILE *f = fopen(path, "wb");
    if (!f) {
        log_e("Can not open file");
        return -1;
    }
    log_v("Writing file...");
    fwrite(TYPE_MIDI_HEADER, 4, 1, f);
    log_v("Writing header...");
    write_midi_header(f, midi->header);

    MidiTrack *track = midi->track;

    while (track) {
        log_v("Writing track...");
        fwrite(TYPE_MIDI_TRACK, 4, 1, f);
        write_midi_track(f, track);
        track = track->next;
    }
    log_v("Writing file successful");
    fclose(f);
    return 0;
}


void write_midi_header(FILE *f, MidiHeader *header) {
    write_uint32(f, header->length);
    write_uint16(f, header->format);
    write_uint16(f, header->track);
    write_uint16(f, header->division);
}

void write_midi_track(FILE *f, MidiTrack *track) {
    TrackEvent *event = track->trackEvent;
    write_uint32(f, track->length);
    while (event) {
        write_midi_event(f, event);
        event = event->next;
    }
    TrackEvent endEvent;
    endEvent.type = TRACK_EVENT_TYPE_END;
    endEvent.offset = 0;
    write_midi_event(f, &endEvent);
}

void write_midi_event(FILE *f, TrackEvent *event) {
    write_vlq(f, event->offset);
    switch (event->type) {
        case TRACK_EVENT_TYPE_NOTE:
            write_midi_note(f, event->event);
            break;
        case TRACK_EVENT_TYPE_TIME_SIGNATURE:
            write_time_signature(f, event->event);
            break;
        case TRACK_EVENT_TYPE_SET_TEMPO:
            write_tempo(f, event->event);
            break;
        case TRACK_EVENT_TYPE_TEXT:
            write_midi_text(f, event->event);
            break;
        case TRACK_EVENT_TYPE_END://construct it when there is no more event
            write_midi_end_event(f);
        default://can't parse, ignore
            break;
    }
}

void write_midi_end_event(FILE *f) {
    write_byte(f, 0xff);
    write_byte(f, 0x2f);
    write_byte(f, 0x00);
}

void write_tempo(FILE *f, TempoEvent *event) {
    float tempo = event->tempo;
    uint32 t = (uint32) (60e6 / tempo);
    byte tmp[3];

    tmp[0] = (byte) ((t & 0x00ff0000) >> 16);
    tmp[1] = (byte) ((t & 0x0000ff00) >> 8);
    tmp[2] = (byte) (t & 0x000000ff);

    write_byte(f, 0xff);
    write_byte(f, 0x51);
    write_byte(f, 0x03);

    fwrite(tmp, 3, 1, f);
}

void write_time_signature(FILE *f, TimeSignatureEvent *event) {
    TimeSignature *timeSignature = event->timeSignature;

    write_byte(f, 0xff);
    write_byte(f, 0x58);
    write_byte(f, 0x04);

    write_byte(f, timeSignature->numerator);
    write_byte(f, (byte) sqrt(timeSignature->denominator));
    write_byte(f, timeSignature->clock);
    write_byte(f, timeSignature->notate);
}

void write_midi_note(FILE *f, NoteEvent *event) {
    Note *note = event->note;
    byte t;
    if (note->type == NOTE_START) {
        t = (byte) (0x90 | note->track);
    } else {
        t = (byte) (0x80 | note->track);
    }
    write_byte(f, t);
    write_byte(f, note->note);
    write_byte(f, note->velocity);
}

void write_midi_text(FILE *f, TextEvent *event) {
    write_byte(f, 0xff);
    write_byte(f, event->type);
    write_vlq(f, event->len - 1);//Midi file needs no str end
    fwrite(event->text, event->len - 1, 1, f);
}
