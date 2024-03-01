#include "Player.h"
#include "CGrid.h"
#include "CInput.h"
#include "PlayerMove.h"
#include "NormalMove.h"
#include "FatMove.h"
#include "ThinMove.h"
#include "MuscleMove.h"
#include "TextureFactory.h"
#include"CalorieGage_hori.h"
#include"CCamera.h"
#include"xa2.h"

#define START_CALORIE (8)	// スタート時のカロリー
#define CHILI_CALORIE (2)	// とうがらし食べた減るのリスのカロリー
constexpr float GAMEOVER_TIME = 1.0f; //カロリーが０になってから何秒後にゲームオーバーになるか

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
	IsStop = false;
	isCasetellaPush = false;
	PlayMakeover = false;
	gameOverOnes = false;
	isEatTrigger = false;

	// プレイヤーが扱うテクスチャをここでロードして、各状態の配列に入れていく
	TextureInput(L"asset/Player/N_Walk.png", STATE::NORMAL, ANIM_TEX::WALK);
	TextureInput(L"asset/Player/N_Wait.png", STATE::NORMAL, ANIM_TEX::WAIT);
	TextureInput(L"asset/Player/F_Walk.png", STATE::FAT, ANIM_TEX::WALK);
	TextureInput(L"asset/Player/F_Wait.png", STATE::FAT, ANIM_TEX::WAIT);
	TextureInput(L"asset/Player/T_Walk.png", STATE::THIN, ANIM_TEX::WALK);
	TextureInput(L"asset/Player/T_Wait.png", STATE::THIN, ANIM_TEX::WAIT);
	TextureInput(L"asset/Player/M_Walk.png", STATE::MUSCLE, ANIM_TEX::WALK);
	TextureInput(L"asset/Player/M_Wait.png", STATE::MUSCLE, ANIM_TEX::WAIT);

	TextureInput(L"asset/Player/N_EatCake.png", STATE::NORMAL, ANIM_TEX::EAT_CAKE);
	TextureInput(L"asset/Player/F_EatCake.png", STATE::FAT, ANIM_TEX::EAT_CAKE);
	TextureInput(L"asset/Player/T_EatCake.png", STATE::THIN, ANIM_TEX::EAT_CAKE),
		TextureInput(L"asset/Player/N_EatChili.png", STATE::NORMAL, ANIM_TEX::EAT_CHILI);
	TextureInput(L"asset/Player/F_EatChili.png", STATE::FAT, ANIM_TEX::EAT_CHILI);
	TextureInput(L"asset/Player/T_EatChili.png", STATE::THIN, ANIM_TEX::EAT_CHILI);
	TextureInput(L"asset/Player/T_EatChili.png", STATE::THIN, ANIM_TEX::EAT_CHILI);

	TextureInput(L"asset/Player/N_Aseri.png", STATE::NORMAL, ANIM_TEX::PANIC);
	TextureInput(L"asset/Player/F_Aseri.png", STATE::FAT, ANIM_TEX::PANIC);
	TextureInput(L"asset/Player/T_Aseri.png", STATE::THIN, ANIM_TEX::PANIC);
	TextureInput(L"asset/Player/M_Aseri.png", STATE::MUSCLE, ANIM_TEX::PANIC);

	TextureInput(L"asset/Player/N_Drink.png", STATE::NORMAL, ANIM_TEX::DRINK);
	TextureInput(L"asset/Player/F_Drink.png", STATE::FAT, ANIM_TEX::DRINK);
	TextureInput(L"asset/Player/T_Drink.png", STATE::THIN, ANIM_TEX::DRINK);

	punchTex[0] = TextureFactory::GetInstance()->Fetch(L"asset/Player/M_Punch_Down.png");
	punchTex[1] = TextureFactory::GetInstance()->Fetch(L"asset/Player/M_Punch_Left.png");
	punchTex[2] = TextureFactory::GetInstance()->Fetch(L"asset/Player/M_Punch_Right.png");
	punchTex[3] = TextureFactory::GetInstance()->Fetch(L"asset/Player/M_Punch_Up.png");

	castellaPushTex = TextureFactory::GetInstance()->Fetch(L"asset/Player/F_PushWalk.png");

	GallEatTex = TextureFactory::GetInstance()->Fetch(L"asset/Player/12komaEat_L.png");

	GameOverTex = TextureFactory::GetInstance()->Fetch(L"asset/Player/collapse.png");

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

	if (calorie > 8)
	{
		ChangeState(STATE::FAT);
	}
	else
	{
		ChangeState(STATE::NORMAL);
	}
	/*SetTexture(normalTex[0]);*/

	calorieGage->SetCalorie(calorie);

	/*move->CheckCanMove();*/

	//プレイヤーの座標をグリッドテーブルとグリッド座標から求める
	mTransform.pos = GetGridTable()->GridToWorld(Grid->gridPos, CGridObject::BlockType::START);

}

