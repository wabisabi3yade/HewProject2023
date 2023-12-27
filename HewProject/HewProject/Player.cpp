#include "Player.h"
#include "CGrid.h"
#include "CInput.h"
#include "CPlayerAnim.h"


Player::Player(D3DBUFFER vb, D3DTEXTURE tex)
	:CGridObject(vb, tex)
{
	move = std::make_shared<PlayerMove>(this);
	mAnim = new CPlayerAnim();
	mAnim->SetPattern(0);
	mAnim->isStop = false;
}

void Player::Update()
{
	move->Update();

	if (gInput->GetKeyTrigger(VK_LEFT))
	{
		dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(2);
	}
	if (gInput->GetKeyTrigger(VK_RIGHT))
	{
		dynamic_cast <CPlayerAnim*>(mAnim)->PlayWalk(3);
	}

	if (gInput->GetKeyTrigger(VK_BACK))
	{
		dynamic_cast <CPlayerAnim*>(mAnim)->StopWalk();
	}
}

void Player::Draw()
{
	CObject::Draw();
}

Player::~Player()
{
	CLASS_DELETE(mAnim);
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
