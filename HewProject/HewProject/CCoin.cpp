#include "CCoin.h"
#include"DoTween.h"
constexpr float getScale = 0.1f;
constexpr float getPosY = 0.3f;
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
	//this->mTransform.scale /= this->;
	//dotween->DoMoveY()
}
