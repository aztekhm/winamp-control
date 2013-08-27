#include "StdAfx.h"
#include "GUI.h"

using namespace gen_winampControl;

System::Void GUI::btnExecute_Click(System::Object^  sender, System::EventArgs^  e) {
	String^ command = this->txtCommand->Text;
	String^ _param1 = this->txtParam1->Text;
	String^ _param2 = this->txtParam2->Text;
	
	std::string param1 = marshal_as<std::string>(_param1);
	std::string param2 = marshal_as<std::string>(_param2);


	if (command->Equals("extended")) {
		char artistName[256];
		int result = _winampController->getExtendedFileInfo(param1.c_str(), param2.c_str(), artistName, 256);
		this->txtResult->Text = gcnew String(artistName);

	} else if (command->Equals("play")) {
		_winampController->addToPlaylist(param1);
	}
}

void GUI::setWinampController(WinampController* winampController) {
	_winampController = winampController;
}