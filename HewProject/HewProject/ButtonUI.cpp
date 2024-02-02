#include "ButtonUI.h"

ButtonUI::ButtonUI(D3DBUFFER vb, D3DTEXTURE tex)
	: UI(vb, tex)
{
}

void ButtonUI::Draw()
{
	UI::Draw();
}

ButtonUI::~ButtonUI()
{
}

void ButtonUI::SetHighlight(bool _isLight)
{
	uv.y = 0.0f;

	//  2等分の下なので
	if (_isLight)
	{
		uv.y = 0.5f;
	}
}
