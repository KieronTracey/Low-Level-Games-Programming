#ifndef _VECTOR_TEMPLATE_H_
#define _VECTOR_TEMPLATE_H_

#include <iomanip>
#include <iostream>

template<typename Template>

class Vector3
{
public:
	Template x, y, z;

	Vector3() : x(Template(0)), y(Template(0)), z(Template(0))
	{

	}

	Vector3(Template tempVar) : x(tempVar), y(tempVar), z(tempVar)
	{

	}
	
	Vector3(Template xTemp, Template yTemp, Template zTemp) : x(xTemp), y(yTemp), z(zTemp) 
	{

	}

	Vector3& normalizeTemplate()
	{
		//work pleaz
		Template normal2 = lengthB();
		if (!normal2 < 0) {
			Template invNormal; 
			invNormal = 1 / sqrt(normal2);

			x *= invNormal; 
			y *= invNormal; 
			z *= invNormal;
		}
		return *this;
	}

	Vector3<Template> operator * (const Template& f) const 
	{
		return Vector3<Template>(x * f, y * f, z * f); 
	}

	Vector3<Template> operator * (const Vector3<Template>& Vec) const 
	{ 
		return Vector3<Template>(x * Vec.x, y * Vec.y, z * Vec.z); 
	}

	Template mathVar(const Vector3<Template>& Vec) const 
	{
		return x * Vec.x + y * Vec.y + z * Vec.z; //why this make break
	} 

	Vector3<Template> operator - (const Vector3<Template>& Vec) const 
	{
		return Vector3<Template>(x - Vec.x, y - Vec.y, z - Vec.z); 
	}

	Vector3<Template> operator + (const Vector3<Template>& Vec) const 
	{
		return Vector3<Template>(x + Vec.x, y + Vec.y, z + Vec.z); 
	}

	Vector3<Template>& operator += (const Vector3<Template>& Vec) 
	{
		x += Vec.x, y += Vec.y, z += Vec.z; return *this; 
	}

	Vector3<Template>& operator *= (const Vector3<Template>& Vec) 
	{
		x *= Vec.x, y *= Vec.y, z *= Vec.z; return *this; 
	}

	Vector3<Template> operator - () const 
	{
		return Vector3<Template>(-x, -y, -z); 
	}

	friend bool operator == (const Vector3<Template>& temp1, const Vector3<Template>& temp2) 
	{
		return (temp1.x == temp2.x && temp1.y == temp2.y && temp1.z == temp2.z) ? true : false; 
	}

	friend bool operator != (const Vector3<Template>& temp1, const Vector3<Template>& temp2) 
	{
		return !(temp1 == temp2); 
	}

	Template lengthB() const 
	{
		return x * x + y * y + z * z; 
	}

	Template lengthA() const 
	{
		return sqrt(lengthB()); 
	}

	friend std::ostream& operator << (std::ostream& OpSys, const Vector3<Template>& Vec)
	{
		OpSys << "[" << Vec.x << " " << Vec.y << " " << Vec.z << "]";
		return OpSys;
	}

	friend std::istream& operator >> (std::istream& Ent, Vector3<Template>& Vec)
	{//fix later
		string input;

		std::cout << std::setw(64) << "Please input X: " << flush;
		Ent >> input;
		std::cout << std::setw(56) << flush;
		Vec.x = std::stof(input);

		std::cout << std::setw(64) << "Please input Y: " << flush;
		Ent >> input;
		std::cout << std::setw(56) << flush;
		Vec.y = std::stof(input);

		std::cout << std::setw(64) << "Please input Z: " << flush;
		Ent >> input;
		std::cout << std::setw(56) << "\r";
		Vec.z = std::stof(input);

		return Ent;
	}
};


#endif