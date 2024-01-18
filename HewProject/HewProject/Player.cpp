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
	fallFloorChange = false;

	// プレイヤーが扱うテクスチャをここでロードして、各状態の配列に入れていく
	TextureInput(L"asset/Player/N_Walk.png", STATE::NORMAL, ANIM_TEX::WALK);
	TextureInput(L"asset/Player/F_Walk.png", STATE::FAT, ANIM_TEX::WALK);
	TextureInput(L"asset/Player/T_Walk.png", STATE::THIN, ANIM_TEX::WALK);
	TextureInput(L"asset/Player/M_Walk01_Forword.png", STATE::MUSCLE, ANIM_TEX::WALK);
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

	dotween->Update();

	if (move->GetIsFalling() == false)
	{
		if (move->GetIsWalk_Old() == false && move->GetIsWalk_Now() == true)
		{
			dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(direction));
		}
		else if (move->GetIsWalk_Old() == true && move->GetIsWalk_Now() == false)
		{
			dynamic_cast<CPlayerAnim*>(mAnim)->StopWalk();
		}
	}
	else
	{
		switch (nowFloor)
		{
		case 1:
			if (mTransform.pos.y <= (FALL_POS_Y - mTransform.scale.y / 2))
			{
				move->MoveAfter();
				move->FallAfter();
				GameOver();
			}
			break;
		case 2:
		case 3:
			if (mTransform.pos.y <= FALL_POS_Y - mTransform.scale.y / 2)
			{
				mTransform.pos.y = (FALL_POS_Y * -1.0f) /*+ mTransform.scale.y / 2*/;  //最終地点の反対 ＝ 画面の最上部地点
				fallFloorChange = true;
			}
			if (fallFloorChange && mTransform.pos == gridTable->GridToWorld(this->GetGridPos(), CGridObject::BlockType::START))
			{
				move->FallAfter();
				move->MoveAfter();
			}
			break;
		default:
			break;
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
		SetTexture(normalTex[0]);
		break;

	case STATE::FAT:
		move = std::make_shared<FatMove>(this);
		playerState = STATE::FAT;
		SetTexture(fatTex[0]);
		break;

	case STATE::THIN:
		move = std::make_shared<ThinMove>(this);
		playerState = STATE::THIN;
		SetTexture(thinTex[0]);
		break;

	case STATE::MUSCLE:
		move = std::make_shared<MuscleMove>(this);
		playerState = STATE::MUSCLE;
		SetTexture(muscleTex[0]);
		this->calorie = CAKE_CALORIE;
		break;
	}

	// 移動できる方向を更新
	move->CheckCanMove();
}

void Player::Draw()
{
	CObject::Draw();
}

void Player::Fall()
{
	dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(direction), 2.0f);
	move->FallStart();
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

