#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "Json/json.hpp"
#include "MemoryManager.h"
#include "UI.h"
#include <fstream>
#include <math.h>
#include <sstream>

typedef Vector3<float> Vec3f;

using namespace nlohmann; //for Json
using namespace std;

class Sphere
{
public:

	Vec3f OBJ_surfcolour;
	Vec3f OBJ_emisscolour;
	float OBJ_transparency;
	float OBJ_reflection;
	Vec3f OBJ_center;
	float OBJ_radius;
	string OBJ_name;// stuff for object ^
	Vec3f OBJ_startpos;// for anim
	Vec3f OBJ_endpos; // for anim

	void UIchange();
	void ConvertOBJtoJSON(json* Jdata, int fjindex);
	void ConvertJSONtoOBJ(json* Jdata, int fjindex);
	void outputCurrentValues();

	bool intersecting(const Vec3f& rayOrigin, const Vec3f& rayDirection, float& temp1, float& temp2);
	UI* spUI;

	template<typename Template>
	void ChangeVar(Template input, Template* variableToChange);

	void* operator new(size_t size);
	void operator delete(void* mem);

	Sphere();
	~Sphere();
};

template<typename Template>
void Sphere::ChangeVar(Template input, Template* variableToChange)
{
	*variableToChange = input;
}

#endif