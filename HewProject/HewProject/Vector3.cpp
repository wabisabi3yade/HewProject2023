#include "Vector3.h"

Vector3 Vector3::up = { 0.0f,1.0f,0.0f };
Vector3 Vector3::down = { 0.0f,-1.0f,0.0f };
Vector3 Vector3::left = { -1.0f,0.0f,0.0f };
Vector3 Vector3::right = { 1.0f,0.0f,0.0f };
Vector3 Vector3::one = { 1.0f,1.0f,1.0f };
Vector3 Vector3::zero = { 0.0f,0.0f,0.0f };

Vector3::Vector3(float _x, float _y, float _z)
{
	x = _x, y = _y, z = _z;
}

Vector3 Vector3::operator+(Vector3 _v)
{
	Vector3 v3;
	v3.x = this->x + _v.x;
	v3.y = this->y + _v.y;
	v3.z = this->z + _v.z;
	return v3;
}

void Vector3::operator+=(Vector3 _v)
{
	this->x += _v.x;
	this->y += _v.y;
	this->z += _v.z;
}