#include<stdio.h>
#include<iostream>

template<class T>
class vec3
{
public:
	T x;
	T y;
	T z;
public:
	//Operators
	vec3<T> operator+(vec3<T> vector) const;
	vec3<T> operator-(vec3<T> vector) const;
	void operator+=(vec3<T> vector);
	void operator-=(vec3<T> vector);
	void operator=(vec3<T> vector);
	bool operator==(vec3<T> vector) const;

	//Class methods
	void normalize();
	void zero();
	bool is_zero();
	double distance_to(vec3<T> vector);
	double get_module();
	vec3<T> get_vector_from(vec3<T> vector);
	//Constructor and destructor
    vec3<T>(T _x, T _y, T _z)
	{
		x = _x; y = _y; z = _z;
	}
	vec3<T>():x(0), y(0), z(0) {}
	
};

template<class T>
vec3<T> vec3<T>::operator+(vec3<T> vector) const
{
	vec3<T> ret(x + vector.x, y + vector.y, z + vector.z);
	return ret;
}

template<class T>
vec3<T> vec3<T>::operator-(vec3<T> vector) const
{
	vec3<T> ret(x - vector.x, y - vector.y, z - vector.z);
	return ret;
}

template<class T>
void vec3<T>::operator+=(vec3<T> vector)
{
	x += vector.x;
	y += vector.y;
	z += vector.z;

}

template<class T>
void vec3<T>::operator-=(vec3<T> vector) 
{
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;
}

template<class T>
void vec3<T>::operator=(vec3<T> vector) 
{
	x = vector.x;
	y = vector.y;
	z = vector.z;
}

template<class T>
bool vec3<T>::operator==(vec3<T> vector) const
{
	return x == vector.x && y == vector.y && z == vector.z;
}

template<class T>
void vec3<T>::normalize()
{
	vec3<T> module_representer = this;

	x = x / module_representer.get_module();
	y = y / module_representer.get_module();
	z = z / module_representer.get_module();
}

template<class T>
void vec3<T>::zero()
{
	x = 0; y = 0; z = 0;
}

template<class T>
bool vec3<T>::is_zero()
{
	return x == 0 && y == 0 && z == 0;
}

template<class T>
double vec3<T>::distance_to(vec3 vector)
{
	int nx, ny, nz;

	nx = x - vector.x;
	ny = y - vector.y;
	nz = z - vector.z;
	return sqrt(pow(nx, 2) + pow(ny, 2) + pow(nz, 2));
}

template<class T>
double vec3<T>::get_module()
{
	return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

template<class T>
vec3<T> vec3<T>::get_vector_from(vec3 vector)
{
	vec3 newvector = vec3(x - vector.x, y - vector.y,z - vector.z);
    return newvector;
}

	

