#include "WinampServer.h"
#include "WinampController.h"
#include <sstream>
#include <iostream>

WinampServer::WinampServer() {
	_port = DEFAULT_PORT;
	_synchronizedMode = true;
}

WinampServer::WinampServer(int port) {
	_port = port;
	_synchronizedMode = true;
}

WinampServer::~WinampServer() {
}
		
void WinampServer::setListenerWindow(HWND listenerWindow) {
	_listenerWindow = listenerWindow;
}

HWND WinampServer::getListenerWindow() {
	return _listenerWindow;
}

void WinampServer::setPort(int port) {
	_port = port;
}

int WinampServer::getPort() {
	return _port;
}

void WinampServer::start() {
	extern int PORT;
	extern HWND LISTENER_WINDOW;
	
	PORT = _port;
	LISTENER_WINDOW = _listenerWindow;
	
	if ((_serverThread = CreateThread(NULL, 0, waitForCommandsThread, this, 0, NULL)) == NULL) {
		sendDataMessage(SERVER_STARTUP_ERROR, "Server startup error");
	}
}

void WinampServer::stop() {
	extern SOCKET SERVER_SOCKET, CLIENT_SOCKET;
	TerminateThread(_serverThread, 0);
	closesocket(SERVER_SOCKET);
	closesocket(CLIENT_SOCKET);
	WSACleanup();
	sendDataMessage(SERVER_MSG, "Server is down");
}

void WinampServer::setSynchronizedMode(bool mode) {
	_synchronizedMode = mode;
}

bool WinampServer::getSynchronizedMode() {
	return _synchronizedMode;
}

HANDLE& WinampServer::getServerThread() {
	return _serverThread;
}

std::string WinampServer::parseRequest(char *prequest) {
	std::cout << "request:" << prequest << " - ";
	std::string request(prequest);
	
	std::string response;
	if (request.size() > 0) {
		int command;
		std::string param, param2;
		
		int _pos = request.find('|');
		std::stringstream commandStream;
		if (_pos == std::string::npos) {
			commandStream << request;
			commandStream >> command;
		} else {
			commandStream << request.substr(0, _pos);
			commandStream >> command;
			
			int _pos2 = request.find('|', _pos+1);
			if (_pos2 == std::string::npos) {
				param.append(request.substr(_pos+1, request.size()-_pos));
			} else {
				param.append(request.substr(_pos+1, _pos2-_pos-1));
				param2.append(request.substr(_pos2+1, request.size()-_pos2));
			}
			//std::cout << "command:" << command << ", param:" << param << ", param2:" << param2 << std::endl;
		}
		std::cout << "command[" << command << "], param[" << param << "], param2[" << param2 << "]" << std::endl;
		response = executeCommand(command, param, param2);
	}
	return response;
}

