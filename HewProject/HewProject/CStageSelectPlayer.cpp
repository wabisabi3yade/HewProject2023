#include "CStageSelectPlayer.h"
#include "CPlayerAnim.h"
#include "InputManager.h"
#include "Direct3D.h"

#define STAGESELECT_SPEED (0.05f)	// プレイヤー速度
#define STAGESELECT_PLAYER_ANIMSPD (0.2f)	// プレイヤーアニメ速度
#define SCREEN_RIGHT_MAX (7.0f)   //画面右端
#define SCREEN_LEFT_MAX (-7.0f)   //画面左端
#define SCREEN_UP_MAX (3.6f)      //画面上端
#define SCREEN_DOWN_MAX (-3.7f)   //画面下端
CStageSelectPlayer::CStageSelectPlayer(D3DBUFFER vb, D3DTEXTURE tex) :CObject(vb, tex)
{
	playerDir = DIRECTION::DOWN;

	// アニメーションを作成
	mAnim = new CPlayerAnim();
	mAnim->animSpeed = STAGESELECT_PLAYER_ANIMSPD;
	//mAnim->SetPattern(static_cast<int>(CPlayerAnim::PATTERTN::));
	mAnim->isStop = false;
	isMoving = false;
	isChangeScene = false;
	isOnAnim_Left = false;
	isOnAnim_Right = false;
	isOnAnim_Up = false;
	isOnAnim_Down = false;
	isDiagonal = false;
	isWait = true;
	nNumSelectScene = 7;
}

CStageSelectPlayer::~CStageSelectPlayer()
{
	CLASS_DELETE(mAnim);
}

void CStageSelectPlayer::Update()
{
	InputManager* input = InputManager::GetInstance();
	
	DirectX::XMFLOAT3 d;

	//方向なしベクトルに設定
	d.x = 0;
	d.y = 0;
	d.z = 0;

	mDir = { 0 };

	// 毎フレームフラグを降ろす
	isMoving = false;
	static bool o_isMoving = false;

	static bool isDown = false;	// 下向いているかフラグ
	static bool isLeft = false;	// 左向いているかフラグ

	d.x = input->GetMovement().x;
	d.y = input->GetMovement().y;


	if (d.x < 0)
	{
		isMoving = true;
		isLeft = true;
	}

	if (d.x > 0)
	{
		isMoving = true;
		isLeft = false;
	}

	if (d.y > 0)
	{
		isMoving = true;
		isDown = false;
	}

	if (d.y < 0)
	{
		isMoving = true;
		isDown = true;
	}

	static CPlayerAnim::PATTERN walkAnimPattern = CPlayerAnim::PATTERN::WALK_DOWN;
	

	if (isMoving)	// 動いているなら
	{
		if (isDown)	// 下向き
		{
			if (isLeft)	// 左向き
			{
				playerDir = DIRECTION::LEFT;
				walkAnimPattern = CPlayerAnim::PATTERN::WALK_LEFT;

			}
			else	// 右向き
			{
				playerDir = DIRECTION::DOWN;
				walkAnimPattern = CPlayerAnim::PATTERN::WALK_DOWN;
			
			}

		}
		else	// 上向き
		{
			if (isLeft)	// 左向き
			{
				playerDir = DIRECTION::UP;
				walkAnimPattern = CPlayerAnim::PATTERN::WALK_UP;

			}
			else	// 右向き
			{
				playerDir = DIRECTION::RIGHT;
				walkAnimPattern = CPlayerAnim::PATTERN::WALK_RIGHT;

			}
		}


		// アニメーションの向きを設定する
		mAnim->SetPattern(static_cast<int>(walkAnimPattern));
		
	}


	if (mTransform.pos.x > SCREEN_RIGHT_MAX)
	{
		mTransform.pos.x = SCREEN_RIGHT_MAX;
	}

	if (mTransform.pos.x < SCREEN_LEFT_MAX)
	{
		mTransform.pos.x = SCREEN_LEFT_MAX;
	}

	if (mTransform.pos.y > SCREEN_UP_MAX)
	{
		mTransform.pos.y = SCREEN_UP_MAX;
	}

	if (mTransform.pos.y < SCREEN_DOWN_MAX)
	{
		mTransform.pos.y = SCREEN_DOWN_MAX;
	}


	// 動き始めた瞬間
	if (isMoving && !o_isMoving)
	{
		// 歩くアニメーションをする
		dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(playerDir));
		isWait = false;
	}
	// 動きが止まった瞬間
	else if (!isMoving && o_isMoving)
	{
		// アニメーションを止める
		// 向いている方向に
		dynamic_cast<CPlayerAnim*>(mAnim)->StopWalk(static_cast<int>(playerDir));
		isWait = true;
	}

	// 前のフラグ状態を持っておく
	o_isMoving = isMoving;

	// XMFLOAT3型に変換する
	mDir = dirChangeVec3(d);

	//単位ベクトル化する（矢印の長さを１にする）＝　正規化
	DirectX::XMVECTOR v = DirectX::XMLoadFloat3(dirChange(mDir));   //ベクトル計算用の型に入れる
	v = DirectX::XMVector3Normalize(v);   //正規化する
	DirectX::XMStoreFloat3(dirChange(mDir), v);   //元の変数dirに結果を戻す

	//ベクトルを使って移動
	mTransform.pos.x = mTransform.pos.x + mDir.x * STAGESELECT_SPEED;
	mTransform.pos.y = mTransform.pos.y + mDir.y * STAGESELECT_SPEED;
}

void CStageSelectPlayer::Draw()
{
	CObject::Draw();
}

