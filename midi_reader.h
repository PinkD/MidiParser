#ifndef MIDIPARSER_READER_H
#define MIDIPARSER_READER_H

#include "midi_common.h"

//NOTE: if you call free_xxx, all it's children with be free too

/**
 * read hole midi file
 * @param file file path
 * @return midi, free with free_midi
 */
Midi *read_midi_file(char *file);

/**
 * read Midi header from f
 * @param len header data len
 * @param f file ptr
 * @return MidiHeader *, need to be free
 */
MidiHeader *read_midi_header(uint32 len, FILE *f);

/**
 * @param len track len
 * @param f file ptr
 * @return remember to free with free_header
 */
MidiTrack *read_midi_track(uint32 len, FILE *f);

/**
 * read event
 * @param f file ptr
 * @return remember to free with free_event
 */
TrackEvent *read_midi_event(FILE *f);

/**
 * read tempo
 * @param f file ptr
 * @return tempo in float
 */
float read_tempo(FILE *f);

/**
 * read time signature
 * @param f file ptr
 * @return remember to free with free_time_signature
 */
TimeSignature *read_time_signature(FILE *f);

/**
 * read note
 * @param f file ptr
 * @param type note type see `NOTE_TYPE`
 * @param track note track between 0-f
 * @param offset time unit offset
 * @return remember to free with free_note
 */
Note *read_midi_note(FILE *f, NOTE_TYPE type, byte track, uint32 offset);

#endif