void Player::Update()
{
	// フラグの初期化
	move->FlagInit();
	isCasetellaPush = false;
	IsPlayMakeoverTrigger = false;
	isEatTrigger = false;
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

			if (isCasetellaPush)
			{
				isCasetellaPush = false;
				ChangeTexture(ANIM_TEX::PUSH_CASTELLA);
				dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(direction), 0.7f);
			}
			//IsStop = false;
		}
		else if (move->GetIsWalk_Old() == true && move->GetIsWalk_Now() == false && isEat == false)
		{
			ChangeTexture(ANIM_TEX::WAIT);
			dynamic_cast<CPlayerAnim*>(mAnim)->StopWalk(static_cast<int>(this->direction));
			//IsStop = true;
		}
	}
	else
	{
		if (move->GetIsFalling() == true)
		{
			// 落ちる処理 
			if (fallMoveTrriger == true)
			{
				if (this->GetNowFloor() == 1)
				{
					XA_Play(SOUND_LABEL::S_GAMEOVER);
					this->GameOver();
					return;
				}
				mTransform.pos.y = (FALL_POS_Y * -1.0f) + mTransform.scale.y / 2;  //最終地点の反対 ＝ 画面の最上部地点
				fallFloorChangeTrriger = true;
			}
			if (mTransform.pos == gridTable->GridToWorld(this->GetPlayerMove()->GetNextGridPos(), CGridObject::BlockType::START, static_cast<int>(this->playerState)) && fallFloorChangeTrriger)
			{
				if (this->gridTable->CheckFloorType(move->GetNextGridPos()) != static_cast<int>(CGridObject::BlockType::HOLL))
				{
					move->WalkAfter();
				}
				move->Step();
				fallFloorChangeTrriger = false;
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
			if (mTransform.pos == gridTable->GridToWorld(this->move->GetNextGridPos(), CGridObject::BlockType::START, static_cast<int>(this->playerState)) && risingChangeTrriger)
			{
				//move->Move(static_cast<PlayerMove::DIRECTION>(direction));
				move->WalkAfter();
				this->SetGridPos(move->GetNextGridPos());
				//move->MoveAfter();
				XA_Play(SOUND_LABEL::S_TYAKUTI);
				Vector3 pos = mTransform.pos;
				Vector3 scale = mTransform.scale;
				pos.z -= 0.000001f;
				pos.y -= 0.1f;
				scale.x *= STAR_BOUND_SCALE;
				scale.y *= STAR_BOUND_SCALE;
				PlayEffect(pos, scale, EffectManeger::FX_TYPE::STAR_BOUND, false);
				move->Step();
				move->RiseAfter();
				risingChangeTrriger = false;
			}

		}
	}

	for (auto it = effect.begin(); it != effect.end();)
	{
		(*it)->Update();
		if ((*it)->GetFxType() == static_cast<int>(EffectManeger::FX_TYPE::AURA))
		{
			(*it)->mTransform.pos = this->mTransform.pos;
			(*it)->mTransform.pos.z += 0.00001f;
			(*it)->mTransform.pos.y -= 0.5f;
		}
		if ((*it)->GetEffectAnim()->GetAnimEnd())
		{
			CLASS_DELETE(*it);
			it = effect.erase(it);
			continue;
		}
		it++;
	}


	if (calorie <= 0 && !gameOverOnes)
	{
		if (playerState != STATE::MUSCLE)
		{
			XA_Play(SOUND_LABEL::S_DOWN);
			ChangeTexture(ANIM_TEX::GAMEOVER);
			dynamic_cast<CPlayerAnim*>(mAnim)->PlayGameOver(static_cast<int>(direction), 1.5f);
			dotween->DelayedCall(GAMEOVER_TIME, [&]()
				{
					XA_Play(SOUND_LABEL::S_GAMEOVER);
					GameOver();
				});
			gameOverOnes = true;
		}
		else
		{
			Vector3 pos = mTransform.pos;
			Vector3 scale = mTransform.scale;

			pos.z -= 0.00001f;
			pos.y += 0.5f * gridTable->GetGridScale().y;
			scale.x *= SMOKE_SCALE;
			scale.y *= SMOKE_SCALE;
			XA_Play(SOUND_LABEL::S_CHANGE);
			PlayEffect(pos, scale, EffectManeger::FX_TYPE::SMOKE_R, false);
			gameOverOnes = true;
			ChangeState(STATE::THIN);
			mTransform.scale.y /= 1.4f;
			mTransform.pos = gridTable->GridToWorld(GetGridPos(), CGridObject::BlockType::START);
			dotween->DelayedCall(1.0f, [&]()
				{
					XA_Play(SOUND_LABEL::S_DOWN);
					ChangeTexture(ANIM_TEX::GAMEOVER);
					dynamic_cast<CPlayerAnim*>(mAnim)->PlayGameOver(static_cast<int>(direction), 1.5f);
					dotween->DelayedCall(GAMEOVER_TIME, [&]()
						{
							XA_Play(SOUND_LABEL::S_GAMEOVER);
							GameOver();
						});
				});
		}
	}
}

