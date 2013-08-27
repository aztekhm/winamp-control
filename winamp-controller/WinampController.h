#pragma once
#ifndef WINAMPCONTROLLER_H
#define WINAMPCONTROLLER_H

#include <string>
#include <windows.h>

#define STOP_CURRENT_TRACK 1
#define FADEOUT_AND_STOP 2
#define STOP_AFTER_CURRENT_TRACK 3

#define AUDIO_SAMPLERATE 1
#define AUDIO_BITRATE 2
#define AUDIO_CHANNELS 3

#define PLAYBACK_POSITION 1
#define TRACK_LENGTH 2

class WinampController {
	protected:
		HWND _winampWindow;
		std::string _winampPath;
		int _volumeBeforeMute;
		unsigned long readWinampToLocal(HWND hwndWinamp, void *remoteBuf, void *localBuf, unsigned long bufsize);
	public:
		WinampController();
		~WinampController();
		void setWinampWindow(HWND winampWindow);
		HWND getWinampWindow();
		void setWinampPath(std::string winampPath);
		std::string getWinampPath();
		void handleWinampWindow();
		
		bool isWinampRunning();	//1
		void previousTrack();	//2
		void nextTrack();		//3
		void playTrack();		//4
		void playTrack(int track);
		void pauseTrack();		//5
		void stopPlayback(int mode);	//6
		void togglePlayPause();	//7
		///-------------------- 8 ---------------------///
		void forwardFiveSeconds();		//9
		void rewindFiveSeconds();		//10
		void gotoStartOfPlaylist();		//11
		void gotoEndOfPlaylist();		//12
		int raiseVolumeOnePercent();	//13
		int lowerVolumeOnePercent();	//14
		void toggleRepeat();	//15
		void toggleShuffle();	//16
		void closeWinamp();		//17
		void rewindTenTracksInPlaylist();	//18
		void playAudioCD();		//19
		void loadDefaultPreset();	//20
		int getWinampVersion();		//21
		void startPlayback();		//22
		void clearPlaylist();		//23
		void playSelectedTrack();	//24
		int getPlaybackStatus();	//25
		void getCurrentTrackInfo(int& currentPlaybackPosition, int& currentTrackLength);	//26
		int getCurrentTrackInfo(int wichInfo);
		///------------------------------- 27 ----------------------------///
		void seekCurrentTrack(int position);	//28
		void setPlaylistPosition(int position);	//29
		void setVolume(int volume);	//30
		int getVolume();		//31
		void toggleMute();		//32
		void setPanning(int panning);	//33
		int getTracksInPlaylist();		//34
		int getCurrentTrackInPlaylist();	//35
		void getCurrentAudioInfo(int& sampleRate, int& bitRate, int& channels);		//36
		int getCurrentAudioInfo(int wichInfo);
		///-------------------- 37,38 ---------------------///
		void getElementEqualizer(int* elems);		//39
		int getElementEqualizer(int element);
		///-------------------- 40 ---------------------///
		
		bool isEqualizerEnabled();		//41
		//bool isAutoloadEnabled();		//42		//Hace cualquier otra cosa menos lo que debe, o no supe como usarlo D: (lo mas seguro)
		void setElementEqualizer(int element, int value);	//43
		void restartWinamp();		//44
		bool isShuffleOptionSet();	//45
		bool isRepeatOptionSet();	//46
		void setShuffleOption(int mode);	//47
		void setRepeatOption(int mode);		//48
		std::string getPlayingFilename();	//49
		std::string getPlaylistEntry(int track);	//55
		void addToPlaylist(std::string file);		//56
		void play(std::string media);		//57
		void openWinamp();	//59
		std::string getPlayingTitle();	//60
		std::string getPlayingTitle(int track);
		// metadata=[title,artist,albumartist,album,genre,year,disc,publisher,comment,track,composer,conductor]
		int getExtendedFileInfo(std::string file, std::string metadata, char* dest, int len); //61
		
};
#endif
