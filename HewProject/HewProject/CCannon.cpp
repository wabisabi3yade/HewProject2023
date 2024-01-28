#include "CCannon.h"
#include"direct3d.h"
#include "CArrow.h"
#include"CScene.h"
void CCannon::CheckCanMove()
{
	// 全ての方向をtrue
	for (int i = 0; i < 4; i++)
	{
		canMoveDir[i] = true;
	}

	//↓進路先の床の情報で移動できるか判断する //////////////////////////
	// 4方向見る
	for (int dirRoop = 0; dirRoop < static_cast<int>(Player::DIRECTION::NUM); dirRoop++)
	{
		// 後ろ以外を見るだけで大丈夫なので
		if (!canMoveDir[dirRoop]) continue;

		// 方向
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


		// プレイヤーの進行先のグリッド座標を取得
		CGrid::GRID_XY forwordPos = this->GetGridPos();
		forwordPos.x += d.x;
		forwordPos.y += d.y;

		// 移動先がマップ外なら移動できないようにする
		if (forwordPos.x < 0 || forwordPos.y < 0
			|| forwordPos.x  > stageSize.x || forwordPos.y > stageSize.y)
		{
			canMoveDir[dirRoop] = false;
			continue;
		}
	}
	//↑進路先の床の情報で移動できるか判断する //////////////////////////

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
		//矢印を表示
		for (int i = 0; i < static_cast<int>(DIRECTION::NUM); i++)
		{
			if (canMoveDir[i] == true)
			{
				Arrow[i]->Update();
			}

		}
		//発射方向選択

		if (gInput->GetKeyTrigger(VK_TAB))
		{
			if (moveDir == static_cast<DIRECTION>(canMoveDir[static_cast<int>(moveDir)]))
			{
				Fire();
			}

		}
		//なんかのキーで発射
	}
	CGridObject::Update();
}

void CCannon::Draw()
{
	if (inPlayer)
	{
		//矢印を表示
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