// 歩いた時のカロリー消費
void Player::WalkCalorie()
{
	calorie--;
	calorieGage->AddCalorie(-1);
	if (calorie < 0) calorie = 0;
}

// ケーキ食べた処理
void Player::EatCake()
{
	calorie = CAKE_CALORIE;
	calorieGage->SetCalorie(CAKE_CALORIE);
}

// とうがらし
void Player::EatChilli()
{
	calorie -= CHILI_CALORIE;
	calorieGage->AddCalorie(-2);
	if (calorie < 0) calorie = 0;
}

// 状態を変えるときに呼び出す処理
void Player::ChangeState(STATE _set)
{
	bool o_isMoveTrigger = false;
	bool o_iswataame = false;
	if (move.get() != nullptr)
	{
		o_isMoveTrigger = move->GetIsMoveTrigger();
		o_iswataame = move->GetMoveWataame();
	}

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
		PlayMakeover = false;
		break;

	case STATE::FAT:
		move = std::make_shared<FatMove>(this);
		playerState = STATE::FAT;
		SetTexture(fatTex[ANIM_TEX::WAIT]);
		PlayMakeover = false;
		break;

	case STATE::THIN:
		move = std::make_shared<ThinMove>(this);
		playerState = STATE::THIN;
		SetTexture(thinTex[ANIM_TEX::WAIT]);
		PlayMakeover = false;
		break;

	case STATE::MUSCLE:
		move = std::make_shared<MuscleMove>(this);
		SetTexture(muscleTex[ANIM_TEX::WAIT]);
		if (!PlayMakeover)
		{
			ChangeTexture(Player::ANIM_TEX::PANIC);
			IsPlaymakeover = true;
			PlayMakeover = true;
			IsPlayMakeoverTrigger = true;
		}
		else
		{
			this->mTransform.scale.y *= 1.5f;
		}
		playerState = STATE::MUSCLE;
		break;
	}

	move->SetMoveTrigger(o_isMoveTrigger);

	if (move->GetMoveWataame() != o_iswataame)
		move->SetMoveWataame(o_iswataame);

	dynamic_cast<CPlayerAnim*>(mAnim)->StopWalk(static_cast<int>(direction));
	if (IsPlaymakeover)
	{
		mTransform.pos = gridTable->GridToWorld(Grid->gridPos, CGridObject::BlockType::START);
		dynamic_cast<CPlayerAnim*>(mAnim)->PlayMakeover(static_cast<int>(direction));
		dotween->DelayedCall(MAKEOVER_TIME, [&]()
			{
				Vector3 pos = mTransform.pos;
				Vector3 scale = mTransform.scale;
				scale.x *= 3.0f;
				scale.y *= 3.0f;
				pos.z -= 0.0001f;
				pos.y += 0.3f * scale.y;
				XA_Play(SOUND_LABEL::S_CHANGE);
				this->PlayEffect(pos, scale, EffectManeger::FX_TYPE::SMOKE_P, false);
				this->mTransform.scale.y *= 1.5f;
				SetTexture(muscleTex[ANIM_TEX::WAIT]);
				mTransform.pos = gridTable->GridToWorld(Grid->gridPos, CGridObject::BlockType::START, static_cast<int>(playerState));
				IsPlaymakeover = false;
			});
	}


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
	else if (_animTex == ANIM_TEX::EAT_CAKE)
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
		isEat = true;
		return;
	}
	else if (_animTex == ANIM_TEX::EAT_CHILI)
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
		isEat = true;
		return;
	}
	else if (_animTex == ANIM_TEX::PUNCH)
	{
		SetTexture(punchTex[static_cast<int>(direction)]);
		return;
	}

	else if (_animTex == ANIM_TEX::PUSH_CASTELLA)
	{
		SetTexture(castellaPushTex);
		return;
	}
	else if (_animTex == ANIM_TEX::PANIC)
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
		case Player::STATE::MUSCLE:
			SetTexture(muscleTex[_animTex]);
			break;
		default:
			break;
		}
		return;
	}
	else if (_animTex == ANIM_TEX::DRINK)
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
		isEat = true;
		return;
	}
	else if (_animTex == ANIM_TEX::GALL_EAT)
	{
		SetTexture(GallEatTex);
		return;
	}
	else if (_animTex == Player::ANIM_TEX::GAMEOVER)
	{
		SetTexture(GameOverTex);
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
	if (effect.size() > 0)
	{
		for (auto it = effect.begin(); it != effect.end(); it++)
		{
			if ((*it)->mTransform.pos.z > this->mTransform.pos.z)
				(*it)->Draw();
		}
	}
	CObject::Draw();
	if (effect.size() > 0)
	{
		for (auto it = effect.begin(); it != effect.end(); it++)
		{
			if ((*it)->mTransform.pos.z < this->mTransform.pos.z)
				(*it)->Draw();
		}
	}
}

