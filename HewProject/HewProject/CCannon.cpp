#include "CCannon.h"
#include"direct3d.h"
#include "CArrow.h"
#include"CScene.h"
#include"CEffectManeger.h"

void CCannon::CheckCanMove()
{
	// �S�Ă̕�����true
	for (int i = 0; i < 4; i++)
	{
		canMoveDir[i] = true;
	}

	//���i�H��̏��̏��ňړ��ł��邩���f���� //////////////////////////
	// 4��������
	for (int dirRoop = 0; dirRoop < static_cast<int>(Player::DIRECTION::NUM); dirRoop++)
	{
		// ���ȊO�����邾���ő��v�Ȃ̂�
		if (!canMoveDir[dirRoop]) continue;

		// ����
		CGrid::GRID_XY d = {};

		switch (static_cast<DIRECTION>(dirRoop))
		{
		case DIRECTION::UP:
			d.y = -1;
			break;

		case DIRECTION::DOWN:
			d.y = 1;
			break;

		case DIRECTION::RIGHT:
			d.x = 1;
			break;

		case DIRECTION::LEFT:
			d.x = -1;
			break;
		}


		// �v���C���[�̐i�s��̃O���b�h���W���擾
		CGrid::GRID_XY forwordPos = this->GetGridPos();
		forwordPos.x += d.x;
		forwordPos.y += d.y;

		// �ړ��悪�}�b�v�O�Ȃ�ړ��ł��Ȃ��悤�ɂ���
		if (forwordPos.x < 0 || forwordPos.y < 0
			|| forwordPos.x  > stageSize.x || forwordPos.y > stageSize.y)
		{
			canMoveDir[dirRoop] = false;
			continue;
		}
	}
	//���i�H��̏��̏��ňړ��ł��邩���f���� //////////////////////////

}

CCannon::CCannon(D3DBUFFER vb, D3DTEXTURE tex, GridTable* _nowTable)
	:CGridObject(vb, tex)
{
	inPlayer = false;
	IsUse = false;
	mAnim = new CannonAnim();
	dotween = std::make_unique<DoTween>(this);
	
}

CCannon::~CCannon()
{
	CLASS_DELETE(mAnim);
	
}

void CCannon::SetStageSize(CGrid::GRID_XY _set)
{
	stageSize = _set;
}

void CCannon::Update()
{
	//mAnim->Update();
	dotween->Update();
	CGridObject::Update();
}

void CCannon::Draw()
{
	CGridObject::Draw();
}

void CCannon::DirSelect(Player::DIRECTION _dir)
{
	//moveDir = static_cast<DIRECTION>(_dir);

	//�����ɍ��킹�ĉ�]���g��
	//dynamic_cast<CannonAnim*>(mAnim)->PlayTurn

		//this->mAnim;
	switch (_dir)
	{
	case Player::DIRECTION::DOWN:
		dynamic_cast<CannonAnim*>(mAnim)->PlayStart(static_cast<int>(DIRECTION::DOWN), 2.0f);
		break;
	case Player::DIRECTION::LEFT:
		dynamic_cast<CannonAnim*>(mAnim)->PlayStart(static_cast<int>(DIRECTION::LEFT), 2.0f);
		break;
	case Player::DIRECTION::RIGHT:
		dynamic_cast<CannonAnim*>(mAnim)->PlayStart(static_cast<int>(DIRECTION::RIGHT), 2.0f);
		break;
	case Player::DIRECTION::UP:
		dynamic_cast<CannonAnim*>(mAnim)->PlayStart(static_cast<int>(DIRECTION::UP), 2.0f);
		break;
	default:
		break;
	}

}
void CCannon::CheckCanMove(const GridTable& _nowTable)
{

	// �S�Ă̕�����true
	for (int i = 0; i < 4; i++)
	{
		canMoveDir[i] = true;
	}
	for (int dirRoop = 0; dirRoop < static_cast<int>(CCannon::DIRECTION::NUM); dirRoop++)
	{
		// ����
		CGrid::GRID_XY d = {};

		switch (static_cast<DIRECTION>(dirRoop))
		{
		case DIRECTION::UP:
			d.y = -1;
			break;

		case DIRECTION::DOWN:
			d.y = 1;
			break;

		case DIRECTION::RIGHT:
			d.x = 1;
			break;

		case DIRECTION::LEFT:
			d.x = -1;
			break;
		}


		// �v���C���[�̐i�s��̃O���b�h���W���擾
		CGrid::GRID_XY forwordPos = this->GetGridPos();
		forwordPos.x += d.x;
		forwordPos.y += d.y;

		// �ړ��悪�}�b�v�O�Ȃ�ړ��ł��Ȃ��悤�ɂ���
		if (forwordPos.x < 0 || forwordPos.y < 0
			|| _nowTable.floorTable[forwordPos.y][forwordPos.x] == 0)
		{
			canMoveDir[dirRoop] = false;
			continue;
		}
	}
}

void CCannon::PlayTurn(int _dir, float _animSpeedRate)
{
	dynamic_cast<CannonAnim*>(mAnim)->PlayTurn(_dir,3.0f);
}

void CCannon::PlayReturn(float _animSpeedRate)
{
	dynamic_cast<CannonAnim*>(mAnim)->PlayReturn(_animSpeedRate * 3.0f);
}

void CCannon::BlowOff(int _dir)
{
	switch (_dir)
	{
		//�E��
	case 0:
	case 2:
		dotween->DoMoveXY({ MAX_POS_X + mTransform.scale.x / 2, MAX_POS_Y + 2.0f }, BLOWOFF_TIME / 2);
		dotween->Join(360.0f, BLOWOFF_TIME / 2, DoTween::FUNC::ROTATION);
		break;

		//����
	case 1:
	case 3:
		dotween->DoMoveXY({ (MAX_POS_X * -1.0f) - mTransform.scale.x / 2,MAX_POS_Y + 2.0f }, BLOWOFF_TIME / 2);
		dotween->Join(360.0f, BLOWOFF_TIME, DoTween::FUNC::ROTATION);
		break;
	default:
		break;
	}
}
