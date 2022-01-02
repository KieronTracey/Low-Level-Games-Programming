#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

#include "Sphere.h"

class SceneManager
{
public:
	

	UI* Hui;
	string SceneName;
	vector<Sphere*> objectPresent;

	void Menus();
	void SceneInformation();
	void LoadSceneFromJson();
	void SaveSceneToJson();
	void CreateNewSphereOBJ();
	void EditSphereOBJ();

	SceneManager(UI* UIRef);
	~SceneManager();

	vector<Sphere*> FrameToBeRendered(int FPScount);
	void SceneRefresh();

	bool loadFile;
	int* selectedObject;
	Sphere* selectedSphere;
	float Length;
	int FPS;

};

#endif