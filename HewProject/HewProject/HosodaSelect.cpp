#include "HosodaSelect.h"
#include "CSceneManager.h"
#include "CDirectWrite.h"


wchar_t templaName[20] = L"asset/StageCsv/";

// ↓asset/StageCsvファイル内に入れたファイル名をここに書く
std::vector<const char*> csvFilePath
{
		"Stage.csv"
};

HosodaSelect::HosodaSelect()
{
	nextScene = 0;
	WriteText = wcscat(templaName, (wchar_t*)csvFilePath[nextScene]);
}

HosodaSelect::~HosodaSelect()
{
}

void HosodaSelect::Update()
{
	if (gInput->GetKeyTrigger(VK_UP))
	{
		nextScene--;

		if (nextScene < 0)
		{
			nextScene = csvFilePath.size() - 1;
		}

		WriteText = wcscat(templaName, (wchar_t*)csvFilePath[nextScene]);

	}

	if (gInput->GetKeyTrigger(VK_DOWN))
	{
		nextScene++;

		if (nextScene > csvFilePath.size())
		{
			nextScene = 0;
		}
		WriteText = wcscat(templaName, (wchar_t*)csvFilePath[nextScene]);
	}

	if (gInput->GetKeyTrigger(VK_RETURN))
	{
		
	}

}

void HosodaSelect::LateUpdate()
{
}

void HosodaSelect::Draw()
{
	char* c;
	wcstombs(c, WriteText, 100);

	Write->SetFont(Font::MelodyLine);
	Write->DrawString(std::string(c), DirectX::XMFLOAT2(90, 100), D2D1_DRAW_TEXT_OPTIONS_NONE);
}
