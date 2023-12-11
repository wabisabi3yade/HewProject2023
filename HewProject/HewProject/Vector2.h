#pragma once
#include <d3d11.h>		// DirectX11を使うためのヘッダー
#include<DirectXMath.h> //DirectXの数学関連のヘッダーファイル

// float型の変数2個持つクラス

class Vector2
{

public:
	float x, y;	// float型変数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_x">xの初期値</param>
	/// <param name="_y">yの初期値</param>
	Vector2(float _x = 0, float _y = 0);	

	static Vector2 up;
	static Vector2 down;
	static Vector2 left;
	static Vector2 right;
	static Vector2 one;
	static Vector2 zero;

	Vector2 operator+(Vector2 _v);
	Vector2 operator-(Vector2 _v);
	Vector2 operator*(Vector2 _v);
	Vector2 operator/(Vector2 _v);

	const bool& operator>=(const Vector2& _v)const;

	const bool& operator<=(const Vector2& _v)const;

	const bool& operator>(const Vector2& _v)const;

	const bool& operator<(const Vector2& _v)const;

	const bool& operator==(const Vector2& _v)const;
};

