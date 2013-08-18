#pragma once
#include "WinampController.h"
#include "message_codes.h"
#include "controller_threads.h"
#include "util.h"
//#include <fileref.h>
//#include <tag.h>
#include <stdio.h>

WinampController::WinampController() {
	_winampWindow = FindWindow(TEXT("Winamp v1.x"), NULL);
	_volumeBeforeMute = 0;
	//Finding winamp path
	HKEY hKey;
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Clients\\Media\\Winamp\\shell\\open\\command", 0, KEY_READ, &hKey) == ERROR_SUCCESS){
		char keyValue[512];
		DWORD size = sizeof(keyValue);
		RegQueryValueEx(hKey, NULL, NULL, NULL, (LPBYTE)keyValue, &size);
		RegCloseKey(hKey);
		_winampPath = keyValue;
	}
}

WinampController::~WinampController() {
}

unsigned long WinampController::readWinampToLocal(HWND hwndWinamp, void *remoteBuf, void *localBuf, unsigned long bufsize) {
	int isError;
	HANDLE hWinamp;
	unsigned long dWinamp;

	// find the process id
	GetWindowThreadProcessId(hwndWinamp, &dWinamp);

	// open the process object
	hWinamp = OpenProcess(PROCESS_ALL_ACCESS, false, dWinamp);
	if (hWinamp == NULL) {
		//std::cout << "winamp handle = null" << std::endl;
		return 0;
	}

	unsigned long readedBytes;
	isError = ReadProcessMemory(hWinamp, remoteBuf, localBuf, bufsize, &readedBytes);
	//std::cout << "readedBytes:" << readedBytes << std::endl;
	CloseHandle(hWinamp);
	
	return !isError ? 0 : bufsize;
}


void WinampController::setWinampWindow(HWND winampWindow) {
	_winampWindow = winampWindow;
}

HWND WinampController::getWinampWindow() {
	return _winampWindow;
}

void WinampController::setWinampPath(std::string winampPath) {
	_winampPath = winampPath;
}

std::string WinampController::getWinampPath() {
	return _winampPath;
}

void WinampController::handleWinampWindow() {
	_winampWindow = FindWindow(TEXT("Winamp v1.x"), NULL);
}

bool WinampController::isWinampRunning() {
	return FindWindow(TEXT("Winamp v1.x"), NULL) != NULL;
}

void WinampController::previousTrack() {
	SendMessage(_winampWindow, WM_COMMAND, MSG_PREVIOUS, 0);
}

void WinampController::nextTrack() {
	SendMessage(_winampWindow, WM_COMMAND, MSG_NEXT, 0);
}

void WinampController::playTrack() {
	SendMessage(_winampWindow, WM_COMMAND, MSG_PLAY, 0);
}

void WinampController::playTrack(int track) {
	if (track >= 0 && track < getTracksInPlaylist()) {
		setPlaylistPosition(track);
		playTrack();
	}
}

void WinampController::pauseTrack() {
	SendMessage(_winampWindow, WM_COMMAND, MSG_PAUSE, 0);
}

void WinampController::stopPlayback(int mode) {
	if (mode == FADEOUT_AND_STOP)
		SendMessage(_winampWindow, WM_COMMAND, MSG_FADEOUT_AND_STOP, 0);
	else if (mode == STOP_AFTER_CURRENT_TRACK)
		SendMessage(_winampWindow, WM_COMMAND, MSG_STOP_AFTER_CURRENT_TRACK, 0);
	else if (mode == STOP_CURRENT_TRACK)
		SendMessage(_winampWindow, WM_COMMAND, MSG_STOP, 0);
}

void WinampController::togglePlayPause() {
	int playbackStatus = getPlaybackStatus();
	if (playbackStatus == 1) {
		pauseTrack();
	} else if (playbackStatus == 3) {
		playTrack();
	}
}

void WinampController::forwardFiveSeconds() {
	SendMessage(_winampWindow, WM_COMMAND, MSG_FORWARD_5_SECONDS, 0);
}

