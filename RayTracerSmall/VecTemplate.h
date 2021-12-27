#ifndef _VECTOR_TEMPLATE_H_
#define _VECTOR_TEMPLATE_H_

#include <iostream>
#include <iomanip>

template<typename T>
class Vec3
{
public:
	T x, y, z;
	Vec3() : x(T(0)), y(T(0)), z(T(0)) {}
	Vec3(T xx) : x(xx), y(xx), z(xx) {}
	Vec3(T xx, T yy, T zz) : x(xx), y(yy), z(zz) {}
	Vec3& normalize()
	{
		T nor2 = length2();
		if (nor2 > 0) {
			T invNor = 1 / sqrt(nor2);
			x *= invNor, y *= invNor, z *= invNor;
		}
		return *this;
	}
	Vec3<T> operator * (const T& f) const { return Vec3<T>(x * f, y * f, z * f); }
	Vec3<T> operator * (const Vec3<T>& v) const { return Vec3<T>(x * v.x, y * v.y, z * v.z); }
	T dot(const Vec3<T>& v) const { return x * v.x + y * v.y + z * v.z; }
	Vec3<T> operator - (const Vec3<T>& v) const { return Vec3<T>(x - v.x, y - v.y, z - v.z); }
	Vec3<T> operator + (const Vec3<T>& v) const { return Vec3<T>(x + v.x, y + v.y, z + v.z); }
	Vec3<T>& operator += (const Vec3<T>& v) { x += v.x, y += v.y, z += v.z; return *this; }
	Vec3<T>& operator *= (const Vec3<T>& v) { x *= v.x, y *= v.y, z *= v.z; return *this; }
	Vec3<T> operator - () const { return Vec3<T>(-x, -y, -z); }

	friend bool operator == (const Vec3<T>& a, const Vec3<T>& b) { return (a.x == b.x && a.y == b.y && a.z == b.z) ? true : false; }
	friend bool operator != (const Vec3<T>& a, const Vec3<T>& b) { return !(a == b); }

	T length2() const { return x * x + y * y + z * z; }
	T length() const { return sqrt(length2()); }
	friend std::ostream& operator << (std::ostream& os, const Vec3<T>& v)
	{
		os << "[" << v.x << " " << v.y << " " << v.z << "]";
		return os;
	}

	friend std::istream& operator >> (std::istream& in, Vec3<T>& v)
	{
		string ls_inputData;

		cout << std::setw(64) << "Enter X: " << flush; in >> ls_inputData; cout << std::setw(56) << flush;
		v.x = std::stof(ls_inputData);
		cout << std::setw(64) << "Enter Y: " << flush; in >> ls_inputData; cout << std::setw(56) << flush;
		v.y = std::stof(ls_inputData);
		cout << std::setw(64) << "Enter Z: " << flush; in >> ls_inputData; cout << std::setw(56) << "\r";
		v.z = std::stof(ls_inputData);

		return in;
	}
};


#endif // !_VECTOR_TEMPLATE_H_