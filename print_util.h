#ifndef MIDIPARSER_PRINT_UTIL_H
#define MIDIPARSER_PRINT_UTIL_H


#include "midi_common.h"

void print_midi_header(MidiHeader *header);

void print_time_signature(TimeSignature *timeSignature);

void print_note(Note *note);

void print_track(MidiTrack *track);

void print_midi(Midi *midi);
#endif
