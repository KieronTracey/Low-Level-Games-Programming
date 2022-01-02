#include "UI.h"

void UI::DisplayMenu(vector<MenuOption> inputArray, string subTopic)
{
	bool exitMenu = false;
	int pageCount = 1;
	int menuOption = 0;

	while (!exitMenu)
	{
		Header(subTopic + " Page Number: " + to_string(pageCount) + " out of " + to_string((int)round(inputArray.size() / 7) + 1));

		int numToLoop = ((inputArray.size() - ((pageCount - 1) * 7)) > 7) ? 7 : (inputArray.size() - ((pageCount - 1) * 7));
		menuOption = (pageCount - 1) * 7;
		for (int i = 1; i < numToLoop + 1; i++)
		{
			OutputText("Input " + to_string(i) + " to go to " + inputArray[menuOption].MenuOptOutput);
			menuOption++;
		}

		OutputText("Input 8 to go to the previos page of options");
		OutputText("Input 9 to go to next page");
		OutputText("Input 0 to go back");
		OutputFooter();

		string userInput = (GetUserInput<string>("Input Selection: "));

		menuOption = (pageCount - 1) * 7;
		for (int x = 1; x < numToLoop + 1; x++)
		{
			if (userInput == to_string(x) && inputArray[menuOption].SubMenuOpt.size() > 0)
			{
				DisplayMenu(inputArray[menuOption].SubMenuOpt, inputArray[menuOption].MenuOptOutput);
				cin.get();
				cin.get();
			}
			else if (userInput == to_string(x))
			{
				inputArray[menuOption].functions();
				OutputFooter();
				cin.get();
				cin.get();
			}
			menuOption++;
		}

		int tog = 0;
		switch (userInput[0])
		{
		case '8':
			if (menuOption > 7)
			{
				menuOption -= 7;
				tog = 1;
			}
			break;

		case '9':
			if (menuOption <= ((ceil(inputArray.size() / 7) + 1) * 7))
			{
				menuOption += 7;
				tog = 0;
			}
			break;

		case '0':
			exitMenu = true;
			break;
		}

		pageCount = ceil(menuOption / 7) + tog;
		if (pageCount == 0) { pageCount = 1; }
	}
}

void UI::DisplayMenu(vector<MenuOption> inputArray, string subTopic, void(*a_updateFunction)(), int* api_userSelectionRef)
{
	bool exitMenu = false;
	int currentPg = 1;
	int menuOptions = 0;

	while (!exitMenu)
	{
		Header(subTopic + " Page Number " + to_string(currentPg) + " out of " + to_string((int)round(inputArray.size() / 7) + 1));
		int ammountToLoop = ((inputArray.size() - ((currentPg - 1) * 7)) > 7) ? 7 : (inputArray.size() - ((currentPg - 1) * 7));
		menuOptions = (currentPg - 1) * 7;

		for (int a = 1; a < ammountToLoop + 1; a++)
		{
			OutputText("Input " + to_string(a) + " to go to " + inputArray[menuOptions].MenuOptOutput);
			menuOptions++;
		}

		OutputText("Input 8 to go to the previos page of options");
		OutputText("Input 9 to go to next page");
		OutputText("Input 0 to go back");
		OutputFooter();

		string userInput = (GetUserInput<string>("Input Selection: "));

		menuOptions = (currentPg - 1) * 7;
		for (int n = 1; n < ammountToLoop + 1; n++)
		{
			if (userInput == to_string(n) && inputArray[menuOptions].SubMenuOpt.size() > 0)
			{
				DisplayMenu(inputArray[menuOptions].SubMenuOpt, inputArray[menuOptions].MenuOptOutput);
				cin.get();
				cin.get();
			}
			else if (userInput == to_string(n))
			{
				*api_userSelectionRef = menuOptions;
				a_updateFunction();
				inputArray[menuOptions].functions();
				OutputFooter();
				cin.get();
				cin.get();
			}
			menuOptions++;
		}
		int toggle = 0;

		switch (userInput[0])
		{
		case '8':
			if (menuOptions > 7)
			{
				menuOptions -= 7;
				toggle = 1;
			}
			break;

		case '9':
			if (menuOptions <= ((ceil(inputArray.size() / 7) + 1) * 7))
			{
				menuOptions += 7;
				toggle = 0;
			}
			break;

		case '0':
			exitMenu = true;
			break;
		}

		currentPg = ceil(menuOptions / 7) + toggle;
		if (currentPg == 0) { currentPg = 1; }
	}
}

void UI::OutputText(string centreText)
{
	int centreOfText = (int)centreText.length() / 2;

	cout << setw(60 + centreOfText) << centreText << setw(59 - centreOfText) << "\n";
}

Vec3f UI::UserInputVec3f(string inputMessage)
{
	OutputText(inputMessage);
	Vec3f dataInput;
	cin >> dataInput;
	return dataInput;
}

void UI::Header(string subTopic)
{
	CleanInterface();
	cout << "\n";
	if (subTopic != "")
	{
		OutputText(subTopic);
	}
}

void UI::OutputFooter()
{
	cout << " \n";
}

void UI::CleanInterface()
{
#if defined _WIN32
	system("cls");
#elif defined __linux__ || defined __APPLE__
	system("clear");
#endif
}

UI::UI()
{
}

UI::~UI()
{
}



void WWdisplayData()
{

};

void WWdisplayError()
{

};

void WWgetUserInput()
{

};

void WWmultiplePages()
{

};

void WWsubMenuPages()
{

};

void WWprintText()
{

};

void UI::WWSettingsMenu()
{
}