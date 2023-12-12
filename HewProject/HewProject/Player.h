#pragma once
#include "CObject.h"
#include <iostream>

class CGrid;

// �v���C���[�i���X�j�̃I�u�W�F�N�g�N���X
class Player: 
	public CObject
{
	// �O���b�h�N���X�̃|�C���^
	std::shared_ptr<CGrid> grid;

public:
	Player(D3DBUFFER vb, D3DTEXTURE tex);

	void Update() override;
	// �v���C���[���ړ�����֐�(1�}�X����)
	void Move();

	void Draw() override;

	~Player();

	CGrid* GetGrid();
};

