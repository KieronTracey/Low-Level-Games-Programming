#include "sphere.h"
Sphere* OBJ_sSphere;


Sphere::Sphere()
{
	
	OBJ_center = Vec3f(2.5, -1, -15);
	OBJ_radius = 2;
	OBJ_surfcolour = Vec3f(0.9,0.1,0.1);
	OBJ_emisscolour = Vec3f(0.1,0.1,0.1);
	OBJ_transparency = 0.5;
	OBJ_reflection = 1;
	OBJ_name = "SphereDefault";

	OBJ_sSphere = this;
}

Sphere::~Sphere()
{

}

bool Sphere::intersecting(const Vec3f& rayOrigin, const Vec3f& rayDirection, float& temp1, float& temp2)
{
	float Radius = (OBJ_radius * OBJ_radius);

	Vec3f temp3 = OBJ_center - rayOrigin; //calculat length by sphere centre compared to rays origin

	float dts = temp3.mathVar(rayDirection); // work out distance to sphere

	if (dts < 0) return false; //if dts < 0 means ray is going away from sphere so break

	float dtCos = temp3.mathVar(temp3) - dts * dts; // calculate the distance to centre of sphere (mathVar = square)

	if (dtCos > Radius) return false; // dtCos compared to radius to calculate if inside of sphere

	float rcTC = sqrt(Radius - dtCos); // rcTC = space from centre of raycast to it's outside

	temp1 = dts - rcTC; // temp1 = space ammount from ray origin to sphere entry

	temp2 = dts + rcTC; // temp2 = space ammount from ray origin to sphere exit

	return true;
}

//allocate for new sphere
void* Sphere::operator new(size_t size)
{
	return MemoryManagerRef::memoryManager->sceneMemPool->Allocate(size);
}

//delete sphere
void Sphere::operator delete(void* mem)
{
	MemoryManagerRef::memoryManager->sceneMemPool->FreeMemory(mem);
}

void Sphere::ConvertOBJtoJSON(json* jsonDt, int jIndex) //comment clearly later too messy
{
	(*jsonDt)["Spheres"][jIndex]["Name"] = OBJ_name;
	(*jsonDt)["Spheres"][jIndex]["center"]["X"] = OBJ_center.x;
	(*jsonDt)["Spheres"][jIndex]["center"]["Y"] = OBJ_center.y;
	(*jsonDt)["Spheres"][jIndex]["center"]["Z"] = OBJ_center.z;
	(*jsonDt)["Spheres"][jIndex]["radius"] = OBJ_radius;
	(*jsonDt)["Spheres"][jIndex]["surfaceColor"]["X"] = OBJ_surfcolour.x;
	(*jsonDt)["Spheres"][jIndex]["surfaceColor"]["Y"] = OBJ_surfcolour.y;
	(*jsonDt)["Spheres"][jIndex]["surfaceColor"]["Z"] = OBJ_surfcolour.z;
	(*jsonDt)["Spheres"][jIndex]["emissionColor"]["X"] = OBJ_emisscolour.x;
	(*jsonDt)["Spheres"][jIndex]["emissionColor"]["Y"] = OBJ_emisscolour.y;
	(*jsonDt)["Spheres"][jIndex]["emissionColor"]["Z"] = OBJ_emisscolour.z;
	(*jsonDt)["Spheres"][jIndex]["transparency"] = OBJ_transparency;
	(*jsonDt)["Spheres"][jIndex]["reflection"] = OBJ_reflection;
	(*jsonDt)["Spheres"][jIndex]["startPosition"]["X"] = OBJ_startpos.x;
	(*jsonDt)["Spheres"][jIndex]["startPosition"]["Y"] = OBJ_startpos.y;
	(*jsonDt)["Spheres"][jIndex]["startPosition"]["Z"] = OBJ_startpos.z;
	(*jsonDt)["Spheres"][jIndex]["endPosition"]["X"] = OBJ_endpos.x;
	(*jsonDt)["Spheres"][jIndex]["endPosition"]["Y"] = OBJ_endpos.y;
	(*jsonDt)["Spheres"][jIndex]["endPosition"]["Z"] = OBJ_endpos.z;

}

