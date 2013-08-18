#include "StdAfx.h"
#include "GUI.h"

using namespace gen_WifiControlForWinamp;

GUI::GUI() 
{
	InitializeComponent();
}

GUI::~GUI()
{
	if (components)
	{
		delete components;
	}
}

System::Void GUI::GUI_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) 
{
	// Cuando el usuario cierra la ventana, esta solo se oculta
	if (e->CloseReason == System::Windows::Forms::CloseReason::UserClosing) 
	{
		Hide();
		e->Cancel = true;
	}
}

System::Void GUI::btnStart_Click(System::Object^  sender, System::EventArgs^  e) 
{
	// Inicio del server
	_winampServer->start();
}

System::Void GUI::btnStop_Click(System::Object^  sender, System::EventArgs^  e) 
{
	// Apagado del server
	_winampServer->stop();
}

System::Void GUI::btnSave_Click(System::Object^  sender, System::EventArgs^  e) 
{
	// Guarda las preferencias y reinicia el server si el puerto se cambio
	int oldPort = _settingsManager->getPort();
	_settingsManager->setPort(getPort());
	_settingsManager->setShowOnStart(getShowOnStart());

	if (_settingsManager->writeConfigurationFile())
	{
		String^ message = gcnew String("Settings saved successfull");
		if (_settingsManager->getPort() != oldPort)
			message += "\nServer will restart";

		MessageBox::Show(message, "Information", MessageBoxButtons::OK, MessageBoxIcon::Information);
		if (_settingsManager->getPort() != oldPort)
		{
			_winampServer->stop();
			_winampServer->setPort(getPort());
			_winampServer->start();
		}
	}
	else
	{
		MessageBox::Show("Cannot save settings\nPlease retry", "Information", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}

}

System::Void GUI::btnClear_Click(System::Object^  sender, System::EventArgs^  e) 
{
	this->log->Items->Clear();
}

HWND GUI::getHandledWindow() 
{
	return static_cast<HWND>(this->Handle.ToPointer());
}

void GUI::WndProc(System::Windows::Forms::Message% m) 
{
	if (m.Msg == WM_COPYDATA) {
		COPYDATASTRUCT *data = (COPYDATASTRUCT*)m.LParam.ToPointer();
		String^ msg = gcnew String((char*)data->lpData);

		switch ((int)data->dwData) {
			case 777:
				lblStatus->Text = msg;
				log->Items->Add(msg);
				break;
				
			case 666:
				log->Items->Add(msg);
				break;
		}
	} else {
		Form::WndProc(m);
	}
}

void GUI::setWinampServer(WinampServer* winampServer)
{
	this->_winampServer = winampServer;
}

void GUI::setSettingsManager(SettingsManager^ settingsManager)
{
	this->_settingsManager = settingsManager;
}

void GUI::setPort(int port)
{
	this->numPort->Value = port;
}

int GUI::getPort()
{
	return Decimal::ToInt32(numPort->Value);
}

void GUI::setShowOnStart(bool checked)
{
	this->checkShowWindow->Checked = checked;
}

bool GUI::getShowOnStart()
{
	return this->checkShowWindow->Checked;
}
