#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "Player.h"
#include "CGrid.h"
#include "CInput.h"
#include "PlayerMove.h"
#include "CPlayerAnim.h"
#include "NormalMove.h"
#include "FatMove.h"
#include "ThinMove.h"
#include "MuscleMove.h"

#define START_CALORIE (10)	// スタート時のカロリー
#define CAKE_CALORIE (15)	// ケーキ食べたあとのリスのカロリー
#define CHILI_CALORIE (2)	// とうがらし食べた減るのリスのカロリー

void Player::TextureInput(const wchar_t* _texPath, STATE _set)
{
	D3DTEXTURE tex = NULL;
	std::vector<D3DTEXTURE>* _vector = nullptr;

	switch (_set)
	{
	case STATE::NORMAL:
		_vector = &normalTex;
		break;

	case STATE::FAT:
		_vector = &fatTex;
		break;

	case STATE::THIN:
		_vector = &thinTex;
		break;

	case STATE::MUSCLE:
		_vector = &muscleTex;
		break;
	}
	D3D_LoadTexture(_texPath, &tex);
	_vector->push_back(tex);
}

Player::Player(D3DBUFFER vb, D3DTEXTURE tex)
	:CGridObject(vb, tex)
{
	dotween = std::make_unique<DoTween>(this);

	move = std::make_shared<ThinMove>(this);
	
	// アニメーションを作成
	mAnim = new CPlayerAnim();
	mAnim->SetPattern(0);
	mAnim->isStop = false;

	// プレイヤーが扱うテクスチャをここでロードして、各状態の配列に入れていく
	TextureInput(L"asset/Player/N_Walk01_Forword.png", STATE::NORMAL);
	TextureInput(L"asset/Player/F_Walk01_Forword.png", STATE::FAT);
	TextureInput(L"asset/Player/S_Walk01_Forword.png", STATE::THIN);
	TextureInput(L"asset/Player/M_Walk01_Forword.png", STATE::MUSCLE);

	// 通常状態から始める
	playerState = STATE::NORMAL;
	direction = DIRECTION::UP;
	calorie = START_CALORIE;
}

void Player::Init(GridTable* _pTable)
{
	// 現在いるグリッドテーブル設定
	SetGridTable(_pTable);

	move->CheckCanMove();

	//プレイヤーの座標をグリッドテーブルとグリッド座標から求める
	mTransform.pos = GetGridTable()->GridToWorld(Grid->gridPos, CStageMake::BlockType::START);
	
}

void Player::Update()
{
	// フラグの初期化
	move->FlagInit();

	// ↓FlagInitの後
	move->Input();
	
	dotween->Update();
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

	/*case STATE::MUSCLE:
		move = std::make_shared<MuscleMove>(this);
		break;*/
	}

	// 状態が変わって行けるところも変わるので行ける方向を更新
	move->CheckCanMove();
}

void Player::Draw()
{
	CObject::Draw();
}

Player::~Player()
{
	CLASS_DELETE(mAnim);
	
	for (int i = 0; i < normalTex.size(); i++)
	{
		SAFE_RELEASE(normalTex[i]);
	}
	normalTex.clear();

	for (int i = 0; i < fatTex.size(); i++)
	{
		SAFE_RELEASE(fatTex[i]);
	}
	fatTex.clear();
	for (int i = 0; i < thinTex.size(); i++)
	{
		SAFE_RELEASE(thinTex[i]);
	}
	thinTex.clear();
	for (int i = 0; i < muscleTex.size(); i++)
	{
		SAFE_RELEASE(muscleTex[i]);
	}
	muscleTex.clear();
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

void Player::SetDirection(int _set)
{
	direction = static_cast<DIRECTION>(_set);
}

