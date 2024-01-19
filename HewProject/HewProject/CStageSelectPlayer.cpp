#include "CStageSelectPlayer.h"
#include "CPlayerAnim.h"
#include "CInput.h"
#include "Direct3D.h"

#define STAGESELECT_SPEED (0.04f)	// プレイヤー速度
#define STAGESELECT_PLAYER_ANIMSPD (0.2f)	// プレイヤーアニメ速度
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
	nNumSelectScene = 7;
}

CStageSelectPlayer::~CStageSelectPlayer()
{
	CLASS_DELETE(mAnim);
}

void CStageSelectPlayer::Update()
{
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

	if (gInput->GetKeyPress(VK_LEFT))
	{
		isMoving = true;
		d.x = -1.0f;
		isLeft = true;
	}

	if (gInput->GetKeyPress(VK_RIGHT))
	{
		isMoving = true;
		d.x = 1.0f;
		isLeft = false;
	}

	if (gInput->GetKeyPress(VK_UP))
	{
		isMoving = true;
		d.y = 1.0f;
		isDown = false;
	}

	if (gInput->GetKeyPress(VK_DOWN))
	{
		isMoving = true;
		d.y = -1.0f;
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


	if (mTransform.pos.x > 7.0f)
	{
		mTransform.pos.x = 7.0f;
	}

	if (mTransform.pos.x < -7.0f)
	{
		mTransform.pos.x = -7.0f;
	}

	if (mTransform.pos.y > 3.6f)
	{
		mTransform.pos.y = 3.6f;
	}

	if (mTransform.pos.y < -3.7f)
	{
		mTransform.pos.y = -3.7f;
	}


	// 動き始めた瞬間
	if (isMoving && !o_isMoving)
	{
		// 歩くアニメーションをする
		dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(playerDir));
	}
	// 動きが止まった瞬間
	else if (!isMoving && o_isMoving)
	{
		// アニメーションを止める
		// 向いている方向に
		dynamic_cast<CPlayerAnim*>(mAnim)->StopWalk(static_cast<int>(playerDir));
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

void CStageSelectPlayer::FlagInit()
{
	mAnim->SetPattern(0);
	mAnim->isStop = false;
	isMoving = false;
	isChangeScene = false;
	isOnAnim_Left = false;
	isOnAnim_Right = false;
	isOnAnim_Up = false;
	isOnAnim_Down = false;
	nNumSelectScene = 7;
}
