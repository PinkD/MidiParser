#ifndef MIDIPARSER_COMMON_H
#define MIDIPARSER_COMMON_H

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
    TEXT_EVENT_TYPE_TEXT = 0x01,
    TEXT_EVENT_TYPE_COPYRIGHT = 0x02,
    TEXT_EVENT_TYPE_TRACK_NAME = 0x03,
    TEXT_EVENT_TYPE_INSTRUMENT_NAME = 0x04,
    TEXT_EVENT_TYPE_LYRIC = 0x05,
    TEXT_EVENT_TYPE_MAKER = 0x06,
    TEXT_EVENT_TYPE_CUE_POINT = 0x07,
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
    uint32 offset;
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

//NOTE: if you call free_xxx, all it's children with be free too

/**
 * free midi and it's children
 * @param midi
 */
void free_midi(Midi *midi);

/**
 * free midi track and it's children
 * @param track
 */
void free_track(MidiTrack *track);

/**
 * free header
 * @param header
 */
void free_header(MidiHeader *header);

/**
 * free event and it's children
 * @param event
 */
void free_event(TrackEvent *event);

/**
 * free note event and it's children
 * @param noteEvent
 */
void free_note_event(NoteEvent *noteEvent);

/**
 * free time signature event and it's children
 * @param timeSignatureEvent
 */
void free_time_signature_event(TimeSignatureEvent *timeSignatureEvent);

/**
 * free text event and text in it
 * @param textEvent
 */
void free_text_event(TextEvent *textEvent);

#endif
