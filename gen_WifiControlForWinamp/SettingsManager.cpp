#include "StdAfx.h"
#include <Shlobj.h>		//SHGetFolderPath
#include <fstream>
#include "SettingsManager.h"
#include "WinampServer.h"
#include "util.h"

using namespace gen_WifiControlForWinamp;

SettingsManager::SettingsManager(void)
{
	// Default Settings
	_settings = new std::map<std::string, std::string>();
	_settings->insert(std::pair<std::string, std::string>(KEY_PORT->c_str(), toStdString(WinampServer::DEFAULT_PORT)));
	_settings->insert(std::pair<std::string, std::string>(KEY_SHOWON_START->c_str(), "1"));

	// Configuration path 
	wchar_t tempPath[200];
	SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, tempPath);
	_fullConfigurationPath = new std::string(utf8_encode(tempPath));
	_fullConfigurationPath->append("\\");
	_fullConfigurationPath->append(CONFIG_FILE->c_str());
}

bool SettingsManager::readConfigurationFile()
{
	std::ifstream file(_fullConfigurationPath->c_str());
	if (!file.is_open())
		return false;
	
	std::string line;
	size_t found;
	
	int keysChanged = 0;
	while (file.good()) {
		getline(file, line);
		if (trim(line) != "") {
			if ((found = line.find(KEY_VALUE_SEPARATOR->c_str())) != std::string::npos) {
				std::string key = line.substr(0, found);
				std::string value = line.substr(found+1, line.length()-found);
				if (_settings->find(key) != _settings->end()) {
					_settings->erase(key);
					_settings->insert(std::pair<std::string, std::string>(key, value));
					keysChanged++;
				}
			}
		}
	}
	file.close();
	return keysChanged == _settings->size();
}

bool SettingsManager::writeConfigurationFile()
{
	std::fstream file(_fullConfigurationPath->c_str(), std::fstream::in | std::fstream::out | std::fstream::trunc);
	if (file.is_open())
	{
		std::map<std::string, std::string>::iterator it;
		for (it=_settings->begin(); it!=_settings->end(); it++)
			file << it->first << KEY_VALUE_SEPARATOR->c_str() << it->second << std::endl;
		file.close();
		return true;
	} 
	else
	{
		std::ofstream outfile (_fullConfigurationPath->c_str());
		std::map<std::string, std::string>::iterator it;
		for (it=_settings->begin(); it!=_settings->end(); it++)
			outfile << it->first << KEY_VALUE_SEPARATOR->c_str() << it->second << std::endl;
		outfile.close();

		return outfile.fail() == false;
	}
}

void SettingsManager::setPort(int port)
{
	_settings->erase(KEY_PORT->c_str());
	_settings->insert(std::pair<std::string, std::string>(KEY_PORT->c_str(), toStdString(port)));
}

int SettingsManager::getPort()
{
	return toInteger((*_settings)[*KEY_PORT]);
}

void SettingsManager::setShowOnStart(bool showOnStart)
{
	_settings->erase(KEY_SHOWON_START->c_str());
	_settings->insert(std::pair<std::string, std::string>(KEY_SHOWON_START->c_str(), showOnStart ? "1" : "0"));
}

bool SettingsManager::getShowOnStart()
{
	return toInteger((*_settings)[*KEY_SHOWON_START]) == 1;
}

std::string SettingsManager::getConfigurationPath()
{
	return *_fullConfigurationPath;
}
