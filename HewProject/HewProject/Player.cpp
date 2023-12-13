#include "Player.h"
#include "CGrid.h"
#include "CInput.h"

#include "PlayerMove.h"


Player::Player(D3DBUFFER vb, D3DTEXTURE tex)
	:CObject(vb, tex)
{
	// グリッドクラスのポインタ
	grid = std::make_shared<CGrid>();
	grid->gridPos = { 0,0 };

	move = std::make_shared<PlayerMove>(this);

	canMove = true;	// 一旦移動できないようにする
	moveDir = DIR::UP;	// 一旦うえにする
}

void Player::Update()
{
	move->Update();
}

void Player::Draw()
{
	CObject::Draw();
}

Player::~Player()
{
}

CGrid* Player::GetGrid()
{
	return grid.get();
}
