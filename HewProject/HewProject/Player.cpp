#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "Player.h"
#include "CGrid.h"
#include "CInput.h"
#include "PlayerMove.h"
#include "NormalMove.h"
#include "FatMove.h"
#include "ThinMove.h"
#include "MuscleMove.h"
#include "TextureFactory.h"

#define START_CALORIE (10)	// スタート時のカロリー
#define CAKE_CALORIE (15)	// ケーキ食べたあとのリスのカロリー
#define CHILI_CALORIE (2)	// とうがらし食べた減るのリスのカロリー

void Player::TextureInput(const wchar_t* _texPath, STATE _set, ANIM_TEX _anim_tex)
{
	D3DTEXTURE tex = NULL;
	D3DTEXTURE* Arry = normalTex;

	switch (_set)
	{
	case STATE::NORMAL:
		/*Arry = normalTex;*/
		break;

	case STATE::FAT:
		Arry = fatTex;
		break;

	case STATE::THIN:
		Arry = thinTex;
		break;

	case STATE::MUSCLE:
		Arry = muscleTex;
		break;
	}
	// テクスチャを管理するクラスから指定したテクスチャを取得する
	D3DTEXTURE texWork = TextureFactory::GetInstance()->Fetch(_texPath);
	// 配列の指定したところにテクスチャ情報を格納する
	Arry[static_cast<int>(_anim_tex)] = texWork;
}

Player::Player(D3DBUFFER vb, D3DTEXTURE tex)
	:CGridObject(vb, tex)
{
	dotween = std::make_unique<DoTween>(this);
	mAnim = new CPlayerAnim();
	mAnim->SetPattern(static_cast<int>(CPlayerAnim::PATTERN::STAY_DOWN));
	mAnim->isStop = false;
	IsgameOver = false;
	fallFloorChangeTrriger = false;
	fallMoveTrriger = false;
	risingChangeTrriger = false;
	risingMoveTrriger = false;
	ChangeCannonTexture = false;

	// プレイヤーが扱うテクスチャをここでロードして、各状態の配列に入れていく
	TextureInput(L"asset/Player/N_Walk.png", STATE::NORMAL, ANIM_TEX::WALK);
	TextureInput(L"asset/Player/N_Wait.png", STATE::NORMAL, ANIM_TEX::WAIT);
	TextureInput(L"asset/Player/F_Walk.png", STATE::FAT, ANIM_TEX::WALK);
	TextureInput(L"asset/Player/F_Wait.png", STATE::FAT, ANIM_TEX::WAIT);
	TextureInput(L"asset/Player/T_Walk.png", STATE::THIN, ANIM_TEX::WALK);
	TextureInput(L"asset/Player/T_Wait.png", STATE::THIN, ANIM_TEX::WAIT);
	TextureInput(L"asset/Player/M_Walk.png", STATE::MUSCLE, ANIM_TEX::WALK);
	TextureInput(L"asset/Player/M_Wait.png", STATE::MUSCLE, ANIM_TEX::WAIT);

	//TextureInput(L"asset/Player/N_EatCake.png", STATE::NORMAL, ANIM_TEX::EAT_CAKE);
	//TextureInput(L"asset/Player/F_EatCake.png", STATE::FAT, ANIM_TEX::EAT_CAKE);
	//TextureInput(L"asset/Player/T_EatCake.png",STATE::THIN,ANIM_TEX::EAT_CAKE),
	//TextureInput(L"asset/Player/N_EatChili.png", STATE::NORMAL, ANIM_TEX::EAT_CHILI);
	//TextureInput(L"asset/Player/F_EatChili.png", STATE::FAT, ANIM_TEX::EAT_CHILI);
	//TextureInput(L"asset/Player/T_EatChili.png", STATE::THIN, ANIM_TEX::EAT_CHILI);


	//punchTex[0] = TextureFactory::GetInstance()->Fetch(L"aseet/Player/M_Punch_Down.png");
	//punchTex[1] = TextureFactory::GetInstance()->Fetch(L"aseet/Player/M_Punch_Left.png");
	//punchTex[2] = TextureFactory::GetInstance()->Fetch(L"aseet/Player/M_Punch_Right.png");
	//punchTex[3] = TextureFactory::GetInstance()->Fetch(L"aseet/Player/M_Punch_Up.png");

	cannonTex = TextureFactory::GetInstance()->Fetch(L"asset/Player/Player_CanonMove.png");
}

