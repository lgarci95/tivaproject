/*
* notes.h
*/

#ifndef NOTES_H
#define NOTES_H

#include <stdint.h>
#include "midi.h"

#define MAX_TRACKS 4
#define MAX_FILE_SIZE 65535
#define MAX_ALBUM_SIZE 0x38000 // 224 kiB
#define FILE_SIGNATURE 0xABBA
#define ALBUM_SIGNATURE 0xACDC

// min and max notes available on PWM
#define MIN_NOTE MIDI_DS1
#define MAX_NOTE MIDI_B8

typedef struct{
    uint16_t signature;
    char name[22];
    uint16_t numTracks;
    uint16_t duration; // seconds
    uint32_t size;
}FileHeader_t;

typedef struct{
    uint16_t signature;
    uint16_t numSongs;
}AlbumHeader_t;

typedef struct{
    AlbumHeader_t* header;
    uint32_t* songOffset; 
}Album_t;

typedef struct{
    uint16_t id;
    uint16_t offset;
    uint16_t eventCount;
}TrackeHeader_t;

typedef struct{
    int16_t deltaTime;
    uint8_t status;
    uint8_t key;
    uint8_t velocity;
    uint8_t reserved;
}NoteEvent_t;

typedef struct{
    NoteEvent_t* notes;
} Track_t;

typedef struct{
    FileHeader_t* header;
    Track_t tracks[MAX_TRACKS];
}Song_t;

extern const uint16_t NotePwmPeriods[];


#endif