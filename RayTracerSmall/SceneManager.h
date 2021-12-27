#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

#include "Sphere.h"
using namespace std;

class SceneManager
{
public:
	//- Manager Methods -//
	SceneManager(UI* ap_uiRef);
	~SceneManager();


	//- User Acsessed -//
	UI* mp_ui;
	string ms_sceneName;
	vector<Sphere*> mp_sceneObjects;

	void Menu();
	void ViewSceneInfo();
	void LoadScene();
	void SaveScene();
	void CreateNewSphere();
	void EditSpheres();


	//- Developer Accsessed -//
	vector<Sphere*> GetFrameToRender(int frameCount);
	void RefreshScene();

	bool mb_loadedFile;
	int* mpi_selectedObjectToEdit;
	Sphere* mp_currentlySelected;
	float mf_duriation;
	int mi_framesPerSecond;

	//- Templates -//

};

#endif // !_SCENE_MANAGER_H_