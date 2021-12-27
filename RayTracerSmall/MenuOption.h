#pragma once
#include <string>
#include <vector>
using namespace std;

struct MenuOption
{
	MenuOption() {};

	MenuOption(string MenOutput, void(*funcToRun)())
	{
		MenuOutput = MenOutput;
		functionToRun = funcToRun;
	};

	MenuOption(string MenOutput, vector<MenuOption> SubMenu)
	{
		MenuOutput = MenOutput;
		SubMenuOptions = SubMenu;
		functionToRun = nullptr;
	};

	string MenuOutput;

	void(*functionToRun)();

	vector<MenuOption> SubMenuOptions;
};