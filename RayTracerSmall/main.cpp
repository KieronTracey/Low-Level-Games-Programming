
#include <stdlib.h>
#include <cstdio>
#include <cmath>
#include <fstream>
#include <vector>
#include <iostream>
#include <cassert>

#include <algorithm>
#include <sstream>
#include <string.h>
#include "sphere.h"
#include "RenderingEngine.h"
#include "definitions.h"
#include "UI.h"
#include "SceneManager.h"
#include "MemoryManager.h"

UI* Mui;
SceneManager* MsceneManager;
RenderingEngine* MrenderingEngine;

void UIWrapper() { Mui->WWSettingsMenu(); };
void RendererWrapper() { MrenderingEngine->Menu(); };
void SceneManagerWrapper() { MsceneManager->Menus(); };


MemManager* MemoryManagerRef::memoryManager = new MemManager();

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);

	UI* mmui = new UI();
	Mui = mmui;

	SceneManager* msceneManager = new SceneManager(mmui);
	MsceneManager = msceneManager;

	RenderingEngine* mrenderer = new RenderingEngine(msceneManager, mmui);
	MrenderingEngine = mrenderer;

	vector<MenuOption> mMainMenu;
	mMainMenu.push_back(MenuOption("Scene Manager", SceneManagerWrapper));
	mMainMenu.push_back(MenuOption("Renderer", RendererWrapper));
	mmui->DisplayMenu(mMainMenu, "Main Menu");

	system("ffmpeg -y -r 60 -f image2 -s 1920*1080 -i spheres%d.ppm -vcodec libx264 -crf 30 -pix_fmt yuv420p video/RaytracingOutput.mp4");

	return 0;
}

