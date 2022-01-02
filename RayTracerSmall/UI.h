#ifndef _UI_H_
#define _UI_H_

#include "VecTemplate.h"
#include "MenuOption.h"

typedef Vector3<float> Vec3f;

class UI
{
public:

	void DisplayMenu(vector<MenuOption> inputArray, string subTopic);
	void DisplayMenu(vector<MenuOption> inputArray, string subTopic, void(*updateFunction)(), int* userSelectionRef);
	void Header(string subTopic);
	void OutputFooter();
	void CleanInterface();
	void OutputText(string textToCentre);
	Vec3f UserInputVec3f(string inputMessage);
	void WWSettingsMenu();

	template<typename Template>
	void OutputDataWithText(string text, Template data);
	template<typename Template>
	void OutputData(Template data);
	template<typename Template>
	void OutputError(Template data);
	template<typename Template>
	Template GetUserInput(string inputMessage);

	UI();
	~UI();
};

template<typename Template>
inline void UI::OutputData(Template data)
{
	std::ostringstream stringStream;
	stringStream << data;
	int centreOfText = (int)(stringStream.str().length()) >> 1;
	cout << "| " << setw((60 + centreOfText)) << stringStream.str() << setw(59 - centreOfText) << "|\n";
}



template<typename Template>
inline void UI::OutputDataWithText(string text, Template data)
{
	ostringstream stringStream;
	stringStream << data;
	string temp1 = text + stringStream.str();
	int centreOfText = (int)(temp1.length()) >> 1;
	cout << "| " << setw(60 + centreOfText) << temp1 << setw(59 - centreOfText) << "|\n";
}

template<typename Template>
inline void UI::OutputError(Template data)
{
	ostringstream stringStream;
	stringStream << data;
	int centreText = (int)(stringStream.str().length()) >> 1;
	cout << "| " << setw((60 + centreText)) << stringStream.str() << setw(59 - centreText) << "|\n";
	cout << setw((60 + centreText)) << "Press Enter To Continue: " << flush;
	cin.get();
	cin.get();
}

template<typename Template>
inline Template UI::GetUserInput(string inputMessage)
{
	int amountToCenter = 60 + (inputMessage.length() >> 1);
	cout << setw(amountToCenter) << inputMessage << flush;
	Template inputData;
	cin >> inputData;

	return (Template)inputData;
}

#endif