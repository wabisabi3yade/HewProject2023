#include "CStageSelectPlayer.h"
#include "CPlayerAnim.h"
#include "CInput.h"
#include "Direct3D.h"

CStageSelectPlayer::CStageSelectPlayer(D3DBUFFER vb, D3DTEXTURE tex) :CObject(vb, tex)
{
	playerDir = DIRECTION::DOWN;

	// アニメーションを作成
	mAnim = new CPlayerAnim();
	//mAnim->SetPattern(static_cast<int>(CPlayerAnim::PATTERTN::));
	mAnim->isStop = false;
	isMoving = false;
	isChangeScene = false;
	isOnAnim_Left = false;
	isOnAnim_Right = false;
	isOnAnim_Up = false;
	isOnAnim_Down = false;
	isDiagonal = false;
	nNumSelectScene = 2;
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
	mMoveSpeed = 0.0f;

	// 毎フレームフラグを降ろす
	isMoving = false;
	static bool o_isMoving = false;


	if (gInput->GetKeyPress(VK_LEFT))
	{
		isMoving = true;
		d.x = -1.0f;
		mMoveSpeed = 0.02f;

		if (isOnAnim_Left == false)
		{
			dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(3));
			isOnAnim_Left = true;
			isOnAnim_Right = false;
			isOnAnim_Up = false;
			isOnAnim_Down = false;
		}

	}

	if (gInput->GetKeyPress(VK_RIGHT))
	{
		isMoving = true;
		d.x = 1.0f;
		mMoveSpeed = 0.02f;

		if (isOnAnim_Right == false)
		{
			dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(2));
			isOnAnim_Right = true;
			isOnAnim_Left = false;
			isOnAnim_Up = false;
			isOnAnim_Down = false;
		}

	}

	if (gInput->GetKeyPress(VK_UP))
	{
		isMoving = true;
		d.y = 1.0f;
		mMoveSpeed = 0.02f;

		if (isOnAnim_Up == false)
		{
			dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(0));
			isOnAnim_Up = true;
			isOnAnim_Left = false;
			isOnAnim_Right = false;
			isOnAnim_Down = false;
		}
	}

	if (gInput->GetKeyPress(VK_DOWN))
	{
		isMoving = true;
		d.y = -1.0f;
		mMoveSpeed = 0.02f;

		if (isOnAnim_Down == false)
		{
			dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(1));
			isOnAnim_Down = true;
			isOnAnim_Left = false;
			isOnAnim_Right = false;
			isOnAnim_Up = false;
		}
	}

	if (isMoving)
	{
		// 右向き
		if (d.x > 0.0f)
		{
			// 上向き
			if (d.y > 0.0f)
			{

			}

			if (d.y < 0.0f)
			{

			}
		}
	}




	// 動き始めたら
	if (isMoving && !o_isMoving)
	{
		dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(1));
	}
	// 動きが止まったら
	else if (!isMoving && o_isMoving)
	{
		dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(1));
	}

	// 前のフラグ状態を持っておく
	o_isMoving = isMoving;

	//キー操作でベクトルが設定されていたらdirに代入する
	if (d.x != 0.0f && d.y != 0.0f)
	{
		mDir = dirChangeVec3(d);
	}

	/*if (mDir.x == -1.0f && mDir.y == 1.0f)
	{
		if (isDiagonal==false)
		{
			dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(3));
			isOnAnim_Left = false;
			isOnAnim_Right = true;
			isOnAnim_Up = true;
			isOnAnim_Down = true;
		}

	}*/

	//単位ベクトル化する（矢印の長さを１にする）＝　正規化
	DirectX::XMVECTOR v = DirectX::XMLoadFloat3(dirChange(mDir));   //ベクトル計算用の型に入れる
	v = DirectX::XMVector3Normalize(v);   //正規化する
	DirectX::XMStoreFloat3(dirChange(mDir), v);   //元の変数dirに結果を戻す

	//ベクトルを使って移動
	mTransform.pos.x = mTransform.pos.x + mDir.x * mMoveSpeed;
	mTransform.pos.y = mTransform.pos.y + mDir.y * mMoveSpeed;
	mTransform.pos.z = mTransform.pos.z + mDir.z * mMoveSpeed;

	CObject::Update();
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
	nNumSelectScene = 2;
}
