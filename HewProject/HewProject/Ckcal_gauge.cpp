#include "Ckcal_gauge.h"
#include "CScene.h"
#include "CDirectWrite.h"

extern DirectWrite* Write;
void Ckcal_gauge::SetKcal(int kcal)
{
	nKcal = kcal;
}

int Ckcal_gauge::GetKcal()
{
	return nKcal;
}

void Ckcal_gauge::Update()
{
	
	if (gInput->GetKeyTrigger(VK_UP))
	{
		nKcal++;
		if (nKcal > 15)
		{
			nKcal = 15;
		}
	}

	if (gInput->GetKeyTrigger(VK_DOWN))
	{
		nKcal--;
		if (nKcal < 0)
		{
			nKcal = 0;
		}
	}

	Write->nKcal = nKcal;
}

void Ckcal_gauge::Draw()
{
	for (int i = 0; i < nKcal; i++)
	{
		if (i < 6)
		{
			Write->SetFont(Font::HG_Gyosyo, nullptr, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 30, L"ja-jp", DWRITE_TEXT_ALIGNMENT_LEADING, D2D1::ColorF(D2D1::ColorF::Red));
		}
		if (4 < i && i < 10)
		{
			Write->SetFont(Font::HG_Gyosyo, nullptr, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 30, L"ja-jp", DWRITE_TEXT_ALIGNMENT_LEADING, D2D1::ColorF(D2D1::ColorF::Yellow));
		}
		if (9 < i)
		{
			Write->SetFont(Font::HG_Gyosyo, nullptr, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 30, L"ja-jp", DWRITE_TEXT_ALIGNMENT_LEADING, D2D1::ColorF(D2D1::ColorF::Green));
		}
		//Kcal->SetFont(Font::HGçsèëëÃ,nullptr,DWRITE_FONT_WEIGHT_NORMAL,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL,30, L"ja-jp",DWRITE_TEXT_ALIGNMENT_LEADING, D2D1::ColorF(D2D1::ColorF::Yellow));
		Write->DrawString("Å°", DirectX::XMFLOAT2(90 + i * 22, 150), D2D1_DRAW_TEXT_OPTIONS_NONE);
	}
}
