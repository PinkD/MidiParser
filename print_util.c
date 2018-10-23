#include <stdio.h>
#include "print_util.h"

void print_midi_header(MidiHeader *header) {
    printf("{\n\tformat: %d, \n\ttrack: %d, \n\tdivision: %d\n}\n",
           header->format, header->track, header->division);
}

void print_time_signature(TimeSignature *timeSignature) {
    printf("{\n\tbeat: %d/%d, \n\tclock: %d, \n\tnotate: %d\n}\n",
           timeSignature->numerator, timeSignature->denominator, timeSignature->clock, timeSignature->notate);
}

void print_note(Note *note) {
    printf("{\n\toffset: %d, \n\ttype: %d, \n\ttrack: %d\n\tnote: %d\n\tvelocity: %d\n}\n",
           note->offset, note->type, note->track, note->note, note->velocity);
}

void print_track(MidiTrack *track) {

}
