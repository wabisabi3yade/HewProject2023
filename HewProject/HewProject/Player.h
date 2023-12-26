#pragma once
#include "CGridObject.h"
#include <iostream>
#include "CGrid.h"
#include "PlayerMove.h"

// �v���C���[�i���X�j�̃I�u�W�F�N�g�N���X
class Player :
	public CGridObject
{
public:


	enum class STATE
	{
		NORMAL,	// �ʏ�
		THIN,	// �K��
		FAT,	// �f�u
		MUSCLE,	// �}�b�`��
		NUM
	};

private:
	std::shared_ptr<PlayerMove> move;

	int calorie;	// �J�����[

	int nowFloor;	// �����w�ڂɂ��邩

public:

	Player(D3DBUFFER vb, D3DTEXTURE tex);

	void Update() override;

	void Draw() override;

	~Player();

	bool GetIsMoving()const;

	int GetDirection()const;

	PlayerMove* GetPlayerMove()const;
};

