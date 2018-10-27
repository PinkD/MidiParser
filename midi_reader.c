#include <malloc.h>
#include <math.h>
#include <memory.h>

#include "midi_reader.h"
#include "log.h"
#include "common_util.h"
#include "print_util.h"


Midi *read_midi_file(char *file) {
    FILE *f = fopen(file, "rb");
    if (!f) {
        log_e("Can not open file");
        return NULL;
    }
    log_v("Reading file...");
    const static int BUFFER_SIZE = 1024;
    byte buffer[BUFFER_SIZE];
    memset(buffer, 0x00, BUFFER_SIZE);
    uint32 len;
    Midi *midi = calloc(sizeof(Midi), 1);
    while (fread(buffer, sizeof(char) * 4, 1, f)) {
        fread(&len, sizeof(uint32), 1, f);
        len = swap_bit_32(len);
        if (strcmp(TYPE_MIDI_HEADER, (const char *) buffer) == 0) {//header
            log_v("Reading header...");
            midi->header = read_midi_header(len, f);
            log_d("Header:");
            print_midi_header(midi->header);
        } else if (strcmp(TYPE_MIDI_TRACK, (const char *) buffer) == 0) {//track
            log_v("Reading track...");
            log_d("Track, len is:");
            log_d(int_to_str(len));
            MidiTrack *track = read_midi_track(len, f);
            if (track != NULL) {
                MidiTrack *t = midi->track;
                if (t) {
                    while (t->next) {
                        t = t->next;
                    }
                    t->next = track;//track.next was inited as `NULL` in `read_track`
                } else {
                    midi->track = track;
                    continue;
                }
            }
        } else {
            log_e("Bad file format\n");
            fclose(f);
            return NULL;
        }
    }
    fclose(f);
    log_v("Read file successful");
    return midi;
}

MidiHeader *read_midi_header(uint32 len, FILE *f) {
    uint16 tmp;
    MidiHeader *header = malloc(sizeof(MidiHeader));

    header->length = len;

    fread(&tmp, sizeof(uint16), 1, f);
    header->format = (Format) (swap_bit_16(tmp));

    fread(&tmp, sizeof(uint16), 1, f);
    header->track = swap_bit_16(tmp);

    fread(&tmp, sizeof(uint16), 1, f);
    header->division = swap_bit_16(tmp);

    return header;
}

MidiTrack *read_midi_track(uint32 len, FILE *f) {
    MidiTrack *track = malloc(sizeof(MidiTrack));
    track->length = len;
    track->trackEvent = NULL;
    track->next = NULL;
    TrackEvent *event;
    for (event = read_midi_event(f); event == NULL || event->type != TRACK_EVENT_TYPE_END; event = read_midi_event(f)) {
        if (!event) {//NULL, unsupported event
            continue;
        }
        if (track->trackEvent) {
            TrackEvent *e = track->trackEvent;
            while (e->next) {
                e = e->next;
            }
            e->next = event;
        } else {
            track->trackEvent = event;
        }
    }
    return track;
}


