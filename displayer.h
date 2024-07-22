#ifndef DISPLAYER_H
#define DISPLAYER_H

#include "drivers/lcd.h"
#include "notes.h"

int Diplay_Init(const LCDPinConfig_t* lcdConfig);
void Display_ShowSongScreen(const Song_t* song, int songNumber, int songCount);
void Display_ShowDownloadingScree(int percentage);
void Display_ShowFileNotLoadedScreen(void);
void Display_ShowPlayDuration(int playDuration, int songDuration);


#endif