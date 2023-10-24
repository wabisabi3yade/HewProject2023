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
	Vector3 ret(this->x - _v.x, this->y - _v.y, this->z - _v.z);
	return ret;
}

Vector3 Vector3::operator-(Vector3 _v)
{
	Vector3 ret(this->x - _v.x, this->y - _v.y, this->z - _v.z);
	return ret;
}

Vector3 Vector3::operator*(Vector3 _v)
{
	Vector3 ret(this->x * _v.x, this->y * _v.y, this->z * _v.z);
	return ret;
}

Vector3 Vector3::operator/(Vector3 _v)
{
	Vector3 ret(this->x / _v.x, this->y / _v.y, this->z / _v.z);
	return ret;
}

const Vector3& Vector3::operator+(const Vector3& _v) const
{
	Vector3 ret(this->x + _v.x, this->y + _v.y, this->z + _v.z);
	return ret;
}

const Vector3& Vector3::operator-(const Vector3& _v)const
{
	Vector3 ret(this->x - _v.x, this->y - _v.y, this->z - _v.z);
	return ret;
}

DirectX::XMFLOAT3* dirChange(Vector3 _vec)
{
	DirectX::XMFLOAT3 v(_vec.x, _vec.y, _vec.z);
	return &v;
}