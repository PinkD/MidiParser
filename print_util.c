#include <stdio.h>
#include "print_util.h"
#include "log.h"

void print_midi_header(MidiHeader *header) {
    char buff[1024];
    sprintf(buff, "{\n\tformat: %d, \n\ttrack: %d, \n\tdivision: %d\n}\n",
            header->format, header->track, header->division);
    log_d(buff);
}

void print_time_signature(TimeSignature *timeSignature) {
    char buff[1024];
    sprintf(buff, "{\n\tbeat: %d/%d, \n\tclock: %d, \n\tnotate: %d\n}\n",
            timeSignature->numerator, timeSignature->denominator, timeSignature->clock, timeSignature->notate);
}

void print_note(Note *note) {
    char buff[1024];
    sprintf(buff, "{\n\toffset: %d, \n\ttype: %d, \n\ttrack: %d\n\tnote: %d\n\tvelocity: %d\n}\n",
            note->offset, note->type, note->track, note->note, note->velocity);
}

void print_track(MidiTrack *track) {

}