void Player::Init(GridTable* _pTable)
{
	// 現在いるグリッドテーブル設定
	SetGridTable(_pTable);
	// 方向を設定する
	direction = DIRECTION::EVERY;

	// 最初は普通状態から始める
	move = std::make_shared<NormalMove>(this);

	// 通常状態から始める
	/*playerState = STATE::NORMAL;*/

	ChangeState(STATE::NORMAL);


	calorie = START_CALORIE;
	/*SetTexture(normalTex[0]);*/



	/*move->CheckCanMove();*/

	//プレイヤーの座標をグリッドテーブルとグリッド座標から求める
	mTransform.pos = GetGridTable()->GridToWorld(Grid->gridPos, CGridObject::BlockType::START);

}

void Player::Update()
{
	// フラグの初期化
	move->FlagInit();

	// ↓FlagInitの後
	move->Input();
	fallMoveTrriger = false;
	risingMoveTrriger = false;

	dotween->Update();

	//fallFloorChangeTrriger = false;
	//risingChangeTrriger = false;

	if (move->GetIsCannonMove())
	{
		move->CannonMove2();
	}

	if (move->GetIsFalling() == false && move->GetIsRising() == false)
	{
		if (move->GetIsWalk_Old() == false && move->GetIsWalk_Now() == true)
		{
			ChangeTexture(ANIM_TEX::WALK);
			dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(direction));
		}
		else if (move->GetIsWalk_Old() == true && move->GetIsWalk_Now() == false)
		{
			ChangeTexture(ANIM_TEX::WAIT);
			dynamic_cast<CPlayerAnim*>(mAnim)->StopWalk(static_cast<int>(this->direction));
		}
	}
	else
	{
		if (move->GetIsFalling() == true)
		{
			switch (nowFloor)
			{
			case 1:
				if (fallMoveTrriger == true)
				{
					move->MoveAfter();
					move->FallAfter();
					GameOver();
				}
				break;
			case 2:
			case 3:
				// 落ちる処理 
				if (fallMoveTrriger == true)
				{
					mTransform.pos.y = (FALL_POS_Y * -1.0f) + mTransform.scale.y / 2;  //最終地点の反対 ＝ 画面の最上部地点
					fallFloorChangeTrriger = true;
				}
				if (mTransform.pos == gridTable->GridToWorld(this->GetPlayerMove()->GetNextGridPos(), CGridObject::BlockType::START) && fallFloorChangeTrriger)
				{
					if (this->gridTable->CheckFloorType(move->GetNextGridPos()) != static_cast<int>(CGridObject::BlockType::HOLL))
					{
						move->WalkAfter();
					}
					move->MoveAfter();
					move->FallAfter();
					move->Step();

					//move->CheckCanMove();
					//move->SetNextGridPos(GetGridPos());
					//move->Move();


					dynamic_cast<CPlayerAnim*>(mAnim)->StopWalk(static_cast<int>(this->direction));
					nowFloor--;
					fallFloorChangeTrriger = false;
				}
				break;
			default:
				break;
			}
		}
		else if (move->GetIsRising() == true)
		{
			//上る処理
			if (risingMoveTrriger == true)
			{
				mTransform.pos.y = FALL_POS_Y - mTransform.scale.y / 2;
				risingChangeTrriger = true;

			}
			if (mTransform.pos == gridTable->GridToWorld(this->move->GetNextGridPos(), CGridObject::BlockType::START) && risingChangeTrriger)
			{
				//move->Move(static_cast<PlayerMove::DIRECTION>(direction));
				move->WalkAfter();
				move->MoveAfter();
				move->Step();
				move->RiseAfter();
				dynamic_cast<CPlayerAnim*>(mAnim)->StopWalk(static_cast<int>(this->direction));
				nowFloor++;
				risingChangeTrriger = false;
			}

		}
	}

}

