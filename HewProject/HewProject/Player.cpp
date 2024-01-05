#include "Player.h"
#include "CGrid.h"
#include "CInput.h"
#include "CPlayerAnim.h"
#include"Ckcal_gauge.h"
#define InitCalorie (10)
#define MaxCalorie (15)

Player::Player(D3DBUFFER vb, D3DTEXTURE tex)
	:CGridObject(vb, tex)
{
	move = std::make_shared<PlayerMove>(this);
	mAnim = new CPlayerAnim();
	mAnim->SetPattern(0);
	mAnim->isStop = false;
	calorie = InitCalorie;
	state = STATE::NORMAL;
	KcalyGauge = new Ckcal_gauge();
	KcalyGauge->SetKcal(10);
}

void Player::Update()
{

	if (move->GetIsMovingTrrger())
	{
		calorie--;
		if (state == STATE::MUSCLE)
		{
			//switch (calorie)
			//{
			//case 5:
			//	mTransform.scale.y /= 1.5f;
			//	break;
			//case 10:
			//	mTransform.scale.y /= 1.5f;
			//	break;
			//case 15:
			//	mTransform.scale.y /= 1.5f;
			//	break;
			//default:
			//	break;
			//}
		}
		//プレイヤーのステートを変更
		else
		{
			switch (calorie)
			{
			case 0:
				//state = STATE::NUM;
				break;
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
				state = STATE::THIN;
				break;
			case 6:
			case 7:
			case 8:
			case 9:
			case 10:
				state = STATE::NORMAL;
				break;
			case 11:
			case 12:
			case 13:
			case 14:
			case 15:
				state = STATE::FAT;
				break;
			default:
				break;
			}
		}
	}
	KcalyGauge->SetKcal(calorie);
	KcalyGauge->Update();
	move->Update();

	if (gInput->GetKeyTrigger(VK_LEFT))
	{
		//dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(2);
	}
	if (gInput->GetKeyTrigger(VK_RIGHT))
	{
		//dynamic_cast <CPlayerAnim*>(mAnim)->PlayWalk(3);
	}

	if (gInput->GetKeyTrigger(VK_BACK))
	{
		//dynamic_cast <CPlayerAnim*>(mAnim)->StopWalk();
	}
}

void Player::Draw()
{
	CObject::Draw();
	KcalyGauge->Draw();
}

void Player::CakeEat()
{
	calorie = 16;
}

void Player::DrinkProtein()
{
	CakeEat();
	state = STATE::MUSCLE;
}

void Player::ChiliEat()
{
	if (calorie >= 2)
	{
		calorie -= 2;
	}
	else
	{
		calorie -= 1;
	}
}

Player::~Player()
{
	CLASS_DELETE(mAnim);
	CLASS_DELETE(KcalyGauge);
}

bool Player::GetIsMoving() const
{
	return move->GetIsMoving();
}

int Player::GetDirection() const
{
	return static_cast<int>(move->GetDirection());
}

Player::STATE Player::GetPlayerState() const
{
	return state;
}

PlayerMove* Player::GetPlayerMove() const
{
	return move.get();
}
