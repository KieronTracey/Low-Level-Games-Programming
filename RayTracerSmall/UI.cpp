#include "UI.h"

UI::UI()
{
}

UI::~UI()
{
}

//--------------------------------------------------//
//------------ Display functions for UI ------------//
//--------------------------------------------------//

void UI::DisplayMenu(vector<MenuOption> a_inputArray, string as_subTopic)
{
	//- initalising required Var -//
	bool lb_exitMenuLevel = false;
	int li_currentPage = 1;
	int li_menuOptionCount = 0;

	//- Loop till menu is exited -//
	while (!lb_exitMenuLevel)
	{
		//- Display Header With Pg Count
		PrintHeader(as_subTopic + " Pg: " + to_string(li_currentPage) + "/" + to_string((int)round(a_inputArray.size() / 7) + 1));

		//- Get the amount of outputs That needed to be displayed -//
		int li_ammountToLoop = ((a_inputArray.size() - ((li_currentPage - 1) * 7)) > 7) ? 7 : (a_inputArray.size() - ((li_currentPage - 1) * 7));
		//- Calculate the menu offset to get correct elements to read from vector-//
		li_menuOptionCount = (li_currentPage - 1) * 7;
		//- Displaying the 7 Dynamic Menu ELements and the 3 Hard Coded Elements -//
		for (int j = 1; j < li_ammountToLoop + 1; j++)
		{
			PrintText("Enter " + to_string(j) + " To: " + a_inputArray[li_menuOptionCount].MenuOutput);
			li_menuOptionCount++;
		}

		//- Hard Coded values for control functions to make it easier to program -//
		PrintText("Enter: 8 To: Return To The Previos Page Of Options");
		PrintText("Enter: 9 To: Go To The Next Page Of Options");
		PrintText("Enter: 0 To: Exit This Menu");
		PrintFooter();

		//- Getting the data from function to allow formating -//
		//- Input is kept as string insted of converting to int to prevent crashes if incorrect option is inputted -//
		//- when incorrect input is submitted the loop will role over without any issues for another try-//
		string ls_userInput = (GetUserInput<string>("Please Enter You Selection: "));

		//- Resetting Option Count to loop though elements to check if the conditions match -//
		li_menuOptionCount = (li_currentPage - 1) * 7;
		for (int j = 1; j < li_ammountToLoop + 1; j++)
		{
			//- check if the input matched menu element and its a subMenu element -//
			if (ls_userInput == to_string(j) && a_inputArray[li_menuOptionCount].SubMenuOptions.size() > 0)
			{
				//- if sub menu is selected the menu is called -//
				//- This calls its self again and again for menus which isnt the best but there arnt that many menu levels so is controllable-//
				DisplayMenu(a_inputArray[li_menuOptionCount].SubMenuOptions, a_inputArray[li_menuOptionCount].MenuOutput);
				cin.get();
				cin.get();
			}
			//- If the input then matches then function is called through saved void functions -//
			else if (ls_userInput == to_string(j))
			{
				a_inputArray[li_menuOptionCount].functionToRun();
				PrintFooter();
				cin.get();
				cin.get();
			}
			//- Keeps optionCount in sync -//
			li_menuOptionCount++;
		}

		//- li_toggle is a on off element for the maths as its only on when going down a page -//
		int li_toggle = 0;

		//- Only need to check first elelemt of the input string as all menu options are 0-9 -//
		switch (ls_userInput[0])
		{
		case '8':
			//- Check if move down is possible -//
			if (li_menuOptionCount > 7)
			{
				//- decriment menu count and togle on the extra maths -//
				li_menuOptionCount -= 7;
				li_toggle = 1;
			}
			break;

		case '9':
			//- Check if move up is possible, maths makes it useable for any size -//
			if (li_menuOptionCount <= ((ceil(a_inputArray.size() / 7) + 1) * 7))
			{
				//- increase count and toggle maths off -//
				li_menuOptionCount += 7;
				li_toggle = 0;
			}
			break;

		case '0':
			//- exit loop to return to next level -//
			lb_exitMenuLevel = true;
			break;
		}


		//- Altering current page count to be from 1-MAX insted of 0-MAX to prevent maths errors -//
		li_currentPage = ceil(li_menuOptionCount / 7) + li_toggle;
		if (li_currentPage == 0) { li_currentPage = 1; }
	}
}

