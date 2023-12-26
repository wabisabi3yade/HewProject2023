#include "Player.h"
#include "CGrid.h"
#include "CInput.h"


Player::Player(D3DBUFFER vb, D3DTEXTURE tex)
	:CGridObject(vb, tex)
{
	move = std::make_shared<PlayerMove>(this);

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

bool Player::GetIsMoving() const
{
	return move->GetIsMoving();
}

int Player::GetDirection() const
{
	return static_cast<int>(move->GetDirection());
}

PlayerMove* Player::GetPlayerMove() const
{
	return move.get();
}
