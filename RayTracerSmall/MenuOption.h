#pragma once
#include <string>
#include <vector>
using namespace std;

struct MenuOption
{
	string MenuOptOutput;

	MenuOption(string MenOutput, void(*funcToRun)())
	{
		MenuOptOutput = MenOutput;
		functions = funcToRun;
	};

	MenuOption(string MenOutput, vector<MenuOption> SubMenu)
	{
		MenuOptOutput = MenOutput;
		SubMenuOpt = SubMenu;
		functions = nullptr;
	};



	void(*functions)();

	vector<MenuOption> SubMenuOpt;
};