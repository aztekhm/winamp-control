#include "stdafx.h"
#include <windows.h>
#include "gen_winampControl.h"
#include "GUI.h"

using namespace gen_winampControl;

// this structure contains plugin information, version, name...
// GPPHDR_VER is the version of the winampGeneralPurposePlugin (GPP) structure
winampGeneralPurposePlugin plugin = {
	GPPHDR_VER,  // version of the plugin, defined in "gen_myplugin.h"
	PLUGIN_NAME, // name/title of the plugin, defined in "gen_myplugin.h"
	init,        // function name which will be executed on init event
	config,      // function name which will be executed on config event
	quit,        // function name which will be executed on quit event
	0,           // handle to Winamp main window, loaded by winamp when this dll is loaded
	0            // hinstance to this dll, loaded by winamp when this dll is loaded
};

int init() {
	WinampController* winampController = new WinampController();
	winampController->setWinampWindow(plugin.hwndParent);

	GUI ^gui = gcnew GUI();
	gui->setWinampController(winampController);
	gui->Show();
	return 0;
}

void config() {

}

void quit() {

}

extern "C" __declspec(dllexport) winampGeneralPurposePlugin * winampGetGeneralPurposePlugin() {
	return &plugin;
}
