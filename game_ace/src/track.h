#pragma once

typedef enum tTrack {
	TRACK_MENU = 2,
	TRACK_TXT = 3,
	TRACK_DEFEAT = 4,
	TRACK_VICTORY = 5,
} tTrack;

void PlayTrack(tTrack eTrack);
