#pragma once
#include "MainFrame.h"
#include "wx/string.h"
#include<wx/wx.h>
#include <format>
#include<iostream>
#include <regex>
#include <string>
#include <stack>
#include <sstream>

enum Button {
	BTID0 = 0,              // 0
	BTID1 = 1,              // 1
	BTID2 = 2,              // 2
	BTID3 = 3,              // 3
	BTID4 = 4,              // 4
	BTID5 = 5,              // 5
	BTID6 = 6,              // 6
	BTID7 = 7,              // 7
	BTID8 = 8,              // 8
	BTID9 = 9,              // 9

	COMMA = 11,             // ,
	DEL = 22,			   // DEL
	DIVIDE = 44,            // %
	MULTI = 55,             // X
	MINOR = 66,             // -
	PLUS = 77,              // +
	EQUAL = 88              // =
	
	};

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_BUTTON(BTID0, MainFrame::OnButtonClickedBtn0)
EVT_BUTTON(BTID1, MainFrame::OnButtonClickedBtn1)
EVT_BUTTON(BTID2, MainFrame::OnButtonClickedBtn2)
EVT_BUTTON(BTID3, MainFrame::OnButtonClickedBtn3)
EVT_BUTTON(BTID4, MainFrame::OnButtonClickedBtn4)
EVT_BUTTON(BTID5, MainFrame::OnButtonClickedBtn5)
EVT_BUTTON(BTID6, MainFrame::OnButtonClickedBtn6)
EVT_BUTTON(BTID7, MainFrame::OnButtonClickedBtn7)
EVT_BUTTON(BTID8, MainFrame::OnButtonClickedBtn8)
EVT_BUTTON(BTID9, MainFrame::OnButtonClickedBtn9)
EVT_BUTTON(COMMA, MainFrame::OnButtonClickedComma)
EVT_BUTTON(DEL, MainFrame::OnButtonClickedDel)
EVT_BUTTON(DIVIDE, MainFrame::OnButtonClickedDivide)
EVT_BUTTON(MULTI, MainFrame::OnButtonClickedMulti)
EVT_BUTTON(MINOR, MainFrame::OnButtonClickedMinus)
EVT_BUTTON(PLUS, MainFrame::OnButtonClickedPlus)
EVT_BUTTON(EQUAL, MainFrame::OnButtonClickedEqual)
wxEND_EVENT_TABLE();

wxString express = "";
wxTextCtrl* expression; wxButton* btnEqual; wxButton* btnPlus; wxButton* btnMinus; wxButton* btnMulti; wxButton* btnComma; wxButton* btnDivide; wxButton* del;
wxButton* btn0; wxButton* btn1; wxButton* btn2; wxButton* btn3; wxButton* btn4; wxButton* btn5; wxButton* btn6; wxButton* btn7; wxButton* btn8; wxButton* btn9;

std::string Format(std::string express) {

	std::string main = "";
	//12+34-56/+78       --> 12 + 34 - 56 /+78     //11+22/ 33*44 / +55    --> 11 + 22 - 33 * +44 / -55 /66 

	main += express[0];       // luoon co dau o dau
	
	for (int i = 1; i < express.length(); i++) {

		if (isdigit(express[i])) {            // là số thì cứ cộng
			main += express[i];

		}
		else {
			//         main += " ";
			// 		main += express[i];

			if (isdigit(express[i + 1]) && isdigit(express[i - 1])) { //neu truoc va sau no deu la so thi cong khoang trang 2 ben
				main = main + " ";
				main = main + express[i];
				main = main + " ";
			}
			else {
				main = main + " ";
				main = main + express[i];
			}

		}
	}
	return main;
}
int Precedence(char op) {
	return (op == '+' || op == '-') ? 1 : 2;
}

int MiniCal(int a, int b, char op) {

	try {
		switch (op) {
		case '+': return a + b;
		case '-': return a - b;
		case '*': return a * b;
		case ':':
			if (b == 0) {
				throw std::runtime_error("Cannot divide by zero.");
			}
			return a / b;
		default:
			throw std::invalid_argument("Invalid operator used.");
		}
	}
	catch (const std::runtime_error& e) {
		std::cerr << "Runtime Error: " << e.what() << std::endl;
		return 0;  // Return a default value or handle differently
	}
	catch (const std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
		return 0;  // Return a default value or handle differently
	}
}


