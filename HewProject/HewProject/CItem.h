#pragma once
#include "CObject.h"

class CItem:public CObject
{
public:
	float calorie;

public:
	
	//�R���X�g���N�^
	CItem(D3DBUFFER vb, D3DTEXTURE tex, float valcalorie);

	//�f�X�g���N�^
	~CItem();

	//�`��
	void Draw();

	//�X�V
	void Update();

	//Get�֐�
	float GetCalorie()const;

	//�ꉞ�A�G�ꂽ���̏����o����Ƃ�
	//void touch();


};

