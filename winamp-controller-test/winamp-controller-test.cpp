// winamp-conteroller-test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "WinampController.h"
#include <iostream>
#include <stdio.h>
#include <conio.h>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	WinampController *winampController = new WinampController;
	
	system("cls");
	printf ("Winamp Controller\n");
	printf ("a. isWinampRunning\n");
	printf ("b. previousTrack\n");
	printf ("c. nextTrack\n");
	printf ("d. playTrack\n");
	printf ("e. pauseTrack\n");
	printf ("f. stopPlayback\n");
	printf ("g. togglePlayPause\n");
	//printf ("h. stopAfterCurrentTrack\n");
	printf ("i. forwardFiveSeconds\n");
	printf ("j. rewindFiveSeconds\n");
	printf ("k. gotoStartOfPlaylist\n");
	printf ("l. gotoEndOfPlaylist\n");
	printf ("m. raiseVolumeOnePercent\n");
	printf ("n. lowerVolumeOnePercent\n");
	printf ("o. toggleRepeat\n");
	printf ("p. toggleShuffle\n");
	printf ("q. closeWinamp\n");
	printf ("r. rewindTenTracksInPlaylist\n");
	printf ("s. playAudioCD\n");
	printf ("t. loadDefaultPreset\n");
	printf ("u. getWinampVersion\n");
	printf ("v. startPlayback\n");
	printf ("w. clearPlaylist\n");
	printf ("x. playSelectedTrack\n");
	printf ("y. getPlaybackStatus\n");
	printf ("z. getCurrentTrackInfo\n");
	//printf ("z. getCurrentPlaybackPosition\n");
	//printf ("A. getCurrentTrackLength\n");
	printf ("B. seekCurrentTrack\n");
	printf ("C. setPlaylistPosition\n");
	printf ("D. setVolume\n");
	printf ("E. getVolume\n");
	printf ("F. toggleMute\n");
	printf ("G. setPanning\n");
	printf ("H. getTracksInPlaylist\n");
	printf ("I. getCurrentTrackInPlaylist\n");
	printf ("J. getCurrentAudioInfo\n");
	//printf ("K. getPlayingTitleW\n");
	//printf ("L. getCurrentChannels\n");
	printf ("M. getElementEqualizer\n");
	printf ("N. getPlayingTitle\n");
	printf ("O. isEqualizerEnabled\n");
	printf ("P. isAutoloadEnabled\n");
	printf ("Q. setElementEqualizer\n");
	printf ("R. restartWinamp\n");
	printf ("S. isShuffleOptionSet\n");
	printf ("T. isRepeatOptionSet\n");
	printf ("U. setShuffleOption\n");
	printf ("V. setRepeatOption\n");
	printf ("W. getPlayingFilename\n");
	printf ("X. getPlayingTitle\n");
	//printf ("X. getID3Title\n");
	//printf ("Y. getID3Artist\n");
	//printf ("Z. getID3Album\n");
	//printf ("1. getID3Year\n");
	//printf ("2. getID3Genre\n");
	printf ("3. getWinampPath\n");
	printf ("4. getPlaylistEntry\n");
	printf ("5. addToPlaylist\n");
	printf ("6. playMedia\n");
	printf ("7. trackTag\n");
	printf ("8. openWinamp\n");
	printf ("0. Exit\n");
	for (;;) {
		int option = getch();
		switch (option){
			case 'a':
				printf ("isWinampRunning: %s\n", winampController->isWinampRunning() ? "true" : "false");
				break;
			case 'b':
				winampController->previousTrack();
				break;
			case 'c':
				winampController->nextTrack();
				break;
			case 'd': {
				int track;
				cout << "which track ? (-1 = current)"; cin >> track;
				if (track == -1)
					winampController->playTrack();
				else
					winampController->playTrack(track);
				break;
			}
			case 'e':
				winampController->pauseTrack();
				break;
			case 'f': {
				int mode;
				cout << "(1)Stop current track. (2)Fadeout and stop. (3)Stop after current track." << endl; cin >> mode;
				winampController->stopPlayback(mode);
				break;
			}
			case 'g':
				winampController->togglePlayPause();
				break;
			case 'i':
				winampController->forwardFiveSeconds();
				break;
			case 'j':
				winampController->rewindFiveSeconds();
				break;
			case 'k':
				winampController->gotoStartOfPlaylist();
				break;
			case 'l':
				winampController->gotoEndOfPlaylist();
				break;
			case 'm':
				winampController->raiseVolumeOnePercent();
				break;
			case 'n':
				winampController->lowerVolumeOnePercent();
				break;
			case 'o':
				winampController->toggleRepeat();
				break;
			case 'p':
				winampController->toggleShuffle();
				break;
			case 'q':
				winampController->closeWinamp();
				break;
			case 'r':
				winampController->rewindTenTracksInPlaylist();
				break;
			case 's':
				winampController->playAudioCD();
				break;
			case 't':
				winampController->loadDefaultPreset();
				break;
			case 'u':
				printf ("winampVersion: %d\n", winampController->getWinampVersion());
				break;
			case 'v':
				winampController->startPlayback();
				break;
			case 'w':
				winampController->clearPlaylist();
				break;
			case 'x':
				winampController->playSelectedTrack();
				break;
			case 'y':
				printf ("playbackStatus: %d\n", winampController->getPlaybackStatus());
				break;
			case 'z': {
				int playbackPosition, trackLength;
				winampController->getCurrentTrackInfo(playbackPosition, trackLength);
				printf("v1: playbackPosition:%d, trackLength:%d\n", playbackPosition, trackLength);
				playbackPosition = winampController->getCurrentTrackInfo(1);
				trackLength = winampController->getCurrentTrackInfo(2);
				printf("v2: playbackPosition:%d, trackLength:%d\n", playbackPosition, trackLength);
				break;
			}
			/*case 'z':
				printf ("currentPlaybackPosition: %d\n", winampController->getCurrentPlaybackPosition());
				break;
			case 'A':
				printf ("currentTrackLength: %d\n", winampController->getCurrentTrackLength());
				break;*/
			case 'B': {
				int position;
				printf ("seekCurrentTrack to... ");scanf ("%d", &position);printf ("\n");
				winampController->seekCurrentTrack(position);
				break;
			}
			case 'C': {
				int position;
				printf ("setPlaylistPosition to... ");scanf ("%d", &position);printf ("\n");
				winampController->setPlaylistPosition(position);
				break;
			}
			case 'D': {
				int volume;
				printf ("setVolume to... ");scanf ("%d", &volume);printf ("\n");
				winampController->setVolume(volume);
				break;
			}
			case 'E':
				printf ("volume: %d\n", winampController->getVolume());
				break;
			case 'F':
				winampController->toggleMute();
				break;
			case 'G': {
				int panning;
				printf ("setPanning to... ");scanf("%d", &panning);printf ("\n");
				winampController->setPanning(panning);
				break;
			}
			case 'H':
				printf ("tracksInPlaylist: %d\n", winampController->getTracksInPlaylist());
				break;
			case 'I':
				printf ("currentTrackInPlaylist: %d\n", winampController->getCurrentTrackInPlaylist());
				break;
			case 'J': {
				int sampleRate, bitRate, channels;
				winampController->getCurrentAudioInfo(sampleRate, bitRate, channels);
				printf ("V1: sampleRate:%d, bitRate:%d, channels:%d\n", sampleRate, bitRate, channels);
				sampleRate = winampController->getCurrentAudioInfo(AUDIO_SAMPLERATE);
				bitRate = winampController->getCurrentAudioInfo(AUDIO_BITRATE);
				channels = winampController->getCurrentAudioInfo(AUDIO_CHANNELS);
				printf ("V2: sampleRate:%d, bitRate:%d, channels:%d\n", sampleRate, bitRate, channels);
				break;
			}
			/*case 'K': {
				cout << "playingTitleW:" << winampController->getPlayingTitleW() << endl;
				break;
			}*/
			case 'M': {
				int elements[11];
				winampController->getElementEqualizer(elements);
				printf("elements:");
				for (int i=0;i<11; i++)printf("%d ", elements[i]);
				printf("\n");
				break;
			}
			case 'N': {
				int track;
				printf ("wich Track (-1 = current) ?");scanf("%d",&track);
				if (track == -1)
					printf ("playingTitle: %s\n", winampController->getPlayingTitle().c_str());
				else
					printf ("playingTitle: %s\n", winampController->getPlayingTitle(track).c_str());
				break;
			}
			case 'O':
				printf ("isEqualizerEnabled: %s\n", winampController->isEqualizerEnabled() ? "true" : "false");
				break;
			/*case 'P':
				printf ("isAutoloadEnabled: %s\n", winampController->isAutoloadEnabled() ? "true" : "false");
				break;*/
			case 'Q': {
				int element, value;
				printf ("setElementEqualizer number... ");scanf ("%d", &element);printf ("\n");
				printf ("value... ");scanf ("%d", &value);printf ("\n");
				winampController->setElementEqualizer(element, value);
				break;
			}
			case 'R':
				winampController->restartWinamp();
				break;
			case 'S':
				printf ("shuffleOptionSet: %s\n", winampController->isShuffleOptionSet() ? "true" : "false");
				break;
			case 'T':
				printf ("repeatOptionSet: %s\n", winampController->isRepeatOptionSet() ? "true" : "false");
				break;
			case 'U': {
				int mode;
				printf ("setShuffleOption to... ");scanf ("%d", &mode);printf ("\n");
				winampController->setShuffleOption(mode);
				break;
			}
			case 'V': {
				int mode;
				printf ("setRepeatOption to... ");scanf ("%d", &mode);printf ("\n");
				winampController->setRepeatOption(mode);
				break;
			}
			case 'W':
				cout << "file:[" << winampController->getPlayingFilename() << "]" << endl;
				break;
			case 'X':
				int track;
				cout << "wich track (-1 = current)";cin >> track;
				if (track == -1) {
					cout << "playing title:[" << winampController->getPlayingTitle() << "]";
				} else {
					cout << "playing title:[" << winampController->getPlayingTitle(track) << "]";
				}
				winampController->getPlayingTitle();
				break;
			/*case 'X': {
				int track;
				cout << "wich track (-1 = current)";cin >> track;
				if (track == -1)
					cout << "title:[" << winampController->getID3Title() << "]" << endl;
				else
					cout << "title:[" << winampController->getID3Title(track) << "]" << endl;
				}
				break;
			case 'Y': {
				int track;
				cout << "wich track (-1 = current)";cin >> track;
				if (track == -1)
					cout << "artist:[" << winampController->getID3Artist() << "]" << endl;
				else
					cout << "artist:[" << winampController->getID3Artist(track) << "]" << endl;
				break;
			}
			case 'Z': {
				int track;
				cout << "wich track (-1 = current)";cin >> track;
				if (track == -1)
					cout << "album:[" << winampController->getID3Album() << "]" << endl;
				else
					cout << "album:[" << winampController->getID3Album(track) << "]" << endl;
				break;
			}
			case '1': {
				int track;
				cout << "wich track (-1 = current)";cin >> track;
				if (track == -1)
					cout << "year:[" << winampController->getID3Year() << "]" << endl;
				else
					cout << "year:[" << winampController->getID3Year(track) << "]" << endl;
				break;
			}
			case '2': {
				int track;
				cout << "wich track (-1 = current)";cin >> track;
				if (track == -1)
					cout << "genre:[" << winampController->getID3Genre() << "]" << endl;
				else
					cout << "genre:[" << winampController->getID3Genre(track) << "]" << endl;
				break;
			}*/
			case '3':
				cout << "winampPath:[" << winampController->getWinampPath() << "]" << endl;
				break;
			case '4': {
				int entry;
				cout << "wich entry ? "; cin >> entry;
				cout << "entry " << entry << ":[" << winampController->getPlaylistEntry(entry) << "]" << endl;
				break;
			}
			case '5': {
				char song[MAX_PATH];
				cout << "wich song?";gets(song);
				winampController->addToPlaylist(song);
				break;
			}
			case '6': {
				char media[MAX_PATH];
				cout << "wich media?";gets(media);
				winampController->play(media);
				break;
			}
			/*case '7': {
				int track;
				cout << "wich track (-1 = current)"; cin >> track;
				if (track == -1)
					cout << "trackTag ? " << (winampController->trackTag() ? "simon" : "nariz de perro") << endl;
				else
					cout << "trackTag of " << track << " ? " << (winampController->trackTag(track) ? "simon" : "nariz de perro") << endl;
				break;
			}*/
			case '8':
				winampController->openWinamp();
				break;
			case '0':
				return 0;
		}
	}
	return 0;
}

