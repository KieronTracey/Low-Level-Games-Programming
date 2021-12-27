#ifndef _SPHERE_H_
#define _SPHERE_H_

#include <math.h>
#include <sstream>
#include <fstream>

#include "UI.h"
#include "Json/json.hpp"
#include "MemoryManager.h"
using namespace nlohmann;
using namespace std;

//- Define for Vec3f Required at start of each header -//
typedef Vec3<float> Vec3f;

class Sphere
{
public:

	//- Manager Methods -//
	Sphere();
	~Sphere();


	//- User Accessed/Defined -//
	//- Visual Variables-//
	string ms_objectName;
	Vec3f m_center;
	float mf_radius;
	Vec3f m_surfaceColor, m_emissionColor;
	float mf_transparency, mf_reflection;

	//- Aimation Variables -//
	Vec3f m_startPosition, m_endPosition;

	void UIAlterValues();
	void ObjectToJson(json* ap_j, int a_index);
	void JsonToObject(json* ap_j, int a_index);
	void DisplayCurrentProperties();


	//- Developer Accessed/Defined -//
	bool intersect(const Vec3f& rayorig, const Vec3f& raydir, float& t0, float& t1);
	UI* mp_ui;

	void* operator new(size_t size);
	void operator delete(void* pMem);

	//- Templates -//
	template<typename T>
	void ChangeVar(T a_input, T* ap_varToChange);

};

template<typename T>
void Sphere::ChangeVar(T a_input, T* ap_varToChange)
{
	*ap_varToChange = a_input;
}

#endif // !_SPHERE_H_