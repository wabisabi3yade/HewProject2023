#include "CCoin.h"
#include"DoTween.h"
constexpr float GET_SCALE = 0.3f;
constexpr float GET_POS_Y = 1.5f;
constexpr float GET_MOVETIME = 1.5f;
constexpr float GET_TIME = 2.0f;
CCoin::CCoin(D3DBUFFER vb, D3DTEXTURE tex)
	:CItem(vb, tex)
{
	type = BlockType::COIN;
	category = Category::ITEM;
	dotween = std::make_unique<DoTween>(this);
}

CCoin::~CCoin()
{
}

void CCoin::Update()
{
	dotween->Update();
	CItem::Update();
}

void CCoin::Draw()
{
	CItem::Draw();
}

void CCoin::GetCoin()
{
	this->mTransform.scale.x = this->mTransform.scale.x * GET_SCALE;
	this->mTransform.scale.y = this->mTransform.scale.y * GET_SCALE;
	//dotween->DoMoveY(this->mTransform.pos.y + GET_POS_Y ,GET_MOVETIME);
	Vector3 pos(mTransform.pos);
	pos.y += GET_POS_Y;
	dotween->DoEaseOutCubic(pos, GET_MOVETIME);
	dotween->OnComplete([&]()
		{
			isActive = false;
		});
}