TrackEvent *read_midi_event(FILE *f) {
    uint32 len;
    char *text;

    TrackEvent *trackEvent = malloc(sizeof(TrackEvent));
    trackEvent->offset = read_vlq(f);
    byte tag = read_byte(f);


    if (tag == 0xff) {
        byte next = read_byte(f);
        TextEvent *textEvent = malloc(sizeof(TextEvent));

        switch (next) {
            case 0x00:
                if (read_byte(f) == 0x02) {//sequence number
                    log_v("sequence number is not implement yet");
                } else {
                    log_w("bad event after 0xff 0x00");
                }
                break;
            case 0x01://text event
                len = read_vlq(f);
                text = malloc(sizeof(char) * (len + 1));
                fread(text, len, 1, f);
                text[len] = 0;
                textEvent->type = TEXT_EVENT_TYPE_TEXT;
                textEvent->len = len + 1;
                textEvent->text = text;
                trackEvent->type = TRACK_EVENT_TYPE_TEXT;
                trackEvent->event = textEvent;
                trackEvent->next = NULL;

                log_d("text event, len is:");
                log_d(int_to_str(len));
                log_d("text is:");
                log_d(text);
                return trackEvent;
            case 0x02://copyright notice
                len = read_vlq(f);
                text = malloc(sizeof(char) * (len + 1));
                fread(text, len, 1, f);
                text[len] = 0;
                textEvent->type = TEXT_EVENT_TYPE_COPYRIGHT;
                textEvent->len = len + 1;
                textEvent->text = text;
                trackEvent->type = TRACK_EVENT_TYPE_TEXT;
                trackEvent->event = textEvent;
                trackEvent->next = NULL;

                log_d("copyright notice, len is:");
                log_d(int_to_str(len));
                log_d("text is:");
                log_d(text);
                return trackEvent;
            case 0x03://sequence/track name
                len = read_vlq(f);
                text = malloc(sizeof(char) * (len + 1));
                fread(text, len, 1, f);
                text[len] = 0;
                textEvent->type = TEXT_EVENT_TYPE_TRACK_NAME;
                textEvent->len = len + 1;
                textEvent->text = text;
                trackEvent->type = TRACK_EVENT_TYPE_TEXT;
                trackEvent->event = textEvent;
                trackEvent->next = NULL;

                log_d("track name, len is:");
                log_d(int_to_str(len));
                log_d("text is:");
                log_d(text);
                return trackEvent;
            case 0x04://instrument name
                len = read_vlq(f);
                text = malloc(sizeof(char) * (len + 1));
                fread(text, len, 1, f);
                text[len] = 0;
                textEvent->type = TEXT_EVENT_TYPE_INSTRUMENT_NAME;
                textEvent->len = len + 1;
                textEvent->text = text;
                trackEvent->type = TRACK_EVENT_TYPE_TEXT;
                trackEvent->event = textEvent;
                trackEvent->next = NULL;

                log_d("instrument name, len is:");
                log_d(int_to_str(len));
                log_d("text is:");
                log_d(text);
                return trackEvent;
            case 0x05://lyric
                len = read_vlq(f);
                text = malloc(sizeof(char) * (len + 1));
                fread(text, len, 1, f);
                text[len] = 0;
                textEvent->type = TEXT_EVENT_TYPE_LYRIC;
                textEvent->len = len + 1;
                textEvent->text = text;
                trackEvent->type = TRACK_EVENT_TYPE_TEXT;
                trackEvent->event = textEvent;
                trackEvent->next = NULL;

                log_d("lyric, len is:");
                log_d(int_to_str(len));
                log_d("text is:");
                log_d(text);
                return trackEvent;
            case 0x06://maker
                len = read_vlq(f);
                text = malloc(sizeof(char) * (len + 1));
                fread(text, len, 1, f);
                text[len] = 0;
                textEvent->type = TEXT_EVENT_TYPE_MAKER;
                textEvent->len = len + 1;
                textEvent->text = text;
                trackEvent->type = TRACK_EVENT_TYPE_TEXT;
                trackEvent->event = textEvent;
                trackEvent->next = NULL;

                log_d("maker, len is:");
                log_d(int_to_str(len));
                log_d("text is:");
                log_d(text);
                return trackEvent;
            case 0x07://cue point
                len = read_vlq(f);
                text = malloc(sizeof(char) * (len + 1));
                fread(text, len, 1, f);
                text[len] = 0;
                textEvent->type = TEXT_EVENT_TYPE_CUE_POINT;
                textEvent->len = len + 1;
                textEvent->text = text;
                trackEvent->type = TRACK_EVENT_TYPE_TEXT;
                trackEvent->event = textEvent;
                trackEvent->next = NULL;

                log_d("cue point, len is:");
                log_d(int_to_str(len));
                log_d("text is:");
                log_d(text);
                return trackEvent;
            case 0x2f:
                if (read_byte(f) == 0x00) {//end of track
                    trackEvent->type = TRACK_EVENT_TYPE_END;
                    trackEvent->event = trackEvent->next = NULL;
                    log_d("end of track");
                    return trackEvent;
                } else {//unknown
                    log_w("unknown event after 0xff 0x2f");
                }
                break;
            case 0x51:
                if (read_byte(f) == 0x03) {//set tempo
                    TempoEvent *tempoEvent = malloc(sizeof(TempoEvent));
                    tempoEvent->tempo = read_tempo(f);
                    trackEvent->type = TRACK_EVENT_TYPE_SET_TEMPO;
                    trackEvent->event = tempoEvent;
                    trackEvent->next = NULL;
                    log_d("set tempo");
                    log_d(float_to_str(tempoEvent->tempo));
                    return trackEvent;
                } else {//unknown
                    log_w("unknown event after 0xff 0x51");
                }
                break;
            case 0x54:
                if (read_byte(f) == 0x05) {//SMPTE offset
                    log_d("SMPTE Offset");
                } else {//unknown
                    log_w("unknown event after 0xff 0x54");
                }
                break;
            case 0x58:
                if (read_byte(f) == 0x04) {//time signature
                    TimeSignatureEvent *timeSignatureEvent = malloc(sizeof(TimeSignatureEvent));
                    timeSignatureEvent->timeSignature = read_time_signature(f);
                    print_time_signature(timeSignatureEvent->timeSignature);
                    trackEvent->type = TRACK_EVENT_TYPE_TIME_SIGNATURE;
                    trackEvent->event = timeSignatureEvent;
                    trackEvent->next = NULL;
                    log_d("time signature");
                    return trackEvent;
                } else {//unknown
                    log_w("unknown event after 0xff 0x58");
                }
                break;
            case 0x59:
                if (read_byte(f) == 0x02) {//key signature
                    log_d("key signature");
                } else {//unknown
                    log_w("unknown event after 0xff 0x58");
                }
                break;
            default:
                break;
        }
        //handle_meta_event
    } else if (tag >= 0x80 && tag <= 0x8f) {//event note off
        log_d("event note end");
        NoteEvent *noteEvent = malloc(sizeof(NoteEvent));
        noteEvent->note = read_midi_note(f, NOTE_END, tag & (byte) 0x0f, trackEvent->offset);
//        print_note(noteEvent->note);
        trackEvent->type = TRACK_EVENT_TYPE_NOTE;
        trackEvent->event = noteEvent;
        trackEvent->next = NULL;
        return trackEvent;
    } else if (tag >= 0x90 && tag <= 0x9f) {//event note on
        log_d("event note start");

        NoteEvent *noteEvent = malloc(sizeof(NoteEvent));
        noteEvent->note = read_midi_note(f, NOTE_START, tag & (byte) 0x0f, trackEvent->offset);
//        print_note(noteEvent->note);

        trackEvent->type = TRACK_EVENT_TYPE_NOTE;
        trackEvent->event = noteEvent;
        trackEvent->next = NULL;
        return trackEvent;
    } else if (tag >= 0xa0 && tag <= 0xaf) {//polyphonic key pressure

    } else if (tag >= 0xb0 && tag <= 0xbf) {//control message
    } else if (tag >= 0xc0 && tag <= 0xcf) {//program change
    } else if (tag >= 0xd0 && tag <= 0xdf) {//channel pressure(after touch)
    } else if (tag >= 0xe0 && tag <= 0xef) {//pitch wheel change
    } else if (tag >= 0xf0 && tag <= 0xff) {//system message
        switch (tag) {
            //-------------system common message-------------
            case 0xf0://system exclusive
                break;
            case 0xf2://song position pointer
                break;
            case 0xf3://song select
                break;
            case 0xf6://true request
                break;
            case 0xf7://end of exclusive
                break;
                //-------------system real-time message-------------
            case 0xf8://time clock
                break;
            case 0xfa://start player sequence
                break;
            case 0xfb://continue playing
                break;
            case 0xfc://stop playing
                break;
            case 0xfd://active sensing
                break;
//            case 0xff://reset all receiver, ignore because of being used in meta-event escape
//                break;
            default:
                //undefined
                break;

        }

    }
    free(trackEvent);
    return NULL;
}


TimeSignature *read_time_signature(FILE *f) {
    TimeSignature *timeSignature = malloc(sizeof(TimeSignature));
    timeSignature->numerator = read_byte(f);
    timeSignature->denominator = (byte) pow(2, read_byte(f));
    timeSignature->clock = read_byte(f);
    timeSignature->notate = read_byte(f);
    return timeSignature;
}

float read_tempo(FILE *f) {
    byte tmp[3];
    fread(tmp, 3, 1, f);
    return (60.0f * 1000000 / (tmp[0] << 16 | tmp[1] << 8 | tmp[2]));
}

Note *read_midi_note(FILE *f, NOTE_TYPE type, byte track, uint32 offset) {
    Note *note = malloc(sizeof(Note));
    note->offset = offset;
    note->type = type;
    note->track = track;
    note->note = read_byte(f);
    note->velocity = read_byte(f);
    return note;
}