void Player::Fall()
{
	ChangeTexture(Player::ANIM_TEX::PANIC);
	dynamic_cast<CPlayerAnim*>(mAnim)->PlayFall(static_cast<int>(direction), 2.0f);
	move->FallStart();
}

void Player::Rise()
{
	ChangeTexture(Player::ANIM_TEX::PANIC);
	dynamic_cast<CPlayerAnim*>(mAnim)->PlayFall(static_cast<int>(direction), 2.0f);
	move->RiseStart();
}

void Player::EatEnd()
{
	dotween->DelayedCall(0.5f, [&]()
		{
			isEat = false;
		});
}

// テクスチャは解放しない
Player::~Player()
{
	CLASS_DELETE(mAnim);


	for (auto it : effect)
	{
		CLASS_DELETE(it);
		it++;
	}

	effect.clear();
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

void Player::PlayEffect(Vector3 _pos, Vector3 _scale, EffectManeger::FX_TYPE _type, bool _isLoop)
{
	effect.push_back(EffectManeger::GetInstance()->Play(_pos, _scale, _type, _isLoop));
}

void Player::Reset()
{
	SetGameOver(false);
}

void Player::Stop(float _stopEndTime)
{
	IsStop = true;
	dotween->DelayedCall(_stopEndTime, [&]()
		{
			IsStop = false;
		});
}

void Player::SetDirection(int _set)
{
	direction = static_cast<DIRECTION>(_set);
}

