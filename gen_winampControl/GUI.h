#pragma once

#include <msclr\marshal_cppstd.h>
#include "WinampController.h"
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "Advapi32.lib")

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace msclr::interop;


namespace gen_winampControl {

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
		GUI(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			_winampController = new WinampController();
		}

	protected:
		WinampController* _winampController;
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~GUI()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  lblCommand;
	private: System::Windows::Forms::TextBox^  txtCommand;
	private: System::Windows::Forms::Label^  lblParam1;
	private: System::Windows::Forms::Label^  lblParam2;
	private: System::Windows::Forms::TextBox^  txtParam1;
	private: System::Windows::Forms::TextBox^  txtParam2;
	private: System::Windows::Forms::Button^  btnExecute;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  txtResult;


	protected: 


	protected: 

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
			this->lblCommand = (gcnew System::Windows::Forms::Label());
			this->txtCommand = (gcnew System::Windows::Forms::TextBox());
			this->lblParam1 = (gcnew System::Windows::Forms::Label());
			this->lblParam2 = (gcnew System::Windows::Forms::Label());
			this->txtParam1 = (gcnew System::Windows::Forms::TextBox());
			this->txtParam2 = (gcnew System::Windows::Forms::TextBox());
			this->btnExecute = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->txtResult = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// lblCommand
			// 
			this->lblCommand->AutoSize = true;
			this->lblCommand->Location = System::Drawing::Point(12, 12);
			this->lblCommand->Name = L"lblCommand";
			this->lblCommand->Size = System::Drawing::Size(54, 13);
			this->lblCommand->TabIndex = 0;
			this->lblCommand->Text = L"Command";
			// 
			// txtCommand
			// 
			this->txtCommand->Location = System::Drawing::Point(73, 9);
			this->txtCommand->Name = L"txtCommand";
			this->txtCommand->Size = System::Drawing::Size(168, 20);
			this->txtCommand->TabIndex = 1;
			// 
			// lblParam1
			// 
			this->lblParam1->AutoSize = true;
			this->lblParam1->Location = System::Drawing::Point(12, 39);
			this->lblParam1->Name = L"lblParam1";
			this->lblParam1->Size = System::Drawing::Size(43, 13);
			this->lblParam1->TabIndex = 2;
			this->lblParam1->Text = L"Param1";
			// 
			// lblParam2
			// 
			this->lblParam2->AutoSize = true;
			this->lblParam2->Location = System::Drawing::Point(12, 65);
			this->lblParam2->Name = L"lblParam2";
			this->lblParam2->Size = System::Drawing::Size(43, 13);
			this->lblParam2->TabIndex = 3;
			this->lblParam2->Text = L"Param2";
			// 
			// txtParam1
			// 
			this->txtParam1->Location = System::Drawing::Point(73, 36);
			this->txtParam1->Name = L"txtParam1";
			this->txtParam1->Size = System::Drawing::Size(168, 20);
			this->txtParam1->TabIndex = 4;
			// 
			// txtParam2
			// 
			this->txtParam2->Location = System::Drawing::Point(73, 62);
			this->txtParam2->Name = L"txtParam2";
			this->txtParam2->Size = System::Drawing::Size(168, 20);
			this->txtParam2->TabIndex = 5;
			// 
			// btnExecute
			// 
			this->btnExecute->Location = System::Drawing::Point(166, 88);
			this->btnExecute->Name = L"btnExecute";
			this->btnExecute->Size = System::Drawing::Size(75, 23);
			this->btnExecute->TabIndex = 6;
			this->btnExecute->Text = L"Execute";
			this->btnExecute->UseVisualStyleBackColor = true;
			this->btnExecute->Click += gcnew System::EventHandler(this, &GUI::btnExecute_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 124);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(37, 13);
			this->label1->TabIndex = 7;
			this->label1->Text = L"Result";
			// 
			// txtResult
			// 
			this->txtResult->Location = System::Drawing::Point(73, 121);
			this->txtResult->Name = L"txtResult";
			this->txtResult->Size = System::Drawing::Size(168, 20);
			this->txtResult->TabIndex = 8;
			// 
			// GUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(253, 165);
			this->Controls->Add(this->txtResult);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->btnExecute);
			this->Controls->Add(this->txtParam2);
			this->Controls->Add(this->txtParam1);
			this->Controls->Add(this->lblParam2);
			this->Controls->Add(this->lblParam1);
			this->Controls->Add(this->txtCommand);
			this->Controls->Add(this->lblCommand);
			this->Name = L"GUI";
			this->Text = L"GUI";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void btnExecute_Click(System::Object^  sender, System::EventArgs^  e);
	public: void setWinampController(WinampController* winampController);
};
}
