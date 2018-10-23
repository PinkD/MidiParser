#ifndef MIDIPARSER_MIDI_STRUCT_H
#define MIDIPARSER_MIDI_STRUCT_H

#include "base_def.h"

static char *TYPE_MIDI_HEADER = "MThd";
static char *TYPE_MIDI_TRACK = "MTrk";

typedef enum {
    SINGLE_TRACK = 0,
    SIMULTANEOUS_TRACK = 1,
    INDEPENDENT_TRACK = 2
} Format;

typedef enum {
    NOTE_START,
    NOTE_END
} NOTE_TYPE;

typedef enum {
    TRACK_EVENT_TYPE_TIME_SIGNATURE,
    TRACK_EVENT_TYPE_NOTE,
    TRACK_EVENT_TYPE_SET_TEMPO,
    TRACK_EVENT_TYPE_TEXT,
    TRACK_EVENT_TYPE_END,
} TRACK_EVENT_TYPE;

typedef enum {
    TEXT_EVENT_TYPE_TEXT,
    TEXT_EVENT_TYPE_COPYRIGHT,
    TEXT_EVENT_TYPE_TRACK_NAME,
    TEXT_EVENT_TYPE_INSTRUMENT_NAME,
    TEXT_EVENT_TYPE_LYRIC,
    TEXT_EVENT_TYPE_MAKER,
    TEXT_EVENT_TYPE_CUE_POINT,
} TEXT_EVENT_TYPE;

typedef struct {
    byte numerator;
    byte denominator;
    byte clock;
    byte notate;
} TimeSignature;

typedef struct {
    NOTE_TYPE type;
    byte track;
    uint32 offset;
    byte note;
    byte velocity;
} Note;

typedef struct {
    TEXT_EVENT_TYPE type;
    uint32 len;
    char *text;
} TextEvent;

typedef struct {
    TimeSignature *timeSignature;
} TimeSignatureEvent;

typedef struct {
    Note *note;
} NoteEvent;

typedef struct {
    float tempo;
} TempoEvent;

typedef struct {
    uint32 length;
    Format format;
    uint16 track;
    uint16 division;
} MidiHeader;

typedef struct _TrackEvent {
    TRACK_EVENT_TYPE type;
    void *event;
    struct _TrackEvent *next;
} TrackEvent;

typedef struct _MidiTrack {
    uint32 length;
    TrackEvent *trackEvent;
    struct _MidiTrack *next;
} MidiTrack;

typedef struct {
    MidiHeader *header;
    MidiTrack *track;
} Midi;

void free_midi(Midi *midi);

void free_track(MidiTrack *track);

void free_header(MidiHeader *header);

void free_event(TrackEvent *event);

void free_note_event(NoteEvent *noteEvent);

void free_time_signature_event(TimeSignatureEvent *timeSignatureEvent);

void free_text_event(TextEvent *textEvent);

#endif
