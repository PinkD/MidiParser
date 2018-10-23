#ifndef MIDIPARSER_LIBRARY_H
#define MIDIPARSER_LIBRARY_H

#include "bit_util.h"
#include "midi_common.h"

Midi *read_midi_file(char *file);

/**
 * read Midi header from f
 * @param len header data len
 * @param f file ptr
 * @return MidiHeader *, need to be free
 */
MidiHeader *read_header(uint32 len, FILE *f);

MidiTrack *read_track(uint32 len, FILE *f);

TrackEvent *read_event(FILE *f);

float read_tempo(FILE *f);

/**
 * read time signature
 * @param f file ptr
 * @return struct, need to be free
 */
TimeSignature *read_time_signature(FILE *f);

Note *read_note(FILE *f, NOTE_TYPE type, byte track, uint32 offset);


#endif