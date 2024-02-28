#include "CCannon.h"
#include"direct3d.h"
#include "CArrow.h"
#include"CScene.h"
#include"CEffectManeger.h"
#include"xa2.h"

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
	for (auto it : effect)
	{
		CLASS_DELETE(it);
		it++;
	}

	effect.clear();
}

void CCannon::SetStageSize(CGrid::GRID_XY _set)
{
	stageSize = _set;
}

void CCannon::Update()
{
	dotween->Update();
	CGridObject::Update();
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
}

void CCannon::Draw()
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

void CCannon::Fire(int _dir)
{
	Vector3 _pos = mTransform.pos;
	Vector3 _Scale = mTransform.scale;
	_Scale.x = _Scale.x * CANNON_FIRE_SCALE;
	_Scale.y = _Scale.y * CANNON_FIRE_SCALE;
	// 右 or 左なら　大砲動かす
	_pos.z -= 0.00001f;
	switch (_dir)
	{
	case 0:
		_pos.x = _pos.x + (0.3f * mTransform.scale.x);
		_pos.y = _pos.y + (0.4f * mTransform.scale.y);
		_pos.z -= 0.100002f;
		break;
		//左に
	case 1:
		_pos.x = _pos.x - (0.1f * mTransform.scale.x);
		_pos.y = _pos.y + (0.4f * mTransform.scale.y);
		_pos.z -= 0.0002f;
		break;
		//右に
	case 2:
			_pos.x = _pos.x + (0.5f * mTransform.scale.x);
			_pos.y = _pos.y + (0.4f * mTransform.scale.y);
		break;
	case 3:
		_pos.x = _pos.x - (0.3f *  mTransform.scale.x);
		_pos.y = _pos.y + (0.3f *  mTransform.scale.y);
		_pos.z += 0.00002f;
		break;
	default:
		break;
	}
	effect.push_back(EffectManeger::GetInstance()->Play(_pos, _Scale, EffectManeger::FX_TYPE::CANNON_FIRE, false));
}

void CCannon::DirSelect(Player::DIRECTION _dir)
{
	//向きに合わせて回転を使う
	//dynamic_cast<CannonAnim*>(mAnim)->PlayTurn
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

	// 全ての方向をtrue
	for (int i = 0; i < 4; i++)
	{
		canMoveDir[i] = true;
	}
	for (int dirRoop = 0; dirRoop < static_cast<int>(CCannon::DIRECTION::NUM); dirRoop++)
	{
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

		if (_nowTable.objectTable[forwordPos.y][forwordPos.x] == static_cast<short> (CGridObject::BlockType::GALL))
		{
			canMoveDir[dirRoop] = false;
			continue;
		}

		// 移動先がマップ外なら移動できないようにする
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
	dynamic_cast<CannonAnim*>(mAnim)->PlayTurn(_dir, 3.0f);
}

void CCannon::PlayReturn(float _animSpeedRate)
{
	dynamic_cast<CannonAnim*>(mAnim)->PlayReturn(_animSpeedRate * 3.0f);
}

void CCannon::BlowOff(int _dir)
{
	switch (_dir)
	{
		//右に
	case 0:
	case 2:
		dotween->DoMoveXY({ MAX_POS_X + mTransform.scale.x / 2, MAX_POS_Y + 2.0f }, BLOWOFF_TIME / 2);
		dotween->Join(360.0f, BLOWOFF_TIME / 2, DoTween::FUNC::ROTATION);
		break;

		//左に
	case 1:
	case 3:
		dotween->DoMoveXY({ (MAX_POS_X * -1.0f) - mTransform.scale.x / 2,MAX_POS_Y + 2.0f }, BLOWOFF_TIME / 2);
		dotween->Join(360.0f, BLOWOFF_TIME, DoTween::FUNC::ROTATION);
		break;
	default:
		break;
	}
}

void CCannon::InPlayer()
{
	Vector3 pos = mTransform.pos;
	pos.y += mTransform.scale.y / 2.0f;
	pos.z -= 0.0001f;
	Vector3 scale = mTransform.scale;
	scale.x *= CANNON_IN_SCALE;
	scale.y *= CANNON_IN_SCALE;
	 effect.push_back(EffectManeger::GetInstance()->Play(pos, scale, EffectManeger::FX_TYPE::CANNON_IN, false));
	 XA_Play(SOUND_LABEL::S_INCANNON);
}
