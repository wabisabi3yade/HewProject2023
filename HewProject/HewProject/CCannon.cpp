#include "CCannon.h"
#include"direct3d.h"
#include "CArrow.h"
#include"CScene.h"
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

CCannon::CCannon(D3DBUFFER vb, D3DTEXTURE tex)
	:CGridObject(vb, tex)
{
	inPlayer = false;
	IsUse = false;
	for (int i = 0; i < static_cast<int>(DIRECTION::NUM); i++)
	{
		Arrow[i] = new CArrow(vb, NULL);
		Arrow[i]->SetOwner(this, static_cast<CArrow::DIRECTION>(i));
	}
}

CCannon::~CCannon()
{
	for (int i = 0; i < static_cast<int>(DIRECTION::NUM); i++)
	{
		CLASS_DELETE(Arrow[i]);
	}
}

void CCannon::SetStageSize(CGrid::GRID_XY _set)
{
	stageSize = _set;
}

void CCannon::Update()
{
	if (inPlayer)
	{
		//����\��
		for (int i = 0; i < static_cast<int>(DIRECTION::NUM); i++)
		{
			if (canMoveDir[i] == true)
			{
				Arrow[i]->Update();
			}

		}
		//���˕����I��

		if (gInput->GetKeyTrigger(VK_TAB))
		{
			if (moveDir == static_cast<DIRECTION>(canMoveDir[static_cast<int>(moveDir)]))
			{
				Fire();
			}

		}
		//�Ȃ񂩂̃L�[�Ŕ���
	}
	CGridObject::Update();
}

void CCannon::Draw()
{
	if (inPlayer)
	{
		//����\��
		for (int i = 0; i < static_cast<int>(DIRECTION::NUM); i++)
		{
			if (canMoveDir[i] == true)
			{
				Arrow[i]->Draw();
			}
		}
	}
	CGridObject::Draw();
}

void CCannon::Fire()
{
	this->inPlayer = false;
}

void CCannon::InPlayer()
{
	inPlayer = true;
}

void CCannon::SetArrow(D3DTEXTURE _tex)
{
	for (int i = 0; i < static_cast<int>(DIRECTION::NUM); i++)
	{
		Arrow[i]->SetArrow(_tex);
	}
}

void CCannon::DirSelect(Player::DIRECTION _dir)
{
	moveDir = static_cast<DIRECTION>(_dir);
}
