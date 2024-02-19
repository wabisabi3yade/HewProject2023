#include "CHoll.h"
#include"DoTween.h"
CHoll::CHoll(D3DBUFFER vb, D3DTEXTURE tex)
	:CGridObject(vb,tex)
{
	type = BlockType::HOLL;
	category = Category::FLOOR;
	this->materialDiffuse.w = 0.5f;
	dotween = std::make_unique<DoTween>(this);
}

CHoll::~CHoll()
{
}

void CHoll::Update()
{
	CGridObject::Update();
	dotween->Update();
}

void CHoll::Draw()
{
	CGridObject::Draw();
}
