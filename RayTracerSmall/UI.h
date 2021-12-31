//- Header Guard -//
#ifndef _UI_H_
#define _UI_H_

#include "MenuOption.h"
#include "VecTemplate.h"

//- Define for Vec3f Required at start of each header -//
typedef Vector3<float> Vec3f;

class UI
{
public:
	//- Manager Methods -//
	UI();
	~UI();

	//- User Acsessed -//
	void SettingsMenu();


	//- Developer Acsessed -//
	void DisplayMenu(vector<MenuOption> a_inputArray, string as_subTopic);
	void DisplayMenu(vector<MenuOption> a_inputArray, string as_subTopic, void(*a_updateFunction)(), int* api_userSelectionRef);
	void PrintHeader(string as_subTopic);
	void PrintFooter();
	void clearInterface();
	void PrintText(string as_textToCentre);
	Vec3f GetUserInputVec3f(string a_inputMessage);


	//- Templates -//
	template<typename Template>
	void PrintDataWithText(string a_text, Template a_data);
	template<typename Template>
	void PrintData(Template a_data);
	template<typename Template>
	void DisplayError(Template a_data);
	template<typename Template>
	Template GetUserInput(string a_inputMessage);


};

template<typename Template>
inline void UI::PrintData(Template a_data)
{
	//- Does cout operation to convert any type of data to a string which is then outputted -//
	std::ostringstream l_stringStream;
	l_stringStream << a_data;
	int li_centreOfText = (int)(l_stringStream.str().length()) >> 1;
	cout << "| " << std::setw((60 + li_centreOfText)) << l_stringStream.str() << setw(59 - li_centreOfText) << "|\n";
}

template<typename Template>
inline void UI::DisplayError(Template a_data)
{
	//- Does cout operation to convert any type of data to a string which is then outputted -//
	std::ostringstream l_stringStream;
	l_stringStream << a_data;
	int li_centreOfText = (int)(l_stringStream.str().length()) >> 1;
	cout << "| " << std::setw((60 + li_centreOfText)) << l_stringStream.str() << setw(59 - li_centreOfText) << "|\n";
	cout << std::setw((60 + li_centreOfText)) << "Please Press Enter To Continue: " << flush;
	cin.get();
	cin.get();
}

template<typename Template>
inline void UI::PrintDataWithText(string a_text, Template a_data)
{
	//- Does cout operation to convert any type of data to a string which is then outputted -//
	std::ostringstream l_stringStream;
	l_stringStream << a_data;
	string temp1 = a_text + l_stringStream.str();
	int centreOfText = (int)(temp1.length()) >> 1;
	cout << "| " << std::setw(60 + centreOfText) << temp1 << setw(59 - centreOfText) << "|\n";
}

template<typename Template>
inline Template UI::GetUserInput(string a_inputMessage)
{
	int li_amountToCenter = 60 + (a_inputMessage.length() >> 1);
	cout << setw(li_amountToCenter) << a_inputMessage << flush;
	Template l_inputData;
	cin >> l_inputData;

	return (Template)l_inputData;
}

#endif // !_UI_H