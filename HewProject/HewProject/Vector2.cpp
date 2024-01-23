#include "Vector2.h"

Vector2 Vector2::up = { 0.0f,1.0f };
Vector2 Vector2::down = { 0.0f,-1.0f };
Vector2 Vector2::left = { -1.0f,0.0f };
Vector2 Vector2::right = { 1.0f,0.0f };
Vector2 Vector2::one = { 1.0f,1.0f };
Vector2 Vector2::zero = { 0.0f,0.0f };

Vector2::Vector2(float _x, float _y)
{
	x = _x;
	y = _y;
}

Vector2 Vector2::operator+(Vector2 _v)
{
	Vector2 ret(this->x + _v.x, this->y + _v.y);
	return ret;
}

Vector2 Vector2::operator-(Vector2 _v)
{
	Vector2 ret(this->x - _v.x, this->y - _v.y);
	return ret;
}

Vector2 Vector2::operator*(Vector2 _v)
{
	Vector2 ret(this->x * _v.x, this->y * _v.y);
	return ret;
}

Vector2 Vector2::operator/(Vector2 _v)
{
	Vector2 ret(this->x / _v.x, this->y / _v.y);
	return ret;
}

Vector2 Vector2::operator*(float _v)
{
	Vector2 ret(this->x * _v, this->y * _v);
	return ret;
}

const bool& Vector2::operator>=(const Vector2& _v) const
{
	if (this->x >= _v.x && this->y >= _v.y)
	{
		return true;
	}
	return false;
}

const bool& Vector2::operator<=(const Vector2& _v) const
{
	if (this->x <= _v.x && this->y <= _v.y)
	{
		return true;
	}
	return false;
}

const bool& Vector2::operator>(const Vector2& _v) const
{
	if (this->x > _v.x && this->y > _v.y)
	{
		return true;
	}
	return false;
}

const bool& Vector2::operator<(const Vector2& _v) const
{
	if (this->x < _v.x && this->y < _v.y)
	{
		return true;
	}
	return false;
}

const bool& Vector2::operator==(const Vector2& _v) const
{
	if (this->x == _v.x && this->y == _v.y)
	{
		return true;
	}
	return false;
}
