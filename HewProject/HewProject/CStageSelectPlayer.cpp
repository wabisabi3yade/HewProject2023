#include "CStageSelectPlayer.h"
#include "CPlayerAnim.h"
#include "CInput.h"
#include "Direct3D.h"

CStageSelectPlayer::CStageSelectPlayer(D3DBUFFER vb, D3DTEXTURE tex) :CObject(vb, tex)
{
	playerDir = DIRECTION::DOWN;

	// �A�j���[�V�������쐬
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

	//�����Ȃ��x�N�g���ɐݒ�
	d.x = 0;
	d.y = 0;
	d.z = 0;

	mDir = { 0 };
	mMoveSpeed = 0.0f;

	// ���t���[���t���O���~�낷
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
		// �E����
		if (d.x > 0.0f)
		{
			// �����
			if (d.y > 0.0f)
			{

			}

			if (d.y < 0.0f)
			{

			}
		}
	}




	// �����n�߂���
	if (isMoving && !o_isMoving)
	{
		dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(1));
	}
	// �������~�܂�����
	else if (!isMoving && o_isMoving)
	{
		dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(1));
	}

	// �O�̃t���O��Ԃ������Ă���
	o_isMoving = isMoving;

	//�L�[����Ńx�N�g�����ݒ肳��Ă�����dir�ɑ������
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

	//�P�ʃx�N�g��������i���̒������P�ɂ���j���@���K��
	DirectX::XMVECTOR v = DirectX::XMLoadFloat3(dirChange(mDir));   //�x�N�g���v�Z�p�̌^�ɓ����
	v = DirectX::XMVector3Normalize(v);   //���K������
	DirectX::XMStoreFloat3(dirChange(mDir), v);   //���̕ϐ�dir�Ɍ��ʂ�߂�

	//�x�N�g�����g���Ĉړ�
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
