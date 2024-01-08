#pragma once
#include <d3d11.h>		// DirectX11を使うためのヘッダー
#include<DirectXMath.h> //DirectXの数学関連のヘッダーファイル

//float型３つのクラス x y z
class Vector3
{
public:
	float x, y, z;
	Vector3(float _x = 0.0f ,float _y = 0.0f, float _z = 0.0f);

	static Vector3 up;
	static Vector3 down;
	static Vector3 left;
	static Vector3 right;
	static Vector3 one;
	static Vector3 zero;

	Vector3 operator+(Vector3 _v);
	Vector3 operator-(Vector3 _v);
	Vector3 operator*(Vector3 _v);
	Vector3 operator/(Vector3 _v);
	//Vector3 operator<(Vector3 _v);
	const Vector3& operator<(const Vector3& _v);
	const Vector3& operator+( const Vector3& _v)const;
	const Vector3& operator-( const Vector3& _v)const;

	const bool& operator>=(const Vector3& _v)const;
	const bool& operator==(const Vector3& _v)const;
	const bool& operator!=(const Vector3& _v)const;
};

DirectX::XMFLOAT3* dirChange(Vector3);

Vector3 dirChangeVec3(DirectX::XMFLOAT3);