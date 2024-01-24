#define _CRT_SECURE_NO_WARNINGS

#include "HosodaSelect.h"
#include "CSceneManager.h"
#include "CDirectWrite.h"
#include"CSceneManager.h"



// ��asset/StageCsv/�t�@�C�����ɓ��ꂽ�t�@�C�����������ɏ���
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
		wcscpy_s(textureName, L"asset/StageCsv/"); // ������R�s�[�֐�
		wcscat_s(textureName, csvFilePath[nextScene]); // �����񌋍��֐�
		pSceneManager->SceneChangeStage(textureName);
	}

}

void HosodaSelect::LateUpdate()
{
}

void HosodaSelect::Draw()
{
	// wcstombs �֐����g���� wchar_t �� char �ɕϊ�
	size_t len = wcslen(csvFilePath[nextScene]) + 1; // �I�[��NULL�������܂߂�����
	char* mbstr = new char[len * MB_CUR_MAX]; // MB_CUR_MAX �̓}���`�o�C�g�����̍ő�T�C�Y

	wcstombs( mbstr,csvFilePath[nextScene], 100);
	Write->SetFont(Font::MelodyLine);
	Write->DrawString(std::string(mbstr), DirectX::XMFLOAT2(90, 100), D2D1_DRAW_TEXT_OPTIONS_NONE);
}
