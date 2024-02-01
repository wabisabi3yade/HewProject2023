#include "CalorieMark.h"

CalorieMark::CalorieMark(D3DBUFFER vb, D3DTEXTURE tex)
	: UI(vb, tex)
{
}

CalorieMark::~CalorieMark()
{
}

void CalorieMark::Update()
{
	if (!isActive) return;
	if (dotween == nullptr) return;

	dotween->Update();
}

void CalorieMark::Draw()
{
	UI::Draw();
}

void CalorieMark::SetColor(const COLOR& _setColor)
{
	// u���W�����炵�ĐF��ς���
	uv.x = 1.0f / 3 * _setColor;
}