void WinampController::rewindFiveSeconds() {
	SendMessage(_winampWindow, WM_COMMAND, MSG_REWIND_5_SECONDS, 0);
}

void WinampController::gotoStartOfPlaylist() {
	SendMessage(_winampWindow, WM_COMMAND, MSG_START_OF_PLAYLIST, 0);
}

void WinampController::gotoEndOfPlaylist() {
	SendMessage(_winampWindow, WM_COMMAND, MSG_END_OF_PLAYLIST, 0);
}

int WinampController::raiseVolumeOnePercent() {
	SendMessage(_winampWindow, WM_COMMAND, MSG_RAISE_VOLUME_1_PERCENT, 0);
	return getVolume();
}

int WinampController::lowerVolumeOnePercent() {
	SendMessage(_winampWindow, WM_COMMAND, MSG_LOWER_VOLUME_1_PERCENT, 0);
	return getVolume();
}

void WinampController::toggleRepeat() {
	SendMessage(_winampWindow, WM_COMMAND, MSG_TOGGLE_REPEAT, 0);
}

void WinampController::toggleShuffle() {
	SendMessage(_winampWindow, WM_COMMAND, MSG_TOGGLE_SHUFFLE, 0);
}

void WinampController::closeWinamp() {
	SendMessage(_winampWindow, WM_COMMAND, MSG_CLOSE_WINAMP, 0);
}

void WinampController::rewindTenTracksInPlaylist() {
	SendMessage(_winampWindow, WM_COMMAND, MSG_BACK_TEN_TRACKS, 0);
}

void WinampController::playAudioCD() {
	SendMessage(_winampWindow, WM_COMMAND, MSG_PLAY_AUDIO_CD, 0);
}

void WinampController::loadDefaultPreset() {
	SendMessage(_winampWindow, WM_COMMAND, MSG_LOAD_DEFAULT_PRESET, 0);
}

int WinampController::getWinampVersion() {
	return SendMessage(_winampWindow, WM_USER, 0, MSG_WINAMP_VERSION);
}

void WinampController::startPlayback() {
	SendMessage(_winampWindow, WM_USER, 0, MSG_START_PLAYBACK);
}

void WinampController::clearPlaylist() {
	SendMessage(_winampWindow, WM_USER, 0, MSG_CLEAR_PLAYLIST);
}

void WinampController::playSelectedTrack() {
	SendMessage(_winampWindow, WM_USER, 0, MSG_PLAY_SELECTED_TRACK);
}

int WinampController::getPlaybackStatus() {
	return SendMessage(_winampWindow, WM_USER, 0, MSG_PLAYBACK_STATUS);
}

void WinampController::getCurrentTrackInfo(int& currentPlaybackPosition, int& currentTrackLength) {
	currentPlaybackPosition = getCurrentTrackInfo(PLAYBACK_POSITION);
	currentTrackLength = getCurrentTrackInfo(TRACK_LENGTH);
}

int WinampController::getCurrentTrackInfo(int wichInfo) {
	int info = 0;
	if (wichInfo == PLAYBACK_POSITION)
		info = SendMessage(_winampWindow, WM_USER, 0, MSG_CURRENT_TRACK_INFO);
	else if (wichInfo == TRACK_LENGTH)
		info = SendMessage(_winampWindow, WM_USER, 1, MSG_CURRENT_TRACK_INFO);
	return info;
}

void WinampController::seekCurrentTrack(int position) {
	if (position < 0)
		return;
	SendMessage(_winampWindow, WM_USER, position, MSG_SEEK_CURRENT_TRACK);
}

void WinampController::setPlaylistPosition(int position) {
	SendMessage(_winampWindow, WM_USER, position, MSG_SET_PLAYLIST_POSITION);
}

void WinampController::setVolume(int volume) {
	SendMessage(_winampWindow, WM_USER, volume, MSG_SET_VOLUME);
}

