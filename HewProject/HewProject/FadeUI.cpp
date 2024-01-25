#include "FadeUI.h"

FadeUI::FadeUI()
{
}

FadeUI::FadeUI(D3DBUFFER vb, D3DTEXTURE tex)
	: UI(vb, tex)
{
}

FadeUI::~FadeUI()
{
}

void FadeUI::Update()
{

}

void FadeUI::Draw()
{
	UI::Draw();
}

void FadeUI::SetBasePos(const Vector3& _setPos)
{
	basePos = _setPos;
	// äÓèÄç¿ïWÇ…ê›íË
	mTransform.pos = basePos + offset;

}


