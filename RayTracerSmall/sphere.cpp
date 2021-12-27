#include "sphere.h"
Sphere* gp_selfSphere;


Sphere::Sphere()
{
	ms_objectName = "BaseSphere";
	m_center = Vec3f(0, 0, 0);
	mf_radius = 1000;
	m_surfaceColor = Vec3f(255, 1, 1);
	m_emissionColor = Vec3f(1, 1, 1);
	mf_transparency = 0;
	mf_reflection = 10;

	gp_selfSphere = this;
}

Sphere::~Sphere()
{

}

//- Intersect explanation -//
// l = calculating length by center of sphere vs ray origin
// tca = calculates the distance to sphere
// if tca < 0 = ray will be going away from sphere so stop calculations
// d2 = calculates distance to center of the sphere (Dot isnt dot is square) and the maths is pythagoras theorem
// d2 checked against radius to see if inside of sphere
// thc = distance from the center of raycast to the outside of it
// t0 = distance from ray origin to entry of the sphere
// t1 = distance from ray origin to exit of the sphere
bool Sphere::intersect(const Vec3f& rayorig, const Vec3f& raydir, float& t0, float& t1)
{
	float lf_radius2 = (mf_radius * mf_radius);

	Vec3f l = m_center - rayorig;
	float tca = l.dot(raydir);
	if (tca < 0) return false;
	float d2 = l.dot(l) - tca * tca;
	if (d2 > lf_radius2) return false;
	float thc = sqrt(lf_radius2 - d2);
	t0 = tca - thc;
	t1 = tca + thc;

	return true;
}

void* Sphere::operator new(size_t size)
{
	return MemoryManagerRef::mp_memoryManager->mp_sceneMemoryPool->Alloc(size);
}

void Sphere::operator delete(void* pMem)
{
	MemoryManagerRef::mp_memoryManager->mp_sceneMemoryPool->Free(pMem);
}

void Sphere::ObjectToJson(json* ap_json, int a_index)
{
	(*ap_json)["Spheres"][a_index]["Name"] = ms_objectName;

	(*ap_json)["Spheres"][a_index]["center"]["X"] = m_center.x;
	(*ap_json)["Spheres"][a_index]["center"]["Y"] = m_center.y;
	(*ap_json)["Spheres"][a_index]["center"]["Z"] = m_center.z;

	(*ap_json)["Spheres"][a_index]["radius"] = mf_radius;

	(*ap_json)["Spheres"][a_index]["surfaceColor"]["X"] = m_surfaceColor.x;
	(*ap_json)["Spheres"][a_index]["surfaceColor"]["Y"] = m_surfaceColor.y;
	(*ap_json)["Spheres"][a_index]["surfaceColor"]["Z"] = m_surfaceColor.z;

	(*ap_json)["Spheres"][a_index]["emissionColor"]["X"] = m_emissionColor.x;
	(*ap_json)["Spheres"][a_index]["emissionColor"]["Y"] = m_emissionColor.y;
	(*ap_json)["Spheres"][a_index]["emissionColor"]["Z"] = m_emissionColor.z;

	(*ap_json)["Spheres"][a_index]["transparency"] = mf_transparency;

	(*ap_json)["Spheres"][a_index]["reflection"] = mf_reflection;

	(*ap_json)["Spheres"][a_index]["startPosition"]["X"] = m_startPosition.x;
	(*ap_json)["Spheres"][a_index]["startPosition"]["Y"] = m_startPosition.y;
	(*ap_json)["Spheres"][a_index]["startPosition"]["Z"] = m_startPosition.z;

	(*ap_json)["Spheres"][a_index]["endPosition"]["X"] = m_endPosition.x;
	(*ap_json)["Spheres"][a_index]["endPosition"]["Y"] = m_endPosition.y;
	(*ap_json)["Spheres"][a_index]["endPosition"]["Z"] = m_endPosition.z;

}

void Sphere::JsonToObject(json* ap_json, int a_index)
{
	ms_objectName = (*ap_json)["Spheres"][a_index]["Name"];

	m_center.x = (*ap_json)["Spheres"][a_index]["center"]["X"];
	m_center.y = (*ap_json)["Spheres"][a_index]["center"]["Y"];
	m_center.z = (*ap_json)["Spheres"][a_index]["center"]["Z"];

	mf_radius = (*ap_json)["Spheres"][a_index]["radius"];

	m_surfaceColor.x = (*ap_json)["Spheres"][a_index]["surfaceColor"]["X"];
	m_surfaceColor.y = (*ap_json)["Spheres"][a_index]["surfaceColor"]["Y"];
	m_surfaceColor.z = (*ap_json)["Spheres"][a_index]["surfaceColor"]["Z"];

	m_emissionColor.x = (*ap_json)["Spheres"][a_index]["emissionColor"]["X"];
	m_emissionColor.y = (*ap_json)["Spheres"][a_index]["emissionColor"]["Y"];
	m_emissionColor.z = (*ap_json)["Spheres"][a_index]["emissionColor"]["Z"];

	mf_transparency = (*ap_json)["Spheres"][a_index]["transparency"];

	mf_reflection = (*ap_json)["Spheres"][a_index]["reflection"];

	m_startPosition.x = (*ap_json)["Spheres"][a_index]["startPosition"]["X"];
	m_startPosition.y = (*ap_json)["Spheres"][a_index]["startPosition"]["Y"];
	m_startPosition.z = (*ap_json)["Spheres"][a_index]["startPosition"]["Z"];

	m_endPosition.x = (*ap_json)["Spheres"][a_index]["endPosition"]["X"];
	m_endPosition.y = (*ap_json)["Spheres"][a_index]["endPosition"]["Y"];
	m_endPosition.z = (*ap_json)["Spheres"][a_index]["endPosition"]["Z"];
}

