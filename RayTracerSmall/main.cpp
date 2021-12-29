// [header]
// A very basic raytracer example.
// [/header]
// [compile]
// c++ -o raytracer -O3 -Wall raytracer.cpp
// [/compile]
// [ignore]
// Copyright (C) 2012  www.scratchapixel.com
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
// [/ignore]

#include <stdlib.h>
#include <cstdio>
#include <cmath>
#include <fstream>
#include <vector>
#include <iostream>
#include <cassert>
// Windows only

#include <algorithm>
#include <sstream>
#include <string.h>

#include "SceneManager.h"
#include "MemoryManager.h"
#include "sphere.h"
#include "RenderingEngine.h"
#include "definitions.h"
#include "UI.h"

using namespace std;

UI* gp_ui;
SceneManager* gp_sceneManager;
RenderingEngine* gp_renderingEngine;

//- Void Function Wrappers for Menu System -//
void SceneManagerWrapper() { gp_sceneManager->Menu(); };
void UIWrapper() { gp_ui->SettingsMenu(); };
void DebuggerWrapper() { /*gp_debugger->Menu(); */ };
void RendererWrapper() { gp_renderingEngine->Menu(); };
void AnimationSettingsWrapper() {/*gp_animator->SettingsMenu()*/ };
//- End Of Wrappers-//

MemManager* MemoryManagerRef::memoryManager = new MemManager();

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);

	UI* lp_ui = new UI();
	gp_ui = lp_ui;

	SceneManager* lp_sceneManager = new SceneManager(lp_ui);
	gp_sceneManager = lp_sceneManager;

	RenderingEngine* lp_renderer = new RenderingEngine(lp_sceneManager, lp_ui);
	gp_renderingEngine = lp_renderer;

	//- Programs Main Menu -//
	vector<MenuOption> l_MainMenu;
	l_MainMenu.push_back(MenuOption("Scene Manager", SceneManagerWrapper));
	l_MainMenu.push_back(MenuOption("Renderer", RendererWrapper));
	l_MainMenu.push_back(MenuOption("Animation Settings", AnimationSettingsWrapper));
	l_MainMenu.push_back(MenuOption("Debugger / Profiler", DebuggerWrapper));
	l_MainMenu.push_back(MenuOption("UI Settings", UIWrapper));
	lp_ui->DisplayMenu(l_MainMenu, "Main Menu");

	system("ffmpeg -y -r 60 -f image2 -s 1920*1080 -i spheres%d.ppm -vcodec libx264 -crf 30 -pix_fmt yuv420p video/RaytracingOutput.mp4");

	return 0;
}

