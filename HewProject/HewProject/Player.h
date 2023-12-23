#pragma once
#include "CObject.h"
#include <iostream>
#include "CGrid.h"


class PlayerMove;

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
	std::shared_ptr<PlayerMove> move;

	// �O���b�h�N���X�̃|�C���^
	std::shared_ptr<CGrid> grid;

	int calorie;	// �J�����[

	bool canMove;	// �ړ��\�t���O

	DIR moveDir;

public:
	Player(D3DBUFFER vb, D3DTEXTURE tex);

	void Update() override;

	void Draw() override;

	~Player();

	CGrid* GetGrid();
};

