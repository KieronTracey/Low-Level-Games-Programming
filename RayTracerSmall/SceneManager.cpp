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
void UpdateScelectedObjectWrapper() { gp_selfSceneManager->mp_currentlySelected = gp_selfSceneManager->mp_sceneObjects[*gp_selfSceneManager->mpi_selectedObjectToEdit]; };
void EditAnimationFPSWrapper() { gp_selfSceneManager->mi_framesPerSecond = gp_selfSceneManager->mp_ui->GetUserInput<float>("Enter FPS: "); };
void EditAnimationDuriationWrapper() { gp_selfSceneManager->mf_duriation = gp_selfSceneManager->mp_ui->GetUserInput<int>("Enter Duriation: "); };

SceneManager::SceneManager(UI* ap_uiRef)
{
	mp_ui = ap_uiRef;
	ms_sceneName = "Temp Scene Name";
	gp_selfSceneManager = this;
	mpi_selectedObjectToEdit = new int();
	*mpi_selectedObjectToEdit = 0;
	mf_duriation = 1.0f;
	mi_framesPerSecond = 30;
	mb_loadedFile = false;
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
	if (mp_sceneObjects.size() == 0)
	{
		mp_ui->PrintText("No scene loaded please load a scene from the Scene Manager Menu");
	}
	else
	{
		mp_ui->PrintDataWithText("Current Scene Name: ", ms_sceneName);
		mp_ui->PrintDataWithText("Amount of objects in the scene: ", mp_sceneObjects.size());
	}
}

void SceneManager::LoadScene()
{
	for (int i = 0; i < mp_sceneObjects.size(); i++)
	{
		delete mp_sceneObjects[i];
		mp_sceneObjects[i] = nullptr;
	}
	mp_sceneObjects.clear();

	json l_json;
	ifstream l_jsonFile;

	while (true)
	{
		ms_sceneName = mp_ui->GetUserInput<string>("What Scene Do You Want To Load: ");
		l_jsonFile.open("Scene Saves/" + ms_sceneName + ".json");

		if (!l_jsonFile.fail())
		{
			l_jsonFile >> l_json;
			mb_loadedFile = true;
			break;
		}
		mp_ui->PrintData<string>("File could not be found please enter a file name without a file format");
	}

	mi_framesPerSecond = l_json["Animation FPS"];
	mf_duriation = l_json["Animation Duriation"];

	for (int i = 0; i < l_json["ObjectCount"]; i++)
	{
		Sphere* lp_newSphere = new Sphere();
		lp_newSphere->ConvertJSONtoOBJ(&l_json, i);
		mp_sceneObjects.push_back(lp_newSphere);
		lp_newSphere = nullptr;
	}

}

void SceneManager::SaveScene()
{
	mp_ui->PrintHeader("Saving Current Scene, Please enter Name of the save file");
	ms_sceneName = mp_ui->GetUserInput<string>("Name Of Scene: ");
	//- Constructing the Scene to Json Format-//
	json l_json;
	l_json["ObjectCount"] = mp_sceneObjects.size();
	l_json["Animation FPS"] = mi_framesPerSecond;
	l_json["Animation Duriation"] = mf_duriation;
	for (int i = 0; i < mp_sceneObjects.size(); i++)
	{
		mp_sceneObjects[i]->ConvertOBJtoJSON(&l_json, i);
	}
	ofstream l_jsonFile("Scene Saves/" + ms_sceneName + ".json");
	l_jsonFile << l_json << "\n";
}

void SceneManager::CreateNewSphere()
{
	Sphere* lp_newSphere = new Sphere();
	lp_newSphere->UIchange();
	mp_sceneObjects.push_back(lp_newSphere);
	lp_newSphere = nullptr;

	SaveScene();
}

void SceneManager::EditSpheres()
{
	//- Creating SubMenu Vector -//
	vector<MenuOption> l_editSceneMenu;
	//- Create Dynamic Spheres -//
	for (int i = 0; i < mp_sceneObjects.size(); i++)
	{
		l_editSceneMenu.push_back(MenuOption(("Edit " + mp_sceneObjects[i]->OBJ_name + " :"), EditSceneWrapper));
	}

	mp_ui->DisplayMenu(l_editSceneMenu, "Edit Scene Elements", UpdateScelectedObjectWrapper, mpi_selectedObjectToEdit);
}

void SceneManager::RefreshScene()
{
	for (int i = 0; i < mp_sceneObjects.size(); i++)
	{
		delete mp_sceneObjects[i];
		mp_sceneObjects[i] = nullptr;
	}
	mp_sceneObjects.clear();

	json l_json;
	ifstream l_jsonFile("Scene Saves/" + ms_sceneName + ".json");
	l_jsonFile >> l_json;

	mi_framesPerSecond = l_json["Animation FPS"];
	mf_duriation = l_json["Animation Duriation"];

	for (int i = 0; i < l_json["ObjectCount"]; i++)
	{
		Sphere* lp_newSphere = new Sphere();
		lp_newSphere->ConvertJSONtoOBJ(&l_json, i);
		mp_sceneObjects.push_back(lp_newSphere);
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