int getStreamLength(std::stringstream& ss) {
	// Lưu lại vị trí hiện tại của stringstream
	std::streampos currentPosition = ss.tellg();

	// Đặt vị trí đọc tại đầu stringstream
	ss.seekg(0, std::ios::beg);

	// Tính toán độ dài của stringstream
	std::streampos beginPosition = ss.tellg();
	ss.seekg(0, std::ios::end);
	std::streampos endPosition = ss.tellg();

	// Khôi phục vị trí đọc ban đầu của stringstream
	ss.seekg(currentPosition, std::ios::beg);

	// Trả về độ dài của stringstream
	return static_cast<int>(endPosition - beginPosition);
}
int Cal(std::string s) {

	
	std::stack<int>numbers;
	std::stack<char>ops;
	std::string abc = s;
	std::stringstream t(abc);
	std::stringstream ss(s);
	if (getStreamLength(t) == 1) {
		std::string temp;
		while (ss >> temp)
			return stoi(temp);
	}
	
	
	std::string temp;

	int precedence = 1;
	
	char op ;
	int ans = 0;


	try {
		while (ss >> temp) {
			
			if (temp.size() > 1)       //object co size > 1 ==> so 
				numbers.push(stoi(temp));
			else {         //dau 
				char op = temp[0]; //op la dau thi lay ra ki tu dau tien cung nhu cuoi cung
				if (isdigit(op)) {
					numbers.push(stoi(temp));
				}
				else {

					while (!ops.empty() && Precedence(ops.top()) >= Precedence(op)) {
						int n2 = numbers.top(); numbers.pop();
						int n1 = numbers.top(); numbers.pop();
						char op = ops.top(); ops.pop();
						numbers.push(MiniCal(n1, n2, op));
						//luon lay n1 op n2 : tranh dau tru` 
					}
					//neu op empty thi them dau vao
					ops.push(op);
				}
			}
		}
		op = ops.top();
		while (!ops.empty() && Precedence(ops.top()) <= Precedence(op)) {
			int n2 = numbers.top(); numbers.pop();
			int n1 = numbers.top(); numbers.pop();
			int sign = ops.top(); ops.pop();
			numbers.push(MiniCal(n1, n2, sign));
			//luon lay n1 op n2 : tranh dau tru` 
		}
	}
	catch (const std::invalid_argument& e) {
		std::cerr << "Invalid argument error: " << e.what() << std::endl;
		return 0;
	}
	catch (...) {
		std::cerr << "An unknown error occurred." << std::endl;
		return 0;
	}


	return numbers.top();
}

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {

/************************************* init **************************/
	wxPanel* panel = new wxPanel(this);
	int x = 400;
	int y = 500;
	
	wxFont font(25, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	wxFont font1(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	 expression = new wxTextCtrl (panel, wxID_ANY, express , wxPoint(0, 0), wxSize(300, 100), wxTE_READONLY);
	expression->SetFont(font1);
	expression->SetMaxLength(9);
	wxButton* btnEqual = new wxButton(panel, EQUAL, "=", wxPoint(300, y-500), wxSize(100, 100));
	 btn7 = new wxButton(panel, BTID7, "7", wxPoint(0, y-400), wxSize(100, 100));
	 btn8 = new wxButton(panel, BTID8, "8", wxPoint(100, y - 400), wxSize(100, 100));
	 btn9 = new wxButton(panel, BTID9, "9", wxPoint(200, y - 400), wxSize(100, 100));
	 btnPlus = new wxButton(panel, PLUS, "+", wxPoint(300, y - 400), wxSize(100, 100));

	 btn4 = new wxButton(panel, BTID4, "4", wxPoint(0, y - 300), wxSize(100, 100));
	btn5 = new wxButton(panel, BTID5, "5", wxPoint(100, y - 300), wxSize(100, 100));	
	 btn6 = new wxButton(panel, BTID6, "6", wxPoint(200, y - 300), wxSize(100, 100));
	btnMinus = new wxButton(panel, MINOR, "-", wxPoint(300, y - 300), wxSize(100, 100));

	 btn1 = new wxButton(panel, BTID1, "1", wxPoint(0, y - 200), wxSize(100, 100));
	 btn2 = new wxButton(panel, BTID2, "2", wxPoint(100, y - 200), wxSize(100, 100));
	 btn3 = new wxButton(panel, BTID3, "3", wxPoint(200, y - 200), wxSize(100, 100));
	 btnMulti = new wxButton(panel, MULTI, "x", wxPoint(300, y - 200), wxSize(100, 100));

	 btnComma = new wxButton(panel, COMMA, "DA", wxPoint(0, y - 100), wxSize(100, 100));
	 btn0 = new wxButton(panel, BTID0, "0", wxPoint(100, y - 100), wxSize(100, 100));
	 del = new wxButton(panel, DEL, "DEL", wxPoint(200, y - 100), wxSize(100, 100));
	 btnDivide = new wxButton(panel, DIVIDE, ":", wxPoint(300, y - 100), wxSize(100, 100));

}
/********************************************************/

int	 MainFrame::StringToInt(wxString express) {
	int Converted = 0;
	for (int i = 0; i < express.length(); i++) {
		if (express[i] >= '0' && express[i] <= '9') {
			Converted = Converted * 10 + (express[i] - '0');
		}
		
	}
	return Converted;
}

wxString MainFrame::IntTowxString(int num) {
	// Sử dụng phương thức Format() của lớp wxString để chuyển đổi số nguyên thành wxString
	return wxString::Format(wxT("%d"), num);

}
wxString MainFrame::ConvertToWxString( std::string& str) {
	return wxString::FromUTF8(str.c_str());
}
wxString MainFrame::DoubleSign(wxString express) {
	std::string temp = express.ToStdString();   //regex không thể sử lí wxString nên phải cv thành string
	temp = std::regex_replace(temp, std::regex("--"), "+");
	temp = std::regex_replace(temp, std::regex("\\+\\+"), "+");
	temp = std::regex_replace(temp, std::regex("-\\+"), "-");
	temp = std::regex_replace(temp, std::regex("\\+-"), "-");
	temp = std::regex_replace(temp, std::regex("x"), "*");
	express = ConvertToWxString(temp);
	return express;
}

/**************  button *****************************/
void MainFrame::OnButtonClickedEqual(wxCommandEvent& evt) {
		

		/**
		4 buoc clean :
		 1. double sign -+ +- -- ++
		 2. khong phai error
		 3. tach thanh chuoi stream
		 4. tinh toan tra ve
		 ***note : wxString phai duoc doi thanh String va String phai duoc doi thanh wxString
		**/
	try {
		 
		express = '+' + express;		// dấu + thêm vào đầu để xét dấu   
		if (express.length() == 2) express = express + '+';
		express = DoubleSign(express);																			//b1: 12-34*56+78-90
		bool check = CheckPlus(express) * CheckMinus(express) * CheckMulti(express) * CheckDivide(express);		//b2: 12+-34*56--78+-90	

		if (check) {

			std::string temp = Format(express.ToStdString());													//b3: 12 - 34 * 56 + 78 - 90;
			
				
				int ans = Cal(temp);
				express = IntTowxString(ans);
		}
		else {
			express = "ERROR";
		}
		
	}
	catch (...) {
		
			std::cerr << "An unknown error occurred." << std::endl;
			

	}
	expression->SetValue(express);

}
void MainFrame::OnButtonClickedBtn0(wxCommandEvent& evt) {
	express += "0";
	expression->SetValue(express);
}
void MainFrame::OnButtonClickedBtn1(wxCommandEvent& evt) {
	express += "1";
	expression->SetValue(express);
}
void MainFrame::OnButtonClickedBtn2(wxCommandEvent& evt) {
	express += "2";
	expression->SetValue(express);
}
void MainFrame::OnButtonClickedBtn3(wxCommandEvent& evt) {
	express += "3";
	expression->SetValue(express);
}
void MainFrame::OnButtonClickedBtn4(wxCommandEvent& evt) {
	express += "4";
	expression->SetValue(express);
}
void MainFrame::OnButtonClickedBtn5(wxCommandEvent& evt) {
	express += "5";
	expression->SetValue(express);
}
void MainFrame::OnButtonClickedBtn6(wxCommandEvent& evt) {
	express += "6";
	expression->SetValue(express);
}
void MainFrame::OnButtonClickedBtn7(wxCommandEvent& evt) {
	express += "7";
	expression->SetValue(express);
}
void MainFrame::OnButtonClickedBtn8(wxCommandEvent& evt) {
	express += "8";
	expression->SetValue(express);
}
void MainFrame::OnButtonClickedBtn9(wxCommandEvent& evt) {
	express += "9";
	expression->SetValue(express);
}
void MainFrame::OnButtonClickedComma(wxCommandEvent& evt) {
	express = "";
	expression->SetValue(express);
}
void MainFrame::OnButtonClickedDel(wxCommandEvent& evt) {
	
		express.erase(express.size() - 1);
		expression->SetValue(express);
		
}
void MainFrame::OnButtonClickedDivide(wxCommandEvent& evt) {
	express += ":";
	expression->SetValue(express);
}

void MainFrame::OnButtonClickedMulti(wxCommandEvent& evt) {
	express += "x";
	expression->SetValue(express);

}
void MainFrame::OnButtonClickedMinus(wxCommandEvent& evt) {
	express += "-";
	expression->SetValue(express);

}
void MainFrame::OnButtonClickedPlus(wxCommandEvent& evt) {
	express += "+";
	expression->SetValue(express);

}



//////////////////////////////////

bool MainFrame::CheckMakeSense(wxString express) {

	if (express.length() == 2) return false;
	wxString s = express.substr(1);
	for (int i = 0; i < s.length(); i++) {

	}
}
bool MainFrame::isDigit(char s) {
	return (s >= '0' && s <= '9');
}

bool MainFrame::CheckPlus(wxString s) {
	try { //express = +3+
		if (s.size() <= 1) return false;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == '+') {
				if (i == s.size() - 1 || s[i + 1] == 'x' || s[i + 1] == ':' ) {
					return false;
				}
			}
		}
		return true;
	}
	catch (const std::exception& e) {
		// Xử lý ngoại lệ ở đây (ví dụ: ghi log, thông báo người dùng...)
		return false; // Trả về false nếu có ngoại lệ xảy ra
	}
	catch (...) {
		expression->SetValue("Error in expression");
		return false;
	}
}
bool MainFrame::CheckMinus(wxString s) {
	try {
		if (s.size() <= 1) return false;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == '-') {
				if (i == s.size() - 1 || s[i + 1] == 'x' || s[i + 1] == ':' ) {
					return false;
				}
			}
		}
		return true;
	}
	catch (const std::exception& e) {
		// Xử lý ngoại lệ ở đây (ví dụ: ghi log, thông báo người dùng...)
		return false; // Trả về false nếu có ngoại lệ xảy ra
	}
	catch (...) {
		expression->SetValue("Error in expression");
		return false;
	}
}
bool MainFrame::CheckMulti(wxString s) {
	try {
		if (s.size() <= 1) return false;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == '*') {
				if (i == s.size() - 1 || s[i + 1] == 'x' || s[i + 1] == ':' ) {
					return false;
				}
			}
		}
		return true;
	}
	catch (const std::exception& e) {
		// Xử lý ngoại lệ ở đây (ví dụ: ghi log, thông báo người dùng...)
		return false; // Trả về false nếu có ngoại lệ xảy ra
	}
	catch (...) {
		expression->SetValue("Error in expression");
		return false;
	}
}
bool MainFrame::CheckDivide(wxString s) {
	try {
		if (s.size() <= 1) return false;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == ':') {
				if (i == s.size() - 1 || s[i + 1] == 'x' || s[i + 1] == ':'   ) {
					return false;
				}
			}
		}
		return true;
	}
	catch (const std::exception& e) {
		// Xử lý ngoại lệ ở đây (ví dụ: ghi log, thông báo người dùng...)
		return false; // Trả về false nếu có ngoại lệ xảy ra
	}
	catch (...) {
		expression->SetValue("Error in expression");
		return false;
	}
}

