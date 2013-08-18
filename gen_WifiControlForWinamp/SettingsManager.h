#pragma once

#include <map>
#include <string>

namespace gen_WifiControlForWinamp
{
	public ref class SettingsManager
	{
	private:
		std::map<std::string, std::string>* _settings;
		std::string* _fullConfigurationPath;
	
	public:
		static const std::string* KEY_PORT = new std::string("PORT");
		static const std::string* KEY_SHOWON_START = new std::string("SHOW_ON_START");
		static const std::string* KEY_VALUE_SEPARATOR = new std::string("=");
		static const std::string* CONFIG_FILE = new std::string("WIFICONTROLFORWINAMP.DAT");

		SettingsManager(void);
		bool readConfigurationFile();
		bool writeConfigurationFile();
		void setPort(int port);
		int getPort();
		void setShowOnStart(bool showOnStart);
		bool getShowOnStart();
		std::string getConfigurationPath();
	};
}
