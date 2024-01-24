#define _CRT_SECURE_NO_WARNINGS

#include "HosodaSelect.h"
#include "CSceneManager.h"
#include "CDirectWrite.h"
#include"CSceneManager.h"



// ↓asset/StageCsv/ファイル内に入れたファイル名をここに書く
std::vector<const wchar_t*> csvFilePath
{
		L"Stage.csv",
		L"Stage2.csv"
};

HosodaSelect::HosodaSelect()
{
	nextScene = 0;

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

	}

	if (gInput->GetKeyTrigger(VK_DOWN))
	{
		nextScene++;

		if (nextScene > csvFilePath.size() - 1 )
		{
			nextScene = 0;
		}
	}

	if (gInput->GetKeyTrigger(VK_RETURN))
	{
		wchar_t textureName[256];
		wcscpy_s(textureName, L"asset/StageCsv/"); // 文字列コピー関数
		wcscat_s(textureName, csvFilePath[nextScene]); // 文字列結合関数
		pSceneManager->SceneChangeStage(textureName);
	}

}

void HosodaSelect::LateUpdate()
{
}

void HosodaSelect::Draw()
{
	// wcstombs 関数を使って wchar_t を char に変換
	size_t len = wcslen(csvFilePath[nextScene]) + 1; // 終端のNULL文字も含めた長さ
	char* mbstr = new char[len * MB_CUR_MAX]; // MB_CUR_MAX はマルチバイト文字の最大サイズ

	wcstombs( mbstr,csvFilePath[nextScene], 100);
	Write->SetFont(Font::MelodyLine);
	Write->DrawString(std::string(mbstr), DirectX::XMFLOAT2(90, 100), D2D1_DRAW_TEXT_OPTIONS_NONE);
}