void Sphere::ConvertJSONtoOBJ(json* jsonDt, int jIndex) //comment clearly later too messy
{
	OBJ_name = (*jsonDt)["Spheres"][jIndex]["Name"];
	OBJ_center.x = (*jsonDt)["Spheres"][jIndex]["center"]["X"];
	OBJ_center.y = (*jsonDt)["Spheres"][jIndex]["center"]["Y"];
	OBJ_center.z = (*jsonDt)["Spheres"][jIndex]["center"]["Z"];
	OBJ_radius = (*jsonDt)["Spheres"][jIndex]["radius"];
	OBJ_surfcolour.x = (*jsonDt)["Spheres"][jIndex]["surfaceColor"]["X"];
	OBJ_surfcolour.y = (*jsonDt)["Spheres"][jIndex]["surfaceColor"]["Y"];
	OBJ_surfcolour.z = (*jsonDt)["Spheres"][jIndex]["surfaceColor"]["Z"];
	OBJ_emisscolour.x = (*jsonDt)["Spheres"][jIndex]["emissionColor"]["X"];
	OBJ_emisscolour.y = (*jsonDt)["Spheres"][jIndex]["emissionColor"]["Y"];
	OBJ_emisscolour.z = (*jsonDt)["Spheres"][jIndex]["emissionColor"]["Z"];
	OBJ_transparency = (*jsonDt)["Spheres"][jIndex]["transparency"];
	OBJ_reflection = (*jsonDt)["Spheres"][jIndex]["reflection"];
	OBJ_startpos.x = (*jsonDt)["Spheres"][jIndex]["startPosition"]["X"];
	OBJ_startpos.y = (*jsonDt)["Spheres"][jIndex]["startPosition"]["Y"];
	OBJ_startpos.z = (*jsonDt)["Spheres"][jIndex]["startPosition"]["Z"];
	OBJ_endpos.x = (*jsonDt)["Spheres"][jIndex]["endPosition"]["X"];
	OBJ_endpos.y = (*jsonDt)["Spheres"][jIndex]["endPosition"]["Y"];
	OBJ_endpos.z = (*jsonDt)["Spheres"][jIndex]["endPosition"]["Z"];
}

void Sphere::outputCurrentValues() //comment clearly later too messy
{
	spUI->PrintHeader("Current Object Values For " + OBJ_name);
	spUI->PrintDataWithText("Object's Name: ", OBJ_name);
	spUI->PrintDataWithText("Position / Center of Object: ", OBJ_center);
	spUI->PrintDataWithText("Radius of Object: ", OBJ_radius);
	spUI->PrintDataWithText("Object's Surface Color: ", OBJ_surfcolour);
	spUI->PrintDataWithText("Object's Emmision Color: ", OBJ_emisscolour);
	spUI->PrintDataWithText("Object's Transparancy: ", OBJ_transparency);
	spUI->PrintDataWithText("Object's Reflection: ", OBJ_reflection);
}

void AlterName() 
{
	OBJ_sSphere->ChangeVar<string>(OBJ_sSphere->spUI->GetUserInput<string>("Please Input Name: "), &OBJ_sSphere->OBJ_name);
};

void AlterTransparancey() 
{
	OBJ_sSphere->ChangeVar<float>(OBJ_sSphere->spUI->GetUserInput<float>("Please Input Transparancy: "), &OBJ_sSphere->OBJ_transparency); 
};

void AlterReflection() 
{
	OBJ_sSphere->ChangeVar<float>(OBJ_sSphere->spUI->GetUserInput<float>("Please Input Reflection: "), &OBJ_sSphere->OBJ_reflection); 
};

void AlterPosition() 
{
	OBJ_sSphere->ChangeVar<Vec3f>(OBJ_sSphere->spUI->GetUserInputVec3f("Please Input Position: "), &OBJ_sSphere->OBJ_center); 
};

void AlterRadius() 
{
	OBJ_sSphere->ChangeVar<float>(OBJ_sSphere->spUI->GetUserInput<float>("Please Input Raidus: "), &OBJ_sSphere->OBJ_radius); 
};

void AlterSurfaceColor() 
{
	OBJ_sSphere->ChangeVar<Vec3f>(OBJ_sSphere->spUI->GetUserInputVec3f("Please Input SurfaceColor: "), &OBJ_sSphere->OBJ_surfcolour); 
};

void AlterEmissionColor() 
{
	OBJ_sSphere->ChangeVar<Vec3f>(OBJ_sSphere->spUI->GetUserInputVec3f("Please Input EmissionColor: "), &OBJ_sSphere->OBJ_emisscolour); 
};

void AlterStartPosition() 
{
	OBJ_sSphere->ChangeVar<Vec3f>(OBJ_sSphere->spUI->GetUserInputVec3f("Please Input Start Position: "), &OBJ_sSphere->OBJ_startpos); 
};

void AlterEndPosition() 
{
	OBJ_sSphere->ChangeVar<Vec3f>(OBJ_sSphere->spUI->GetUserInputVec3f("Please Input End Position: "), &OBJ_sSphere->OBJ_endpos);
};

void DisplayCurrentValues() 
{
	OBJ_sSphere->outputCurrentValues(); 
}

void Sphere::UIchange()
{
	OBJ_sSphere = this;

	vector<MenuOption> InititalMenu;
	InititalMenu.push_back(MenuOption("Display Current Values", DisplayCurrentValues));

	InititalMenu.push_back(MenuOption("Alter Name", AlterName));

	InititalMenu.push_back(MenuOption("Alter Transparacy", AlterTransparancey));

	InititalMenu.push_back(MenuOption("Alter Reflection", AlterReflection));

	InititalMenu.push_back(MenuOption("Alter Position", AlterPosition));

	InititalMenu.push_back(MenuOption("Alter Radius", AlterRadius));

	InititalMenu.push_back(MenuOption("Alter Surface Color", AlterSurfaceColor));

	InititalMenu.push_back(MenuOption("Alter Emission Color", AlterEmissionColor));

	InititalMenu.push_back(MenuOption("Alter Start Position", AlterStartPosition));

	InititalMenu.push_back(MenuOption("Alter End Position", AlterEndPosition));

	spUI->DisplayMenu(InititalMenu, "Alter Spheres Values");

}