int WinampController::getVolume() {
	return SendMessage(_winampWindow, WM_USER, -666, MSG_SET_VOLUME);
}

void WinampController::toggleMute() {
	if (getVolume() != 0) {
		_volumeBeforeMute = getVolume();
		setVolume(0);
	} else {
		setVolume(_volumeBeforeMute);
	}
}

void WinampController::setPanning(int panning) {
	SendMessage(_winampWindow, WM_USER, panning, MSG_SET_PANNING);
}

int WinampController::getTracksInPlaylist() {
	return SendMessage(_winampWindow, WM_USER, 0, MSG_PLAYLIST_LENGTH);
}

int WinampController::getCurrentTrackInPlaylist() {
	return SendMessage(_winampWindow, WM_USER, 0, MSG_GET_POSITION_IN_PLAYLIST);
}

void WinampController::getCurrentAudioInfo(int& sampleRate, int& bitRate, int& channels) {
	sampleRate = getCurrentAudioInfo(AUDIO_SAMPLERATE);
	bitRate = getCurrentAudioInfo(AUDIO_BITRATE);
	channels = getCurrentAudioInfo(AUDIO_CHANNELS);
}

int WinampController::getCurrentAudioInfo(int wichInfo) {
	int info = 0;
	if (wichInfo == AUDIO_SAMPLERATE)
		info = SendMessage(_winampWindow, WM_USER, 0, MSG_CURRENT_PLAYING_INFO);
	else if (wichInfo == AUDIO_BITRATE)
		info = SendMessage(_winampWindow, WM_USER, 1, MSG_CURRENT_PLAYING_INFO);
	else if (wichInfo == AUDIO_CHANNELS)
		info = SendMessage(_winampWindow, WM_USER, 2, MSG_CURRENT_PLAYING_INFO);
	return info;
}

void WinampController::getElementEqualizer(int* elems) {
	if (elems != NULL) {
		for (int element=0; element<=10; element++, elems++)
			*elems = getElementEqualizer(element);
	}
}

int WinampController::getElementEqualizer(int element) {
	return (element >= 0 && element <= 10) ? SendMessage(_winampWindow, WM_USER, element, MSG_EQUALIZER_ELEMENT_INFO) : -1;
}

bool WinampController::isEqualizerEnabled() {
	return SendMessage(_winampWindow, WM_USER, 11, MSG_EQUALIZER_ELEMENT_INFO);
}

/*bool WinampController::isAutoloadEnabled() {
	return SendMessage(_winampWindow, WM_USER, 0, MSG_GET_AUTOLOAD) != 0;
}*/

void WinampController::setElementEqualizer(int element, int value) {
	if (element < 0 || element > 9 || value < 0 || value > 63)
		return;
	SendMessage(_winampWindow, WM_USER, element, MSG_EQUALIZER_ELEMENT_INFO);
	SendMessage(_winampWindow, WM_USER, value, MSG_GET_AUTOLOAD);
}

void WinampController::restartWinamp() {
	SendMessage(_winampWindow, WM_USER, 0, MSG_RESTART_WINAMP);
}

bool WinampController::isShuffleOptionSet() {
	return SendMessage(_winampWindow, WM_USER, 0, MSG_SHUFFLE_OPTION_STATUS);
}

bool WinampController::isRepeatOptionSet() {
	return SendMessage(_winampWindow, WM_USER, 0, MSG_REPEAT_OPTION_STATUS);
}

void WinampController::setShuffleOption(int mode) {
	SendMessage(_winampWindow, WM_USER, mode, MSG_SET_SHUFFLE_OPTION);
}

void WinampController::setRepeatOption(int mode) {
	SendMessage(_winampWindow, WM_USER, mode, MSG_SET_REPEAT_OPTION);
}

std::string WinampController::getPlayingFilename() {
	return getPlaylistEntry(getCurrentTrackInPlaylist());
}

