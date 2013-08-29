#pragma once
#include <map>
#include "GUI.h"

namespace gen_WifiControlForWinamp
{
	public ref class AppManager
	{
	private:
		static GUI^ _gui = nullptr;
		static WinampServer* _winampServer = nullptr;
		static SettingsManager^ _settingsManager = nullptr;
		static std::map<std::string, std::string>* _configs = nullptr;
		AppManager(void);

	public:
		static void configure(WinampServer* winampServer);
		static void runApp();
		static void closeApp();
		static void showApp();
	};

	
}
