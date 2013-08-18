#ifndef MESSAGE_CODES_H
#define MESSAGE_CODES_H


///*********** WM_COMMAND Messages ************///

//Previous track button
#define MSG_PREVIOUS 40044

//Next track button
#define MSG_NEXT 40048

//Play button
#define MSG_PLAY 40045

//Pause/Unpause button
#define MSG_PAUSE 40046

//Stop button 40047
#define MSG_STOP 40047

//Fadeout and stop 40147
#define MSG_FADEOUT_AND_STOP 40147

//Stop after current track 40157
#define MSG_STOP_AFTER_CURRENT_TRACK 40157

//Fast-forward 5 seconds 40148 
#define MSG_FORWARD_5_SECONDS 40148

//Fast-rewind 5 seconds 40144
#define MSG_REWIND_5_SECONDS 40144

//Start of playlist 40154
#define MSG_START_OF_PLAYLIST 40154

//Go to end of playlist 40158
#define MSG_END_OF_PLAYLIST 40158

//Open file dialog 40029
#define MSG_OPEN_FILE_DIALOG 40029

//Open URL dialog 40155
#define MSG_OPEN_URL_DIALOG 40155

//Open file info box 40188
#define MSG_OPEN_FILE_INFO_BOX 40188

//Set time display mode to elapsed 40037
#define MSG_SET_TIME_DISPLAY_ELAPSED 40037

//Set time display mode to remaining 40038
#define MSG_SET_TIME_DISPLAY_REMAINING 40038

//Toggle preferences screen 40012
#define MSG_TOGGLE_PREFERENCES_SCREEN 40012

//Open visualization options 40190
#define MSG_OPEN_VISUALIZATION_OPTIONS 40190

//Open visualization plug-in options 40191
#define MSG_OPEN_VISUALIZATION_PLUGIN_OPTIONS 40190

//Execute current visualization plug-in 40192
#define MSG_EXECUTE_CURRENT_VISUALIZATION_PLUGIN 40192

//Toggle about box 40041
#define MSG_TOGGLE_ABOUT_BOX 40041

//Toggle title Autoscrolling 40189
#define MSG_TOGGLE_TITLE_AUTOSTROLLING 40189

//Toggle always on top 40019
#define MSG_TOGGLE_ALWAYS_ON_TOP 40019

//Toggle Windowshade 40064
#define MSG_TOGGLE_WINDOWSHADE 40064

//Toggle Playlist Windowshade 40266
#define MSG_TOGGLE_PLAYLIST_WINDOWSHADE 40266

//Toggle doublesize mode 40165
#define MSG_TOGGLE_DOUBLESIZE 40165

//Toggle EQ 40036
#define MSG_TOGGLE_EQUALIZER 40036

//Toggle playlist editor 40040
#define MSG_TOGGLE_PLAYLIST_EDITOR 40040

//Toggle main window visible 40258
#define MSG_TOGGLE_MAIN_WINDOW_VISIBLE 40258

//Toggle minibrowser 40298
#define MSG_TOGGLE_MINIBROWSER 40298

//Toggle easymove 40186
#define MSG_TOGGLE_EASYMOVE 40186

//Raise volume by 1% 40058
#define MSG_RAISE_VOLUME_1_PERCENT 40058

//Lower volume by 1% 40059
#define MSG_LOWER_VOLUME_1_PERCENT 40059

//Toggle repeat 40022
#define MSG_TOGGLE_REPEAT 40022

//Toggle shuffle 40023
#define MSG_TOGGLE_SHUFFLE 40023

//Open jump to time dialog 40193
#define MSG_OPEN_JUMP_TO_TIME_DIALOG 40193

//Open jump to file dialog 40194
#define MSG_OPEN_JUMP_TO_FILE_DIALOG 40194

//Open skin selector 40219
#define MSG_OPEN_SKIN_SELECTOR 40219

//Configure current visualization plug-in 40221
#define MSG_CONFIGURE_CURRENT_VISUALIZATION_PLUGIN 40221

