#include "WorldSelectPic.h"
#include "DoTween.h"

WorldSelectPic::WorldSelectPic(D3DBUFFER vb, D3DTEXTURE tex)
	:CObject(vb, tex)
{
	dotween = new DoTween(this);
}

void WorldSelectPic::Update()
{
	CObject::Update();

	dotween->Update();
}

void WorldSelectPic::Draw()
{
	CObject::Draw();
}

WorldSelectPic::~WorldSelectPic()
{
	CLASS_DELETE(dotween);
}
