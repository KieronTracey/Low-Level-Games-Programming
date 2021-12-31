#include "SceneManager.h"

SceneManager* gp_selfSceneManager;

//------------------------------------------- Void Wrappers for Menu System -----------------------------------//
//- Function Wrappers For MenuFunction -//
void ViewSceneInfoWrapper() { gp_selfSceneManager->ViewSceneInfo(); };
void LoadSceneWrapper() { gp_selfSceneManager->LoadScene(); };
void SaveSceneWrapper() { gp_selfSceneManager->SaveScene(); };
void EditSceneWrapper() { gp_selfSceneManager->mp_currentlySelected->UIchange(); };
void CreateSphereWrapper() { gp_selfSceneManager->CreateNewSphere(); };
void EditSpheresWrapper() { gp_selfSceneManager->EditSpheres(); };
void UpdateScelectedObjectWrapper() { gp_selfSceneManager->mp_currentlySelected = gp_selfSceneManager->objectsInScene[*gp_selfSceneManager->mpi_selectedObjectToEdit]; };
void EditAnimationFPSWrapper() { gp_selfSceneManager->sceneFPS = gp_selfSceneManager->mp_ui->GetUserInput<float>("Enter FPS: "); };
void EditAnimationDuriationWrapper() { gp_selfSceneManager->sceneLength = gp_selfSceneManager->mp_ui->GetUserInput<int>("Enter Duriation: "); };

SceneManager::SceneManager(UI* ap_uiRef)
{
	mp_ui = ap_uiRef;
	ms_sceneName = "Temp Scene Name";
	gp_selfSceneManager = this;
	mpi_selectedObjectToEdit = new int();
	*mpi_selectedObjectToEdit = 0;
	sceneLength = 1.0f;
	sceneFPS = 30;
	fileLoaded = false;
}

SceneManager::~SceneManager()
{
	delete mpi_selectedObjectToEdit;
	mpi_selectedObjectToEdit = nullptr;
}

vector<Sphere*> SceneManager::GetFrameToRender(int frameCount)
{
	return vector<Sphere*>();
}

void SceneManager::ViewSceneInfo()
{
	mp_ui->PrintHeader("Scene Info");
	if (objectsInScene.size() == 0)
	{
		mp_ui->PrintText("No scene loaded please load a scene from the Scene Manager Menu");
	}
	else
	{
		mp_ui->PrintDataWithText("Current Scene Name: ", ms_sceneName);
		mp_ui->PrintDataWithText("Amount of objects in the scene: ", objectsInScene.size());
	}
}

void SceneManager::LoadScene()
{
	for (int i = 0; i < objectsInScene.size(); i++)
	{
		delete objectsInScene[i];
		objectsInScene[i] = nullptr;
	}
	objectsInScene.clear();

	json l_json;
	ifstream l_jsonFile;

	while (true)
	{
		ms_sceneName = mp_ui->GetUserInput<string>("What Scene Do You Want To Load: ");
		l_jsonFile.open("Scene Saves/" + ms_sceneName + ".json");

		if (!l_jsonFile.fail())
		{
			l_jsonFile >> l_json;
			fileLoaded = true;
			break;
		}
		mp_ui->PrintData<string>("File could not be found please enter a file name without a file format");
	}

	sceneFPS = l_json["Animation FPS"];
	sceneLength = l_json["Animation Duriation"];

	for (int i = 0; i < l_json["ObjectCount"]; i++)
	{
		Sphere* lp_newSphere = new Sphere();
		lp_newSphere->ConvertJSONtoOBJ(&l_json, i);
		objectsInScene.push_back(lp_newSphere);
		lp_newSphere = nullptr;
	}

}

void SceneManager::SaveScene()
{
	mp_ui->PrintHeader("Saving Current Scene, Please enter Name of the save file");
	ms_sceneName = mp_ui->GetUserInput<string>("Name Of Scene: ");
	//- Constructing the Scene to Json Format-//
	json l_json;
	l_json["ObjectCount"] = objectsInScene.size();
	l_json["Animation FPS"] = sceneFPS;
	l_json["Animation Duriation"] = sceneLength;
	for (int i = 0; i < objectsInScene.size(); i++)
	{
		objectsInScene[i]->ConvertOBJtoJSON(&l_json, i);
	}
	ofstream l_jsonFile("Scene Saves/" + ms_sceneName + ".json");
	l_jsonFile << l_json << "\n";
}

void SceneManager::CreateNewSphere()
{
	Sphere* lp_newSphere = new Sphere();
	lp_newSphere->UIchange();
	objectsInScene.push_back(lp_newSphere);
	lp_newSphere = nullptr;

	SaveScene();
}

void SceneManager::EditSpheres()
{
	//- Creating SubMenu Vector -//
	vector<MenuOption> l_editSceneMenu;
	//- Create Dynamic Spheres -//
	for (int i = 0; i < objectsInScene.size(); i++)
	{
		l_editSceneMenu.push_back(MenuOption(("Edit " + objectsInScene[i]->OBJ_name + " :"), EditSceneWrapper));
	}

	mp_ui->DisplayMenu(l_editSceneMenu, "Edit Scene Elements", UpdateScelectedObjectWrapper, mpi_selectedObjectToEdit);
}

void SceneManager::sceneRefresh()
{
	for (int i = 0; i < objectsInScene.size(); i++)
	{
		delete objectsInScene[i];
		objectsInScene[i] = nullptr;
	}
	objectsInScene.clear();

	json l_json;
	ifstream l_jsonFile("Scene Saves/" + ms_sceneName + ".json");
	l_jsonFile >> l_json;

	sceneFPS = l_json["Animation FPS"];
	sceneLength = l_json["Animation Duriation"];

	for (int i = 0; i < l_json["ObjectCount"]; i++)
	{
		Sphere* lp_newSphere = new Sphere();
		lp_newSphere->ConvertJSONtoOBJ(&l_json, i);
		objectsInScene.push_back(lp_newSphere);
		lp_newSphere = nullptr;
	}
}

void SceneManager::Menu()
{
	//- Main Menu -//
	vector<MenuOption> l_menuOptions;
	l_menuOptions.push_back(MenuOption("View Scene Info", ViewSceneInfoWrapper));
	l_menuOptions.push_back(MenuOption("Load Scene", LoadSceneWrapper));
	l_menuOptions.push_back(MenuOption("Save Scene", SaveSceneWrapper));
	l_menuOptions.push_back(MenuOption("Create New Sphere", CreateSphereWrapper));
	l_menuOptions.push_back(MenuOption("Edit Scene", EditSpheresWrapper));
	l_menuOptions.push_back(MenuOption("Change Animations FPS", EditAnimationFPSWrapper));
	l_menuOptions.push_back(MenuOption("Change Animations Duriation", EditAnimationDuriationWrapper));
	l_menuOptions.push_back(MenuOption("Duplicate View Scene Info (Here to show ui page functions)", ViewSceneInfoWrapper));

	//- Display Menu -//
	mp_ui->DisplayMenu(l_menuOptions, "Scene Manager");
}