//Reload the current skin 40291
#define MSG_RELOAD_CURRENT_SKIN 40291

//Close Winamp 40001
#define MSG_CLOSE_WINAMP 40001

//Moves back 10 tracks in playlist 40197
#define MSG_BACK_TEN_TRACKS 40197

//Show the edit bookmarks 40320
#define MSG_EDIT_BOOKMARKS 40320

//Adds current track as a bookmark 40321
#define MSG_ADD_CURRENT_TRACK_AS_A_BOOKMARK 40321

//Play audio CD 40323
#define MSG_PLAY_AUDIO_CD 40323

//Load a preset from EQ 40253
#define MSG_LOAD_PRESET_FROM_EQUALIZER 40253

//Save a preset to EQF 40254
#define MSG_SAVE_PRESET_TO_EQUALIZER 40254

//Opens load presets dialog 40172
#define MSG_LOAD_PRESETS_DIALOG 40172

//Opens auto-load presets dialog 40173
#define MSG_OPEN_AUTO_LOAD_PRESETS_DIALOG 40173

//Load default preset 40174
#define MSG_LOAD_DEFAULT_PRESET 40174

//Opens save preset dialog 40175
#define MSG_OPEN_SAVE_PRESET_DIALOG 40175

//Opens auto-load save preset 40176
#define MSG_OPEN_AUTOLOAD_SAVE_PRESET 40176

//Opens delete preset dialog 40178
#define MSG_OPEN_DELETE_PRESET_DIALOG 40178

//Opens delete an auto load preset dialog 40180
#define MSG_OPEN_DELETE_AUTOLOAD_PRESET_DIALOG 40180


///*********** WM_USER Messages ************///


#define MSG_WINAMP_VERSION 0 //Retrieves the version of Winamp running. Version will be 0x20yx for 2.yx. This is a good way to determine if you did in fact find the right window, etc. 
#define MSG_START_PLAYBACK 100 //Starts playback. A lot like hitting 'play' in Winamp, but not exactly the same 
#define MSG_CLEAR_PLAYLIST 101 //Clears Winamp's internal playlist. 
#define MSG_PLAY_SELECTED_TRACK 102 //Begins play of selected track. 
#define MSG_WINAMP_CHANGE_DIRECTORY 103 //Makes Winamp change to the directory C:\\download 
#define MSG_PLAYBACK_STATUS 104 //Returns the status of playback. If 'ret' is 1, Winamp is playing. If 'ret' is 3, Winamp is paused. Otherwise, playback is stopped. 
#define MSG_CURRENT_TRACK_INFO 105 //If data is 0, returns the position in milliseconds of playback. If data is 1, returns current track length in seconds. Returns -1 if not playing or if an error occurs. 
#define MSG_SEEK_CURRENT_TRACK 106 //Seeks within the current track. The offset is specified in 'data', in milliseconds. 
#define MSG_WRITE_CURRENT_PLAYLIST 120 //Writes out the current playlist to Winampdir\winamp.m3u, and returns the current position in the playlist. 
#define MSG_SET_PLAYLIST_POSITION 121 //Sets the playlist position to the position specified in tracks in 'data'. 

//Sets the volume to 'data', which can be between 0 (silent) and 255 (maximum). 
//If we passed -666 parameter to sets volume, it returns current volume D: (http://forums.winamp.com/showthread.php?s=&threadid=195266) 
#define MSG_SET_VOLUME 122 

