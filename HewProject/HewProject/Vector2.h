#pragma once
#include <d3d11.h>		// DirectX11���g�����߂̃w�b�_�[
#include<DirectXMath.h> //DirectX�̐��w�֘A�̃w�b�_�[�t�@�C��

// float�^�̕ϐ�2���N���X

class Vector2
{

public:
	float x, y;	// float�^�ϐ�

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_x">x�̏����l</param>
	/// <param name="_y">y�̏����l</param>
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

