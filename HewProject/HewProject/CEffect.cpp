#include "CEffect.h"
#include "CEffectAnim.h"

CEffect::CEffect(D3DBUFFER vb, D3DTEXTURE tex)
	:CObject(vb, tex)
{
	mAnim = new CEffectAnim();
}

void CEffect::Update()
{
}

void CEffect::Draw()
{
	CObject::Draw();
}

CEffect::~CEffect()
{
	CLASS_DELETE(mAnim);
}
