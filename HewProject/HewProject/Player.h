#pragma once
#include "CObject.h"

class CGrid;

// �v���C���[�i���X�j�̃I�u�W�F�N�g�N���X
class Player: 
	public CObject
{
	CGrid* grid;


public:
	Player(D3DBUFFER vb, D3DTEXTURE tex);

	~Player();
};

