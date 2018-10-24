#ifndef MIDIPARSER_MIDI_WRITER_H
#define MIDIPARSER_MIDI_WRITER_H

#include <stdio.h>
#include "midi_common.h"

void write_midi(char *path, Midi *midi);

void write_header(FILE *f, MidiHeader *header);

void write_track(FILE *f, MidiTrack *track);

void write_event(FILE *f, TrackEvent *event);

void write_note(FILE *f, Note *note);

void write_time_signature(FILE *f, TimeSignatureEvent *event);

void write_tempo(FILE *f, TempoEvent *event);

void write_text(FILE *f, TextEvent *event);

void write_end(FILE *f);

#endif
