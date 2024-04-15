#pragma once
#include<wx/wx.h>
class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);

private : 
	void OnButtonClickedBtn0(wxCommandEvent& evt);
	void OnButtonClickedBtn1(wxCommandEvent& evt);
	void OnButtonClickedBtn2(wxCommandEvent& evt);
	void OnButtonClickedBtn3(wxCommandEvent& evt);
	void OnButtonClickedBtn4(wxCommandEvent& evt);
	void OnButtonClickedBtn5(wxCommandEvent& evt);
	void OnButtonClickedBtn6(wxCommandEvent& evt);
	void OnButtonClickedBtn7(wxCommandEvent& evt);
	void OnButtonClickedBtn8(wxCommandEvent& evt);
	void OnButtonClickedBtn9(wxCommandEvent& evt);
	
	void OnButtonClickedComma(wxCommandEvent& evt);
	void OnButtonClickedDel(wxCommandEvent& evt);
	void OnButtonClickedDivide(wxCommandEvent& evt);
	void OnButtonClickedMulti(wxCommandEvent& evt);
	void OnButtonClickedMinus(wxCommandEvent& evt);
	void OnButtonClickedPlus(wxCommandEvent& evt);
	void OnButtonClickedEqual(wxCommandEvent& evt);

	/***************************************************************/
	bool isDigit(char s);
	bool CheckPlus(wxString s);
	bool CheckMinus(wxString s);
	bool CheckMulti(wxString s);
	bool CheckDivide(wxString s);
	bool CheckComma(wxString s);
	bool CheckMakeSense(wxString s);

	/***************************************************************/
	int getAnswer(wxString express);
	int BasicCalculate(wxString express);
	int StringToInt(wxString express);
	wxString IntTowxString(int num);
	wxString DoubleSign(wxString ans);
	wxString ConvertToWxString( std::string& str);
	wxDECLARE_EVENT_TABLE();

};