#define MSG_SET_PANNING 123 //Sets the panning to 'data', which can be between 0 (all left) and 255 (all right). **************[-127 - 127]OK
#define MSG_PLAYLIST_LENGTH 124 //Returns length of the current playlist, in tracks. 
#define MSG_GET_POSITION_IN_PLAYLIST 125 //Returns the position in the current playlist, in tracks (requires Winamp 2.05+). 
#define MSG_CURRENT_PLAYING_INFO 126 //Retrieves info about the current playing track. Returns samplerate (i.e. 44100) if 'data' is set to 0, bitrate if 'data' is set to 1, and number of channels if 'data' is set to 2. (requires Winamp 2.05+) 
#define MSG_EQUALIZER_ELEMENT_INFO 127 //Retrieves one element of equalizer data, based on what 'data' is set to. 0-9 The 10 bands of EQ data. Will return 0-63 (+20db - -20db). 10 The preamp value. Will return 0-63 (+20db - -20db). 11 Enabled. Will return zero if disabled, nonzero if enabled. 
#define MSG_GET_AUTOLOAD 128 //Autoload. Will return zero if disabled, nonzero if enabled. To set an element of equalizer data, simply query which item you wish to set using the message above (127), then call this message with data 
#define MSG_ADD_FILE_TO_BOOKMARK 129 //Adds the specified file to the Winamp bookmark list 
#define MSG_RESTART_WINAMP 135 //Restarts Winamp 


//Here is a list of the currently supported ids that you can only use from within Winamp plug-ins (since they depend on running in the same process as Winamp):

#define MSG_SET_SKIN 200 //Sets the current skin. 'data' points to a string that describes what skin to load, which can either be a directory or a .zip file. If no directory name is specified, the default Winamp skin directory is assumed. 
#define MSG_GET_SKIN 201 //Retrieves the current skin directory and/or name. 'ret' is a pointer to the Skin name (or NULL if error), and if 'data' is non-NULL, it must point to a string 260 bytes long, which will receive the pathname to where the skin bitmaps are stored (which can be either a skin directory, or a temporary directory when zipped skins are used) (Requires Winamp 2.04+). 

//Selects and executes a visualization plug-in. 'data' points to a string which defines which plug-in to execute. The string can be in the following formats:
//vis_whatever.dll Executes the default module in vis_whatever.dll in your plug-ins directory. 
//vis_whatever.dll,1 executes the second module in vis_whatever.dll 
//C:\path\vis_whatever.dll,1 executes the second module in vis_whatever.dll in another directory 
#define MSG_SELECT_AND_EXECUTE_VISUALIZATION_PLUGIN 202 

#define MSG_GET_PLAYLIST_FILE 211 //Retrieves (and returns a pointer in 'ret') a string that contains the filename of a playlist entry (indexed by 'data'). Returns NULL if error, or if 'data' is out of range. 
#define MSG_GET_PLAYLIST_TITLE 212 //Retrieves (and returns a pointer in 'ret') a string that contains the title of a playlist entry (indexed by 'data'). Returns NULL if error, or if 'data' is out of range. 
#define MSG_OPEN_URL_IN_MINIBROWSER 241 //Opens an new URL in the minibrowser. If the URL is NULL it will open the Minibrowser window 
#define MSG_INTERNET_CONNECTION_STATUS 242 //Returns 1 if the internet connecton is available for Winamp 
#define MSG_ASK_UPDATE_CURRENT_TITLE 243 //Asks Winamp to update the information about the current title 
#define MSG_SETS_CURRENT_PLAYLIST_ITEM 245 //Sets the current playlist item 
#define MSG_GET_CURRENT_MINIBROWSER_URL 246 //Retrives the current Minibrowser URL into the buffer. 
#define MSG_FLUSH_PLAYLIST_CACHE_BUFFER 247 //Flushes the playlist cache buffer 
#define MSG_BLOCK_UPDATES_MINIBROWSER 248 //Blocks the Minibrowser from updates if value is set to 1 
#define MSG_FORCE_OPEN_URL_IN_MINIBROWSER 249 //Opens an new URL in the minibrowser (like 241) except that it will work even if 248 is set to 1 
#define MSG_SHUFFLE_OPTION_STATUS 250 //Returns the status of the shuffle option (1 if set) 
#define MSG_REPEAT_OPTION_STATUS 251 //Returns the status of the repeat option (1 if set) 
#define MSG_SET_SHUFFLE_OPTION 252 //Sets the status of the suffle option (1 to turn it on) 
#define MSG_SET_REPEAT_OPTION 253 //Sets the status of the repeat option (1 to turn it on) 

#define IPC_GETPLAYLISTTITLEW 213

#endif
