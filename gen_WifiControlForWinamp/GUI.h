#pragma once

#include <windows.h>
#include "WinampServer.h"
#include "WinampController.h"
#include "SettingsManager.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace gen_WifiControlForWinamp {

	/// <summary>
	/// Summary for GUI
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class GUI : public System::Windows::Forms::Form
	{
	public:
		GUI(void);

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~GUI();

		WinampServer* _winampServer;
		SettingsManager^ _settingsManager;
		


	private: System::Windows::Forms::GroupBox^  gboxStatus;
	private: System::Windows::Forms::Button^  btnStart;
	private: System::Windows::Forms::Button^  btnStop;
	private: System::Windows::Forms::Label^  lblStatus;
	private: System::Windows::Forms::GroupBox^  gboxSettings;
	private: System::Windows::Forms::Button^  btnSave;
	private: System::Windows::Forms::NumericUpDown^  numPort;

	private: System::Windows::Forms::Label^  lblListenPort;
	private: System::Windows::Forms::ListBox^  log;
	private: System::Windows::Forms::Button^  btnClear;
	private: System::Windows::Forms::GroupBox^  gboxLog;
	private: System::Windows::Forms::CheckBox^  checkShowWindow;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->gboxStatus = (gcnew System::Windows::Forms::GroupBox());
			this->btnStart = (gcnew System::Windows::Forms::Button());
			this->btnStop = (gcnew System::Windows::Forms::Button());
			this->lblStatus = (gcnew System::Windows::Forms::Label());
			this->gboxSettings = (gcnew System::Windows::Forms::GroupBox());
			this->btnSave = (gcnew System::Windows::Forms::Button());
			this->numPort = (gcnew System::Windows::Forms::NumericUpDown());
			this->lblListenPort = (gcnew System::Windows::Forms::Label());
			this->log = (gcnew System::Windows::Forms::ListBox());
			this->btnClear = (gcnew System::Windows::Forms::Button());
			this->gboxLog = (gcnew System::Windows::Forms::GroupBox());
			this->checkShowWindow = (gcnew System::Windows::Forms::CheckBox());
			this->gboxStatus->SuspendLayout();
			this->gboxSettings->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numPort))->BeginInit();
			this->gboxLog->SuspendLayout();
			this->SuspendLayout();
			// 
			// gboxStatus
			// 
			this->gboxStatus->Controls->Add(this->btnStart);
			this->gboxStatus->Controls->Add(this->btnStop);
			this->gboxStatus->Controls->Add(this->lblStatus);
			this->gboxStatus->Location = System::Drawing::Point(12, 12);
			this->gboxStatus->Name = L"gboxStatus";
			this->gboxStatus->Size = System::Drawing::Size(600, 47);
			this->gboxStatus->TabIndex = 0;
			this->gboxStatus->TabStop = false;
			this->gboxStatus->Text = L"Status";
			// 
			// btnStart
			// 
			this->btnStart->Location = System::Drawing::Point(438, 15);
			this->btnStart->Name = L"btnStart";
			this->btnStart->Size = System::Drawing::Size(75, 23);
			this->btnStart->TabIndex = 2;
			this->btnStart->Text = L"Start";
			this->btnStart->UseVisualStyleBackColor = true;
			this->btnStart->Click += gcnew System::EventHandler(this, &GUI::btnStart_Click);
			// 
			// btnStop
			// 
			this->btnStop->Location = System::Drawing::Point(519, 15);
			this->btnStop->Name = L"btnStop";
			this->btnStop->Size = System::Drawing::Size(75, 23);
			this->btnStop->TabIndex = 1;
			this->btnStop->Text = L"Stop";
			this->btnStop->UseVisualStyleBackColor = true;
			this->btnStop->Click += gcnew System::EventHandler(this, &GUI::btnStop_Click);
			// 
			// lblStatus
			// 
			this->lblStatus->AutoSize = true;
			this->lblStatus->Location = System::Drawing::Point(7, 20);
			this->lblStatus->Name = L"lblStatus";
			this->lblStatus->Size = System::Drawing::Size(126, 13);
			this->lblStatus->TabIndex = 0;
			this->lblStatus->Text = L"Server status unavailable";
			// 
			// gboxSettings
			// 
			this->gboxSettings->Controls->Add(this->checkShowWindow);
			this->gboxSettings->Controls->Add(this->btnSave);
			this->gboxSettings->Controls->Add(this->numPort);
			this->gboxSettings->Controls->Add(this->lblListenPort);
			this->gboxSettings->Location = System::Drawing::Point(12, 65);
			this->gboxSettings->Name = L"gboxSettings";
			this->gboxSettings->Size = System::Drawing::Size(600, 42);
			this->gboxSettings->TabIndex = 1;
			this->gboxSettings->TabStop = false;
			this->gboxSettings->Text = L"Settings";
			// 
			// btnSave
			// 
			this->btnSave->Location = System::Drawing::Point(519, 11);
			this->btnSave->Name = L"btnSave";
			this->btnSave->Size = System::Drawing::Size(75, 23);
			this->btnSave->TabIndex = 2;
			this->btnSave->Text = L"Save";
			this->btnSave->UseVisualStyleBackColor = true;
			this->btnSave->Click += gcnew System::EventHandler(this, &GUI::btnSave_Click);
			// 
			// numPort
			// 
			this->numPort->Location = System::Drawing::Point(70, 14);
			this->numPort->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1000, 0, 0, 0});
			this->numPort->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {100, 0, 0, 0});
			this->numPort->Name = L"numPort";
			this->numPort->Size = System::Drawing::Size(120, 20);
			this->numPort->TabIndex = 1;
			this->numPort->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {100, 0, 0, 0});
			// 
			// lblListenPort
			// 
			this->lblListenPort->AutoSize = true;
			this->lblListenPort->Location = System::Drawing::Point(7, 16);
			this->lblListenPort->Name = L"lblListenPort";
			this->lblListenPort->Size = System::Drawing::Size(57, 13);
			this->lblListenPort->TabIndex = 0;
			this->lblListenPort->Text = L"Listen Port";
			// 
			// log
			// 
			this->log->FormattingEnabled = true;
			this->log->Location = System::Drawing::Point(10, 19);
			this->log->Name = L"log";
			this->log->Size = System::Drawing::Size(503, 290);
			this->log->TabIndex = 2;
			// 
			// btnClear
			// 
			this->btnClear->Location = System::Drawing::Point(519, 19);
			this->btnClear->Name = L"btnClear";
			this->btnClear->Size = System::Drawing::Size(75, 23);
			this->btnClear->TabIndex = 3;
			this->btnClear->Text = L"Clear log";
			this->btnClear->UseVisualStyleBackColor = true;
			this->btnClear->Click += gcnew System::EventHandler(this, &GUI::btnClear_Click);
			// 
			// gboxLog
			// 
			this->gboxLog->Controls->Add(this->log);
			this->gboxLog->Controls->Add(this->btnClear);
			this->gboxLog->Location = System::Drawing::Point(12, 113);
			this->gboxLog->Name = L"gboxLog";
			this->gboxLog->Size = System::Drawing::Size(600, 317);
			this->gboxLog->TabIndex = 4;
			this->gboxLog->TabStop = false;
			this->gboxLog->Text = L"Log";
			// 
			// checkShowWindow
			// 
			this->checkShowWindow->AutoSize = true;
			this->checkShowWindow->Location = System::Drawing::Point(221, 15);
			this->checkShowWindow->Name = L"checkShowWindow";
			this->checkShowWindow->Size = System::Drawing::Size(207, 17);
			this->checkShowWindow->TabIndex = 3;
			this->checkShowWindow->Text = L"Show this window when winamp starts";
			this->checkShowWindow->UseVisualStyleBackColor = true;
			// 
			// GUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(624, 442);
			this->Controls->Add(this->gboxLog);
			this->Controls->Add(this->gboxSettings);
			this->Controls->Add(this->gboxStatus);
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"GUI";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Wifi Control for Winamp";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &GUI::GUI_FormClosing);
			this->gboxStatus->ResumeLayout(false);
			this->gboxStatus->PerformLayout();
			this->gboxSettings->ResumeLayout(false);
			this->gboxSettings->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numPort))->EndInit();
			this->gboxLog->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void GUI_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e);
	private: System::Void btnStart_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void btnStop_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void btnSave_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void btnClear_Click(System::Object^  sender, System::EventArgs^  e);
	protected: virtual void WndProc(System::Windows::Forms::Message% m) override;
	public: void setWinampServer(WinampServer* winampServer);
	public: void setSettingsManager(SettingsManager^ settingsManager);
	public: HWND getHandledWindow();
	public: void setPort(int port);
	public: int getPort();
	public: void setShowOnStart(bool checked);
	public: bool getShowOnStart();
	};
}
