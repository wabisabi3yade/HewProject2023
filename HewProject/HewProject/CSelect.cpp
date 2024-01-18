//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>

#include "CSelect.h"
#include "CSceneManager.h"
#include "CDirectWrite.h"
#include <string>

CSelect::CSelect()
{
	nextScene = SCENE_NAME::KAWADA;

	D3D_CreateSquare({ 3.0f,3.0f }, { 1.0f,1.0f }, &charBuffer);

	D3D_LoadTexture(L"asset/hashimoto/kawada.png", &charTexture[0]);
	D3D_LoadTexture(L"asset/hashimoto/tatemizo.png", &charTexture[1]);
	D3D_LoadTexture(L"asset/hashimoto/mizuno.png", &charTexture[2]);
	D3D_LoadTexture(L"asset/hashimoto/wakamura.png", &charTexture[3]);
	D3D_LoadTexture(L"asset/hashimoto/hashimoto.png", &charTexture[4]);

	charObj = new CObject(charBuffer, charTexture[0]);
}

CSelect::~CSelect()
{
	CLASS_DELETE(charObj);

	SAFE_RELEASE(charBuffer);

	for (int i = 0; i < SELECT_SCENE_NUM; i++)
	{
		SAFE_RELEASE(charTexture[i]);
	}
}

void CSelect::Update()
{
	if (gInput->GetKeyTrigger(VK_UP))
	{
		nextScene--;

		if (nextScene < 0)
		{
			nextScene = SCENE_NAME::SCENE_NUM - 1;
		}

		/*	if (nextScene <= CSceneManager::HASHIMOTO)
			{
				charObj->SetTexture(charTexture[nextScene]);
			}
			else
			{
				charObj->SetTexture(NULL);
			}*/

	}

	if (gInput->GetKeyTrigger(VK_DOWN))
	{
		nextScene++;

		if (nextScene >= SCENE_NAME::SCENE_NUM)
		{
			nextScene = 0;
		}

	}

	if (gInput->GetKeyTrigger(VK_RETURN))
	{
		CScene::SetScene(nextScene);
	}

	if (nextScene <= SCENE_NAME::HASHIMOTO)
	{
		charObj->SetTexture(charTexture[nextScene]);
	}
	else
	{
		charObj->SetTexture(NULL);
	}
}

void CSelect::LateUpdate()
{
}

void CSelect::Draw()
{

	charObj->Draw();
	Write->SetFont(Font::MelodyLine);
	Write->DrawString(std::to_string(nextScene), DirectX::XMFLOAT2(90, 100), D2D1_DRAW_TEXT_OPTIONS_NONE);
}
