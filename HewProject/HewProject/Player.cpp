#include "Player.h"
#include "CGrid.h"



Player::Player(D3DBUFFER vb, D3DTEXTURE tex)
	:CObject(vb, tex)
{
	// �O���b�h�N���X�̃|�C���^
	grid = std::make_shared<CGrid>();
	grid->gridPos.x = 10;
}

void Player::Update()
{
}

void Player::Draw()
{
}

void Player::Move()
{
}

Player::~Player()
{
}

CGrid* Player::GetGrid()
{
	return grid.get();
}