//std::string WinampController::getID3Title() {
//	return getID3Title(getCurrentTrackInPlaylist());
//}
//
//std::string WinampController::getID3Title(int track) {
//	std::string title;
//	TagLib::FileRef f(getPlaylistEntry(track).c_str());
//	if (!f.isNull() && f.tag())
//		title.append(utf8_encode(f.tag()->title().toWString()));
//	return title;
//}
//
//std::string WinampController::getID3Artist() {
//	return getID3Artist(getCurrentTrackInPlaylist());
//}
//
//std::string WinampController::getID3Artist(int track) {
//	std::string artist;
//	TagLib::FileRef f(getPlaylistEntry(track).c_str());
//	if (!f.isNull() && f.tag())
//		artist.append(utf8_encode(f.tag()->artist().toWString()));
//	return artist;
//}
//
//std::string WinampController::getID3Album() {
//	return getID3Album(getCurrentTrackInPlaylist());
//}
//
//std::string WinampController::getID3Album(int track) {
//	std::string album;
//	TagLib::FileRef f(getPlaylistEntry(track).c_str());
//	if (!f.isNull() && f.tag())
//		album.append(utf8_encode(f.tag()->album().toWString()));
//	return album;
//}
//
//int WinampController::getID3Year() {
//	return getID3Year(getCurrentTrackInPlaylist());
//}
//
//int WinampController::getID3Year(int track) {
//	TagLib::FileRef f(getPlaylistEntry(track).c_str());
//	if (!f.isNull() && f.tag())
//		return f.tag()->year();
//	return 0;
//}
//
//std::string WinampController::getID3Genre() {
//	return getID3Genre(getCurrentTrackInPlaylist());
//}
//
//std::string WinampController::getID3Genre(int track) {
//	std::string genre;
//	TagLib::FileRef f(getPlaylistEntry(track).c_str());
//	if (!f.isNull() && f.tag())
//		genre.append(f.tag()->genre().toCString());
//	return genre;
//}

std::string WinampController::getPlaylistEntry(int track) {
	std::string fileName;
	if (track < 0 || track >= getTracksInPlaylist())
		return fileName;
		
	char buffer[MAX_PATH];
	readWinampToLocal(_winampWindow, (char*)SendMessage(_winampWindow, WM_USER, track, MSG_GET_PLAYLIST_FILE), buffer, MAX_PATH);
	fileName.append(buffer);
	return fileName;
}

void WinampController::addToPlaylist(std::string file) {
	//Chacaleado del bemused
	COPYDATASTRUCT cds;
	cds.dwData = 100; //IPC_PLAYFILE;
	cds.lpData = (void*) file.c_str();
	cds.cbData = strlen((char*) cds.lpData) + 1;
	SendMessage(_winampWindow, WM_COPYDATA, (WPARAM)NULL, (LPARAM)&cds);
	SendMessage(_winampWindow, WM_USER, 0, 120/*IPC_WRITEPLAYLIST*/);
}

void WinampController::play(std::string media) {
	clearPlaylist();
	addToPlaylist(media);
	playTrack();
}

//bool WinampController::trackTag() {
//	return trackTag(getCurrentTrackInPlaylist());
//}
//
//bool WinampController::trackTag(int track) {
//	TagLib::FileRef f(getPlaylistEntry(track).c_str());
//	return (!f.isNull() && f.tag() && !f.tag()->isEmpty());
//}

void WinampController::openWinamp() {
	if (!_winampPath.empty()) {
		CreateThread(NULL, 0, openWinampThread, &_winampPath, 0, NULL);
	}
}

std::string WinampController::getPlayingTitle() {
	return getPlayingTitle(getCurrentTrackInPlaylist());
}

std::string WinampController::getPlayingTitle(int track) {
	if (track < 0 || track >= getTracksInPlaylist())
		return "";
	
	wchar_t buffer[MAX_PATH];
	readWinampToLocal(_winampWindow, (wchar_t*)SendMessage(_winampWindow, WM_USER, track, IPC_GETPLAYLISTTITLEW), buffer, MAX_PATH);
	return utf8_encode(buffer);
}
