#pragma once
#include "CObject.h"
#include <iostream>
#include "CGrid.h"
#include "DoTween.h"

// �v���C���[�i���X�j�̃I�u�W�F�N�g�N���X
class Player: 
	public CObject
{
public:
	enum class DIR
	{
		UP,
		DOWN,
		RIGHT,
		LEFT
	};

private:
	// �O���b�h�N���X�̃|�C���^
	std::shared_ptr<CGrid> grid;

	DoTween* dotween;

	bool canMove;	// �ړ��\�t���O

	DIR moveDir;

public:
	Player(D3DBUFFER vb, D3DTEXTURE tex);

	void Update() override;
	// �v���C���[���ړ�����֐�(1�}�X����)
	void Move();

	void Draw() override;

	~Player();

	CGrid* GetGrid();
};

