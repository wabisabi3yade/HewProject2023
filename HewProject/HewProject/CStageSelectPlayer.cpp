#include "CStageSelectPlayer.h"
#include "CPlayerAnim.h"
#include "InputManager.h"
#include "Direct3D.h"

#define STAGESELECT_SPEED (0.05f)	// �v���C���[���x
#define STAGESELECT_PLAYER_ANIMSPD (0.2f)	// �v���C���[�A�j�����x
#define SCREEN_RIGHT_MAX (7.0f)   //��ʉE�[
#define SCREEN_LEFT_MAX (-7.0f)   //��ʍ��[
#define SCREEN_UP_MAX (3.6f)      //��ʏ�[
#define SCREEN_DOWN_MAX (-3.7f)   //��ʉ��[
CStageSelectPlayer::CStageSelectPlayer(D3DBUFFER vb, D3DTEXTURE tex) :CObject(vb, tex)
{
	playerDir = DIRECTION::DOWN;

	// �A�j���[�V�������쐬
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

	//�����Ȃ��x�N�g���ɐݒ�
	d.x = 0;
	d.y = 0;
	d.z = 0;

	mDir = { 0 };

	// ���t���[���t���O���~�낷
	isMoving = false;
	static bool o_isMoving = false;

	static bool isDown = false;	// �������Ă��邩�t���O
	static bool isLeft = false;	// �������Ă��邩�t���O

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
	

	if (isMoving)	// �����Ă���Ȃ�
	{
		if (isDown)	// ������
		{
			if (isLeft)	// ������
			{
				playerDir = DIRECTION::LEFT;
				walkAnimPattern = CPlayerAnim::PATTERN::WALK_LEFT;

			}
			else	// �E����
			{
				playerDir = DIRECTION::DOWN;
				walkAnimPattern = CPlayerAnim::PATTERN::WALK_DOWN;
			
			}

		}
		else	// �����
		{
			if (isLeft)	// ������
			{
				playerDir = DIRECTION::UP;
				walkAnimPattern = CPlayerAnim::PATTERN::WALK_UP;

			}
			else	// �E����
			{
				playerDir = DIRECTION::RIGHT;
				walkAnimPattern = CPlayerAnim::PATTERN::WALK_RIGHT;

			}
		}


		// �A�j���[�V�����̌�����ݒ肷��
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


	// �����n�߂��u��
	if (isMoving && !o_isMoving)
	{
		// �����A�j���[�V����������
		dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(playerDir));
		isWait = false;
	}
	// �������~�܂����u��
	else if (!isMoving && o_isMoving)
	{
		// �A�j���[�V�������~�߂�
		// �����Ă��������
		dynamic_cast<CPlayerAnim*>(mAnim)->StopWalk(static_cast<int>(playerDir));
		isWait = true;
	}

	// �O�̃t���O��Ԃ������Ă���
	o_isMoving = isMoving;

	// XMFLOAT3�^�ɕϊ�����
	mDir = dirChangeVec3(d);

	//�P�ʃx�N�g��������i���̒������P�ɂ���j���@���K��
	DirectX::XMVECTOR v = DirectX::XMLoadFloat3(dirChange(mDir));   //�x�N�g���v�Z�p�̌^�ɓ����
	v = DirectX::XMVector3Normalize(v);   //���K������
	DirectX::XMStoreFloat3(dirChange(mDir), v);   //���̕ϐ�dir�Ɍ��ʂ�߂�

	//�x�N�g�����g���Ĉړ�
	mTransform.pos.x = mTransform.pos.x + mDir.x * STAGESELECT_SPEED;
	mTransform.pos.y = mTransform.pos.y + mDir.y * STAGESELECT_SPEED;
}

void CStageSelectPlayer::Draw()
{
	CObject::Draw();
}

