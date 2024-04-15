#include "App.h"
#include "MainFrame.h"
#include<wx/wx.h>

wxIMPLEMENT_APP(App);
bool App::OnInit() {
	MainFrame* mainframe = new MainFrame("Calculator");
	mainframe->SetClientSize(400, 500);
	mainframe->Center();
	mainframe->Show();
	return true;

}