// 歩いた時のカロリー消費
void Player::WalkCalorie()
{
	calorie--;
	if (calorie < 0) calorie = 0;
}

// ケーキ食べた処理
void Player::EatCake()
{
	calorie = CAKE_CALORIE;
}

// とうがらし
void Player::EatChilli()
{
	calorie -= CHILI_CALORIE;
	if (calorie < 0) calorie = 0;
}

// 状態を変えるときに呼び出す処理
void Player::ChangeState(STATE _set)
{
	// 移動クラスを解放する
	move.reset();

	// 各状態の移動クラスを取得する
	switch (_set)
	{
	case STATE::NORMAL:
		// 通常状態の動きクラスをmoveに確保する
		move = std::make_shared<NormalMove>(this);
		playerState = STATE::NORMAL;
		SetTexture(normalTex[ANIM_TEX::WAIT]);
		break;

	case STATE::FAT:
		move = std::make_shared<FatMove>(this);
		playerState = STATE::FAT;
		SetTexture(fatTex[ANIM_TEX::WAIT]);
		break;

	case STATE::THIN:
		move = std::make_shared<ThinMove>(this);
		playerState = STATE::THIN;
		SetTexture(thinTex[ANIM_TEX::WAIT]);
		break;

	case STATE::MUSCLE:
		move = std::make_shared<MuscleMove>(this);
		playerState = STATE::MUSCLE;
		SetTexture(muscleTex[ANIM_TEX::WAIT]);
		this->calorie = CAKE_CALORIE;
		break;
	}

	dynamic_cast<CPlayerAnim*>(mAnim)->StopWalk(static_cast<int>(direction));

	// 移動できる方向を更新
	move->CheckCanMove();
}

void Player::ChangeTexture(ANIM_TEX _animTex)
{
	if (_animTex == ANIM_TEX::CANNON)
	{
		SetTexture(cannonTex);
		return;
	}
	if (_animTex == ANIM_TEX::EAT_CAKE || _animTex == ANIM_TEX::EAT_CHILI)
	{
		switch (playerState)
		{
		case Player::STATE::NORMAL:
			SetTexture(normalTex[_animTex]);
			break;
		case Player::STATE::THIN:
			SetTexture(thinTex[_animTex]);
			break;
		case Player::STATE::FAT:
			SetTexture(fatTex[_animTex]);
			break;
		default:
			break;
		}
		return;
	}
	if (_animTex == ANIM_TEX::PUNCH)
	{
		SetTexture(punchTex[static_cast<int>(direction)]);
		return;
	}

	switch (playerState)
	{
	case Player::STATE::NORMAL:
		SetTexture(normalTex[_animTex]);
		break;
	case Player::STATE::THIN:
		//if (_animTex == ANIM_TEX::WAIT)
		//	mAnim->animSpeed = 2.0f;
		SetTexture(thinTex[_animTex]);
		break;
	case Player::STATE::FAT:
		SetTexture(fatTex[_animTex]);
		break;
	case Player::STATE::MUSCLE:
		SetTexture(muscleTex[_animTex]);
		break;
	default:
		break;
	}
}

void Player::Draw()
{
	CObject::Draw();
}

void Player::Fall()
{
	dynamic_cast<CPlayerAnim*>(mAnim)->PlayFall(static_cast<int>(direction), 2.0f);
	move->FallStart();
}

void Player::Rise()
{
	dynamic_cast<CPlayerAnim*>(mAnim)->PlayFall(static_cast<int>(direction), 2.0f);
	move->RiseStart();
}

// テクスチャは解放しない
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
	return static_cast<int>(direction);
}

PlayerMove* Player::GetPlayerMove() const
{
	return move.get();
}

void Player::SetNowFloor(int _set)
{
	nowFloor = _set;
}

void Player::GameOver()
{
	IsgameOver = true;
}

void Player::SetDirection(int _set)
{
	direction = static_cast<DIRECTION>(_set);
}