std::string WinampServer::executeCommand(int command, std::string param, std::string param2) {
	WinampController _winampController;
	_winampController.handleWinampWindow();

	std::string buffer;
	std::stringstream stringStream(std::ios_base::out | std::ios_base::in);
	
	/**
	 * La respuesta del server ira acompañada por el comando solicitado,
	 * de esta forma cuando se soliciten multiples peticiones a la vez,
	 * se identificara la respuesta que corresponde a cada una
	 **/
	std::stringstream commandCode;
	commandCode << command;
	buffer.append(commandCode.str());
	buffer.append("|");
	///-----------------------------------------------------------------------
	switch (command) {
		case 1:
			buffer.append(_winampController.isWinampRunning() ? "1" : "0");
			sendDataMessage(666, "Checking if winamp is running.");
			break;
		case 2:
			_winampController.previousTrack();
			sendDataMessage(666, "Goto previous track.");
			break;
		case 3:
			_winampController.nextTrack();
			sendDataMessage(666, "Goto next track.");
			break;
		case 4: {
			if (param.empty()) {
				_winampController.playTrack();
			} else {
				int track;
				std::stringstream paramStream;
				paramStream << param;
				paramStream >> track;
				_winampController.playTrack(track);
			}
			sendDataMessage(666, "Play track.");
			break;
		}
		case 5:
			sendDataMessage(666, "Pause track.");
			_winampController.pauseTrack();
			break;
		case 6: {
			int mode;
			if (param.empty()) {
				mode = STOP_CURRENT_TRACK;
			} else {
				stringStream << param;
				stringStream >> mode;
			}
			_winampController.stopPlayback(mode);
			break;
		}
		case 7:
			_winampController.togglePlayPause();
			sendDataMessage(666, "Toggle play pause.");
			break;
		case 9:
			_winampController.forwardFiveSeconds();
			sendDataMessage(666, "Forward five seconds.");
			break;
		case 10:
			_winampController.rewindFiveSeconds();
			sendDataMessage(666, "Rewind five seconds.");
			break;
		case 11:
			_winampController.gotoStartOfPlaylist();
			sendDataMessage(666, "Goto start of current playlist.");
			break;
		case 12:
			_winampController.gotoEndOfPlaylist();
			sendDataMessage(666, "Goto end of current playlist.");
			break;
		case 13: {
			stringStream << _winampController.raiseVolumeOnePercent();
			std::string message("Raise volume to "); message.append(stringStream.str());
			buffer.append(message);
			sendDataMessage(666, message);
			break;
		}
		case 14: {
			stringStream << _winampController.lowerVolumeOnePercent();
			std::string message("Lower volume to "); message.append(stringStream.str());
			buffer.append(message);
			sendDataMessage(666, message);
			break;
		}
		case 15:
			_winampController.toggleRepeat();
			sendDataMessage(666, "Toggle repeat.");
			break;
		case 16:
			_winampController.toggleShuffle();
			sendDataMessage(666, "Toggle shuffle.");
			break;
		case 17:
			_winampController.closeWinamp();
			sendDataMessage(666, "Close winamp.");
			break;
		case 18:
			_winampController.rewindTenTracksInPlaylist();		
			sendDataMessage(666, "Rewind ten tracks in current playlist.");
			break;
		case 19:
			_winampController.playAudioCD();
			sendDataMessage(666, "Play Audio CD.");
			break;
		case 20:
			_winampController.loadDefaultPreset();
			sendDataMessage(666, "Load default preset.");
			break;
		case 21:
			stringStream << _winampController.getWinampVersion();
			buffer.append(stringStream.str());
			sendDataMessage(666, "Check winamp version.");
			break;
		case 22:
			_winampController.startPlayback();
			sendDataMessage(666, "Start playback.");
			break;
		case 23:
			_winampController.clearPlaylist();
			sendDataMessage(666, "Clear current playlist.");
			break;
		case 24:
			_winampController.playSelectedTrack();
			sendDataMessage(666, "Play selected track.");
			break;
		case 25:
			stringStream << _winampController.getPlaybackStatus();
			buffer.append(stringStream.str());
			sendDataMessage(666, "Check playback status.");
			break;
		case 26: {
			if (param.empty()) {
				int playbackPosition, trackLength;
				_winampController.getCurrentTrackInfo(playbackPosition, trackLength);
				stringStream << playbackPosition << "|" << trackLength;
			} else {
				int prop;
				std::stringstream paramStream;
				paramStream << param;
				paramStream >> prop;
				stringStream << _winampController.getCurrentTrackInfo(prop);
			}
			buffer.append(stringStream.str());
			sendDataMessage(666, "Getting current track info");
			break;
		}
		case 28: {
			int position;
			stringStream << param;
			stringStream >> position;
			_winampController.seekCurrentTrack(position);
			sendDataMessage(666, "Seeking current track position.");
			break;
		}
		case 29: {
			int position;
			stringStream << param;
			stringStream >> position;
			_winampController.setPlaylistPosition(position);
			sendDataMessage(666, "Setting playlist position.");
			break;
		}
		case 30: {
			int volume;
			stringStream << param;
			stringStream >> volume;
			_winampController.setVolume(volume);
			sendDataMessage(666, "Adjuste volume.");
			break;
		}
		case 31:
			stringStream << _winampController.getVolume();
			buffer.append(stringStream.str());
			sendDataMessage(666, "Getting current volume.");
			break;
		case 32:
			_winampController.toggleMute();
			sendDataMessage(666, "Toggle mute.");
			break;
		case 33: {
			int panning;
			stringStream << param;
			stringStream >> panning;
			_winampController.setPanning(panning);
			sendDataMessage(666, "Setting panning.");
			break;
		}
		case 34:
			stringStream << _winampController.getTracksInPlaylist();
			buffer.append(stringStream.str());
			sendDataMessage(666, "Check tracks in playlist.");
			break;
		case 35:
			stringStream << _winampController.getCurrentTrackInPlaylist();
			buffer.append(stringStream.str());
			sendDataMessage(666, "Getting current track in playlist.");
			break;
		case 36: {
			if (param.empty()) {
				int sampleRate, bitRate, channels;
				_winampController.getCurrentAudioInfo(sampleRate, bitRate, channels);
				stringStream << sampleRate << "|" << bitRate << "|" << channels;
				buffer.append(stringStream.str());
			} else {
				int prop;
				std::stringstream paramStream;
				paramStream << param;
				paramStream >> prop;
				stringStream << _winampController.getCurrentAudioInfo(prop);
				buffer.append(stringStream.str());
			}
			sendDataMessage(666, "Getting current audio info.");
			break;
		}
		case 39: {
			if (param.empty()) {
				int elements[11];
				_winampController.getElementEqualizer(elements);
				for (int i=0; i<11; i++) {
					if (i > 0) stringStream << "|";
					stringStream << elements[i];
				}
			} else {
				int element;
				std::stringstream paramStream;
				paramStream << param;
				paramStream >> element;
				stringStream << _winampController.getElementEqualizer(element);
			}
			buffer.append(stringStream.str());
			sendDataMessage(666, "Checking equalizer.");
			break;
		}
		case 41:
			stringStream << _winampController.isEqualizerEnabled() ? "1" : "0";
			buffer.append(stringStream.str());
			sendDataMessage(666, "Checking equalizer status.");
			break;
		/*case 42:
			stringStream << _winampController.isAutoloadEnabled() ? "1" : "0";
			buffer.append(stringStream.str());*/
			break;
		case 43: {
			int element, value;
			stringStream << param << " " << param2;
			stringStream >> element >> value;
			_winampController.setElementEqualizer(element, value);
			sendDataMessage(666, "Setting equalizer values.");
			break;
		}
		case 44:
			_winampController.restartWinamp();
			sendDataMessage(666, "Restart winamp.");
			break;
		case 45:
			stringStream << _winampController.isShuffleOptionSet() ? "1" :"0";
			buffer.append(stringStream.str());
			sendDataMessage(666, "Checking shuffle option.");
			break;
		case 46:
			stringStream << _winampController.isRepeatOptionSet() ? "1" :"0";
			buffer.append(stringStream.str());
			sendDataMessage(666, "Checking repeat option.");
			break;
		case 47: {
			int mode;
			stringStream << param;
			stringStream >> mode;
			_winampController.setShuffleOption(mode);
			sendDataMessage(666, "Setting shuffle option.");
			break;
		}
		case 48: {
			int mode;
			stringStream << param;
			stringStream >> mode;
			_winampController.setRepeatOption(mode);
			sendDataMessage(666, "Setting repeat option.");
			break;
		}
		case 49:
			stringStream << _winampController.getPlayingFilename().c_str();
			buffer.append(stringStream.str());
			sendDataMessage(666, "Getting playingh file.");
			break;
		/*case 50: {
			if (param.empty()) {
				stringStream << _winampController.getID3Title().c_str();
				buffer.append(stringStream.str());
			} else {
				int track;
				std::stringstream paramStream;
				paramStream << param;
				paramStream >> track;
				stringStream << _winampController.getID3Title(track);
				buffer.append(stringStream.str());
			}
			sendDataMessage(666, "Getting ID3 Title.");
			break;
		}
		case 51: {
			if (param.empty()) {
				stringStream << _winampController.getID3Artist();
				buffer.append(stringStream.str());
			} else {
				int track;
				std::stringstream paramStream;
				paramStream << param;
				paramStream >> track;
				stringStream << _winampController.getID3Artist(track);
				buffer.append(stringStream.str());
			}
			sendDataMessage(666, "Getting ID3 Artist.");
			break;
		}
		case 52: {
			if (param.empty()) {
				stringStream << _winampController.getID3Album();
				buffer.append(stringStream.str());
			} else {
				int track;
				std::stringstream paramStream;
				paramStream << param;
				paramStream >> track;
				stringStream << _winampController.getID3Album(track);
				buffer.append(stringStream.str());
			}
			sendDataMessage(666, "Getting ID3 Album.");
			break;
		}
		case 53: {
			if (param.empty()) {
				stringStream << _winampController.getID3Year();
				buffer.append(stringStream.str());
			} else {
				int track;
				std::stringstream paramStream;
				paramStream << param;
				paramStream >> track;
				stringStream << _winampController.getID3Year(track);
				buffer.append(stringStream.str());
			}
			sendDataMessage(666, "Getting ID3 Year.");
			break;
		}
		case 54: {
			if (param.empty()) {
				stringStream << _winampController.getID3Genre();
				buffer.append(stringStream.str());
			} else {
				int track;
				std::stringstream paramStream;
				paramStream << param;
				paramStream >> track;
				stringStream << _winampController.getID3Genre(track);
				buffer.append(stringStream.str());
			}
			sendDataMessage(666, "Getting ID3 Genre.");
			break;
		}*/
		case 55: {
			int track;
			std::stringstream paramStream;
			paramStream << param;
			paramStream >> track;
			stringStream << _winampController.getPlaylistEntry(track);
			buffer.append(stringStream.str());
			sendDataMessage(666, "Getting Playlist entry.");
			break;
		}
		case 56: {
			std::string message("Adding to playlist: "); message.append(param);
			_winampController.addToPlaylist(param);
			sendDataMessage(666, message);
			break;
		}
		case 57: {
			std::string message("Start to play media: "); message.append(param);
			_winampController.play(param);
			sendDataMessage(666, message);
			break;
		}
		/*case 58: {
			if (param.empty()) {
				stringStream << _winampController.trackTag() ? "1" : "0";
				buffer.append(stringStream.str());
			} else {
				int track;
				std::stringstream paramStream;
				paramStream << param;
				paramStream >> track;
				stringStream << _winampController.trackTag(track) ? "1" : "0";
				buffer.append(stringStream.str());
			}
			sendDataMessage(666, "Checking if track has ID3 Tag.");
			break;
		}*/
		case 59:
			_winampController.openWinamp();
			break;
		case 60:
			if (param.empty()) {
				stringStream << _winampController.getPlayingTitle();
			} else {
				int track;
				std::stringstream paramStream;
				paramStream << param;
				paramStream >> track;
				stringStream << _winampController.getPlayingTitle(track);
			}
			buffer.append(stringStream.str());
			sendDataMessage(666, "Getting current playing title.");
			break;
		/*case 61:
			if (param.empty()) {
				stringStream << _winampController.getPlayingTitleW();
			} else {
				int track;
				std::stringstream paramStream;
				paramStream << param;
				paramStream >> track;
				stringStream << _winampController.getPlayingTitleW(track);
			}
			buffer.append(stringStream.str());
			sendDataMessage(666, "Getting current playing titleW.");
			break;*/
		default:
			break;
	}
	/*if (buffer.size() == 0) {
		std::stringstream commandStream;
		commandStream << command;
		buffer.append(commandStream.str());
	}*/
	return buffer;
}
