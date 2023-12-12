#include "Player.h"
#include "CGrid.h"

#include <iostream>

Player::Player(D3DBUFFER vb, D3DTEXTURE tex)
	:CObject(vb, tex)
{
	// �O���b�h�N���X�̃|�C���^
	std::shared_ptr<CGrid> grid(new CGrid);
}

Player::~Player()
{
}
