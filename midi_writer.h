#ifndef MIDIPARSER_WRITER_H
#define MIDIPARSER_WRITER_H

#include <stdio.h>
#include "midi_common.h"

/**
 * write midi file
 * @param path
 * @param midi
 * @return 0->OK, -1->Error
 */
int write_midi(char *path, Midi *midi);

void write_midi_header(FILE *f, MidiHeader *header);

void write_midi_track(FILE *f, MidiTrack *track);

void write_midi_event(FILE *f, TrackEvent *event);

void write_midi_note(FILE *f, NoteEvent *event);

void write_time_signature(FILE *f, TimeSignatureEvent *event);

void write_tempo(FILE *f, TempoEvent *event);

void write_midi_text(FILE *f, TextEvent *event);

void write_midi_end_event(FILE *f);

#endif
