#include "CBaum.h"
#include"BaumAnim.h"


CBaum::CBaum(D3DBUFFER vb, D3DTEXTURE tex)
	:CGridObject(vb,tex)
{
	category = Category::OBJECT;
	mAnim = new BaumAnim();
}

CBaum::~CBaum()
{
}

void CBaum::Update()
{
	CGridObject::Update();
}

void CBaum::Draw()
{
	CGridObject::Draw();
}

void CBaum::PlayAnim(int _dir, D3DBUFFER _vb)
{
	dynamic_cast<BaumAnim*>(mAnim)->PlayAnim(_dir,2.0f);
	
	SetVertexBuffer(_vb);
}
