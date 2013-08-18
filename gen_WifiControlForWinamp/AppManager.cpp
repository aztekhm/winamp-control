#include "StdAfx.h"
#include <sstream>
#include <Shlobj.h>
#include <vcclr.h>
#include "AppManager.h"
#include "util.h"

using namespace gen_WifiControlForWinamp;

AppManager::AppManager(void)
{
}

void AppManager::runApp()
{
	_winampServer = new WinampServer();
	_settingsManager = gcnew SettingsManager();
	_settingsManager->readConfigurationFile();
	
	if (!_settingsManager->readConfigurationFile())
	{
		String^ message = gcnew String("Cant find configuration file at: ");
		message += (gcnew System::String(_settingsManager->getConfigurationPath().c_str()));
		MessageBox::Show(message, "path", MessageBoxButtons::OK, MessageBoxIcon::Information);

		if (!_settingsManager->writeConfigurationFile())
		{
			MessageBox::Show("Cant write", "path", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
	}
	

	_gui = gcnew GUI();
	_gui->setWinampServer(_winampServer);
	_gui->setSettingsManager(_settingsManager);
	_gui->setPort(_settingsManager->getPort());
	_gui->setShowOnStart(_settingsManager->getShowOnStart());
	if (_settingsManager->getShowOnStart())
		_gui->Show();

	_winampServer->setListenerWindow(_gui->getHandledWindow());
	_winampServer->setPort(_settingsManager->getPort());
	_winampServer->start();	
}

void AppManager::closeApp()
{
	_gui->Close();
}

void AppManager::showApp()
{
	_gui->Show();
}