void UI::DisplayMenu(vector<MenuOption> a_inputArray, string as_subTopic, void(*a_updateFunction)(), int* api_userSelectionRef)
{
	//--------------------------------------------------------------------------------//
	//------------ OVERRIDE FUNCTION with call back to Orignal Call Code -------------//
	//--------------------------------------------------------------------------------//

	//- initalising required Var -//
	bool lb_exitMenuLevel = false;
	int li_currentPage = 1;
	int li_menuOptionCount = 0;

	//- Loop till menu is exited -//
	while (!lb_exitMenuLevel)
	{
		//- Display Header With Pg Count
		PrintHeader(as_subTopic + " Pg: " + to_string(li_currentPage) + "/" + to_string((int)round(a_inputArray.size() / 7) + 1));

		//- Get the amount of outputs That needed to be displayed -//
		int li_ammountToLoop = ((a_inputArray.size() - ((li_currentPage - 1) * 7)) > 7) ? 7 : (a_inputArray.size() - ((li_currentPage - 1) * 7));
		//- Calculate the menu offset to get correct elements to read from vector-//
		li_menuOptionCount = (li_currentPage - 1) * 7;
		//- Displaying the 7 Dynamic Menu ELements and the 3 Hard Coded Elements -//
		for (int j = 1; j < li_ammountToLoop + 1; j++)
		{
			PrintText("Enter " + to_string(j) + " To: " + a_inputArray[li_menuOptionCount].MenuOutput);
			li_menuOptionCount++;
		}

		//- Hard Coded values for control functions to make it easier to program -//
		PrintText("Enter: 8 To: Return To The Previos Page Of Options");
		PrintText("Enter: 9 To: Go To The Next Page Of Options");
		PrintText("Enter: 0 To: Exit This Menu");
		PrintFooter();

		//- Getting the data from function to allow formating -//
		//- Input is kept as string insted of converting to int to prevent crashes if incorrect option is inputted -//
		//- when incorrect input is submitted the loop will role over without any issues for another try-//
		string ls_userInput = (GetUserInput<string>("Please Enter You Selection: "));

		//- Resetting Option Count to loop though elements to check if the conditions match -//
		li_menuOptionCount = (li_currentPage - 1) * 7;
		for (int j = 1; j < li_ammountToLoop + 1; j++)
		{
			//- check if the input matched menu element and its a subMenu element -//
			if (ls_userInput == to_string(j) && a_inputArray[li_menuOptionCount].SubMenuOptions.size() > 0)
			{
				//- if sub menu is selected the menu is called -//
				//- This calls its self again and again for menus which isnt the best but there arnt that many menu levels so is controllable-//
				DisplayMenu(a_inputArray[li_menuOptionCount].SubMenuOptions, a_inputArray[li_menuOptionCount].MenuOutput);
				cin.get();
				cin.get();
			}
			//- If the input then matches then function is called through saved void functions -//
			else if (ls_userInput == to_string(j))
			{
				//----->		//- Changed Element -//
				*api_userSelectionRef = li_menuOptionCount;
				a_updateFunction();
				//----->		//- End Of Change -//
				a_inputArray[li_menuOptionCount].functionToRun();
				PrintFooter();
				cin.get();
				cin.get();
			}
			//- Keeps optionCount in sync -//
			li_menuOptionCount++;
		}

		//- li_toggle is a on off element for the maths as its only on when going down a page -//
		int li_toggle = 0;

		//- Only need to check first elelemt of the input string as all menu options are 0-9 -//
		switch (ls_userInput[0])
		{
		case '8':
			//- Check if move down is possible -//
			if (li_menuOptionCount > 7)
			{
				//- decriment menu count and togle on the extra maths -//
				li_menuOptionCount -= 7;
				li_toggle = 1;
			}
			break;

		case '9':
			//- Check if move up is possible, maths makes it useable for any size -//
			if (li_menuOptionCount <= ((ceil(a_inputArray.size() / 7) + 1) * 7))
			{
				//- increase count and toggle maths off -//
				li_menuOptionCount += 7;
				li_toggle = 0;
			}
			break;

		case '0':
			//- exit loop to return to next level -//
			lb_exitMenuLevel = true;
			break;
		}


		//- Altering current page count to be from 1-MAX insted of 0-MAX to prevent maths errors -//
		li_currentPage = ceil(li_menuOptionCount / 7) + li_toggle;
		if (li_currentPage == 0) { li_currentPage = 1; }
	}
}

void UI::PrintText(string as_textToCentre)
{
	int li_centreOfText = (int)as_textToCentre.length() / 2;

	cout << "| " << std::setw(60 + li_centreOfText) << as_textToCentre << setw(59 - li_centreOfText) << "|\n";
}

Vec3f UI::GetUserInputVec3f(string as_inputMessage)
{
	PrintText(as_inputMessage);
	Vec3f l_dataInput;
	cin >> l_dataInput;
	return l_dataInput;
}

void UI::PrintHeader(string as_subTopic)
{
	clearInterface();

	cout << "|----------------------------------------------------------------------------------------------------------------------|\n";
	cout << "|                                     Low Level Games Programing Ray Traced Render                                     |\n";


	if (as_subTopic != "")
	{
		cout << "|----------------------------------------------------------------------------------------------------------------------|\n";
		PrintText(as_subTopic);
	}

	cout << "|----------------------------------------------------------------------------------------------------------------------|\n";
}

void UI::PrintFooter()
{
	cout << "|----------------------------------------------------------------------------------------------------------------------|\n";
}

void UI::clearInterface()
{
#if defined _WIN32
	system("cls");
#elif defined __linux__ || defined __APPLE__
	system("clear");
#endif
}

//-------------------------------------------------//
//------------ User Acsessed Functions ------------//
//-------------------------------------------------//

//- Void Wrappers -//
void multiplePagesWrapper() {};
void subMenuPagesWrapper() {};
void printTextWrapper() {};
void displayDataWrapper() {};
void displayErrorWrapper() {};
void getUserInputWrapper() {};

//- Member Functions -//
void UI::SettingsMenu()
{
	vector<MenuOption> l_menu;
	l_menu.push_back(MenuOption("UI Test Multiple Pages", multiplePagesWrapper));
	l_menu.push_back(MenuOption("UI Test Sub Menu", subMenuPagesWrapper));
	l_menu.push_back(MenuOption("UI Test Print Text", printTextWrapper));
	l_menu.push_back(MenuOption("UI Test Display Data", displayDataWrapper));
	l_menu.push_back(MenuOption("UI Test Display Error", displayErrorWrapper));
	l_menu.push_back(MenuOption("UI Test Get User Input", getUserInputWrapper));
	DisplayMenu(l_menu, "Settings Menu");
}