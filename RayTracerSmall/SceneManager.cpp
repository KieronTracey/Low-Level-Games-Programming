#include "SceneManager.h"

SceneManager* manager;

void WWViewSceneInfo()
{
	manager->SceneInformation(); 
};

void WWLoadScene() 
{
	manager->LoadSceneFromJson(); 
};

void WWSaveScene() 
{
	manager->SaveSceneToJson(); 
};

void WWEditScene()
{
	manager->selectedSphere->UIchange(); 
};

void WWCreateSphere() 
{
	manager->CreateNewSphereOBJ(); 
};

void WWEditSpheres() 
{
	manager->EditSphereOBJ(); 
};

void WWUpdateScelectedObject() 
{
	manager->selectedSphere = manager->objectPresent[*manager->selectedObject]; 
};

void WWEditAnimationFPS() 
{
	manager->FPS = manager->Hui->GetUserInput<float>("Please input FPS: "); 
};

void WWEditAnimationDuriation() 
{
	manager->Length = manager->Hui->GetUserInput<int>("Please input duration: "); 
};

SceneManager::SceneManager(UI* UIRef)
{
	Hui = UIRef;
	SceneName = "Temp";
	manager = this;
	selectedObject = new int();
	*selectedObject = 0;
	Length = 1.0f;
	FPS = 30;
	loadFile = false;
}

SceneManager::~SceneManager()
{
	delete selectedObject;
	selectedObject = nullptr;
}

vector<Sphere*> SceneManager::FrameToBeRendered(int frameCount)
{
	return vector<Sphere*>();
}

void SceneManager::SceneInformation()
{
	Hui->Header("Current Scene Information");
	if (objectPresent.size() == 0)
	{
		Hui->OutputText("There is no scene currently loaded");
	}
	else
	{
		Hui->OutputDataWithText("Loaded Scene Name: ", SceneName);
		Hui->OutputDataWithText("objects in scene:: ", objectPresent.size());
	}
}

void SceneManager::LoadSceneFromJson()
{
	for (int i = 0; i < objectPresent.size(); i++)
	{
		delete objectPresent[i];
		objectPresent[i] = nullptr;
	}
	objectPresent.clear();

	json jsonF;
	ifstream jsonFileF;

	while (true)
	{
		SceneName = Hui->GetUserInput<string>("please input scene to load  ");
		jsonFileF.open("Scene Saves/" + SceneName + ".json");

		if (!jsonFileF.fail())
		{
			jsonFileF >> jsonF;
			loadFile = true;
			break;
		}
		Hui->OutputData<string>("No file by that name could be found, please input correct name");
	}

	FPS = jsonF["Animation FPS"];
	Length = jsonF["Animation Duriation"];

	for (int i = 0; i < jsonF["ObjectCount"]; i++)
	{
		Sphere* newSphere = new Sphere();
		newSphere->ConvertJSONtoOBJ(&jsonF, i);
		objectPresent.push_back(newSphere);
		newSphere = nullptr;
	}

}

void SceneManager::SaveSceneToJson()
{
	Hui->Header("Saving scene, please enter a name for the save");
	SceneName = Hui->GetUserInput<string>("Scene Name; ");
	json jsonF;
	jsonF["ObjectCount"] = objectPresent.size();
	jsonF["Animation FPS"] = FPS;
	jsonF["Animation Duriation"] = Length;
	for (int i = 0; i < objectPresent.size(); i++)
	{
		objectPresent[i]->ConvertOBJtoJSON(&jsonF, i);
	}
	ofstream jsonFileF("Scene Saves/" + SceneName + ".json");
	jsonFileF << jsonF << "\n";
}

void SceneManager::CreateNewSphereOBJ()
{
	Sphere* newSphere = new Sphere();
	newSphere->UIchange();
	objectPresent.push_back(newSphere);
	newSphere = nullptr;

	SaveSceneToJson();
}

void SceneManager::EditSphereOBJ()
{
	vector<MenuOption> menueditSceneMenu;
	for (int a = 0; a < objectPresent.size(); a++)
	{
		menueditSceneMenu.push_back(MenuOption(("Edit " + objectPresent[a]->OBJ_name + " :"), WWEditScene));
	}

	Hui->DisplayMenu(menueditSceneMenu, "Edit Elements", WWUpdateScelectedObject, selectedObject);
}

void SceneManager::SceneRefresh()
{
	for (int j = 0; j < objectPresent.size(); j++)
	{
		delete objectPresent[j];
		objectPresent[j] = nullptr;
	}
	objectPresent.clear();

	json jsonF;
	ifstream jsonFileF("Scene Saves/" + SceneName + ".json");
	jsonFileF >> jsonF;

	FPS = jsonF["Animation FPS"];
	Length = jsonF["Animation Duriation"];

	for (int n = 0; n < jsonF["ObjectCount"]; n++)
	{
		Sphere* newSphere = new Sphere();
		newSphere->ConvertJSONtoOBJ(&jsonF, n);
		objectPresent.push_back(newSphere);
		newSphere = nullptr;
	}
}

void SceneManager::Menus()
{
	vector<MenuOption> menuoptions;
	menuoptions.push_back(MenuOption("View scene information", WWViewSceneInfo));
	menuoptions.push_back(MenuOption("Load a scene", WWLoadScene));
	menuoptions.push_back(MenuOption("Save a scene", WWSaveScene));
	menuoptions.push_back(MenuOption("Edit scene elements", WWEditSpheres));
	menuoptions.push_back(MenuOption("Change Animations FPS", WWEditAnimationFPS));
	menuoptions.push_back(MenuOption("Create new sphere", WWCreateSphere));
	Hui->DisplayMenu(menuoptions, "Scene Manager");
}