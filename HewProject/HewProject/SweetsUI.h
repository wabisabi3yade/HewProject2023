#pragma once

#include "UI.h"

class SweetsUI
{
	UI* Sweets;
public:
	
	bool isResporn;   //���X�|�[���t���O
	bool isON;        //DoTween�p�t���O

	float pos;     //�����n�_
	float speed;   //���b�ŗ������邩

	Vector3 vCopy;   //���X�|�[���ꏊ

	SweetsUI(D3DBUFFER _sweetsBuffer, D3DTEXTURE _sweetsTex);

	~SweetsUI();

	void Update();

	void Draw();

	//�X�P�[���ݒ�
	void SetScale(const Vector3& _scale);

	//�|�W�V�����ݒ�
	void SetPosition(const Vector3& _position);

	//��]�ݒ�
	void SetRotation(const Vector3& _rotation);

	//�����ꏊ�ƕb�ݒ�
	void SetPosSpeed(const float _pos, const float _speed);

	//Z��]�p
	void SetRotateZ(const float rotatez);

	//�e�N�X�`�����Z�b�g
	void SetTexture(const D3DTEXTURE _tex);
};