void Sphere::DisplayCurrentProperties()
{
	mp_ui->PrintHeader("Current Values For " + ms_objectName);
	mp_ui->PrintDataWithText("Object Name: ", ms_objectName);
	mp_ui->PrintDataWithText("Position/Center: ", m_center);
	mp_ui->PrintDataWithText("Radius: ", mf_radius);
	mp_ui->PrintDataWithText("SurfaceColor: ", m_surfaceColor);
	mp_ui->PrintDataWithText("EmmisionColor: ", m_emissionColor);
	mp_ui->PrintDataWithText("Transparancy: ", mf_transparency);
	mp_ui->PrintDataWithText("Reflection: ", mf_reflection);
}

//-------------------------------------------------//
//------------ void Wrappers for void* ------------//
//-------------------------------------------------//
void DisplayCurrentValues() { gp_selfSphere->DisplayCurrentProperties(); }
void ChangeName() { gp_selfSphere->ChangeVar<string>(gp_selfSphere->mp_ui->GetUserInput<string>("Enter Name(no spaces): "), &gp_selfSphere->ms_objectName); };
void ChangePosition() { gp_selfSphere->ChangeVar<Vec3f>(gp_selfSphere->mp_ui->GetUserInputVec3f("Enter Position: "), &gp_selfSphere->m_center); };
void ChangeRadius() { gp_selfSphere->ChangeVar<float>(gp_selfSphere->mp_ui->GetUserInput<float>("Enter Raidus: "), &gp_selfSphere->mf_radius); };
void ChangeSurfaceColor() { gp_selfSphere->ChangeVar<Vec3f>(gp_selfSphere->mp_ui->GetUserInputVec3f("Enter SurfaceColor: "), &gp_selfSphere->m_surfaceColor); };
void ChangeEmissionColor() { gp_selfSphere->ChangeVar<Vec3f>(gp_selfSphere->mp_ui->GetUserInputVec3f("Enter EmissionColor: "), &gp_selfSphere->m_emissionColor); };
void ChangeTransparacy() { gp_selfSphere->ChangeVar<float>(gp_selfSphere->mp_ui->GetUserInput<float>("Enter Transparancy: "), &gp_selfSphere->mf_transparency); };
void ChangeReflection() { gp_selfSphere->ChangeVar<float>(gp_selfSphere->mp_ui->GetUserInput<float>("Enter Reflection: "), &gp_selfSphere->mf_reflection); };
void ChangeStartPos() { gp_selfSphere->ChangeVar<Vec3f>(gp_selfSphere->mp_ui->GetUserInputVec3f("Enter New Start Position: "), &gp_selfSphere->m_startPosition); };
void ChangeEndPos() { gp_selfSphere->ChangeVar<Vec3f>(gp_selfSphere->mp_ui->GetUserInputVec3f("Enter End Position: "), &gp_selfSphere->m_endPosition); };

void Sphere::UIAlterValues()
{
	gp_selfSphere = this;

	vector<MenuOption> l_mainMenu;
	l_mainMenu.push_back(MenuOption("Display Current Values", DisplayCurrentValues));
	l_mainMenu.push_back(MenuOption("Change Name", ChangeName));
	l_mainMenu.push_back(MenuOption("Change Position", ChangePosition));
	l_mainMenu.push_back(MenuOption("Change Radius", ChangeRadius));
	l_mainMenu.push_back(MenuOption("Change Surface Color", ChangeSurfaceColor));
	l_mainMenu.push_back(MenuOption("Change Emission Color", ChangeEmissionColor));
	l_mainMenu.push_back(MenuOption("Change Transparacy", ChangeTransparacy));
	l_mainMenu.push_back(MenuOption("Change Reflection", ChangeReflection));
	l_mainMenu.push_back(MenuOption("Edit Start Position", ChangeStartPos));
	l_mainMenu.push_back(MenuOption("Edit End Position", ChangeEndPos));

	mp_ui->DisplayMenu(l_mainMenu, "Alter Spheres Values");

}