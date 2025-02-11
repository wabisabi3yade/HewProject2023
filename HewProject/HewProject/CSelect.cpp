//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>

#include "CSelect.h"
#include "CSceneManager.h"

CSelect::CSelect()
{
	nextScene = CSceneManager::KAWADA;

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
			nextScene = CSceneManager::SCENE_NUM - 1;
		}

		charObj->SetTexture(charTexture[nextScene]);
	}

	if (gInput->GetKeyTrigger(VK_DOWN))
	{
		nextScene++;

		if (nextScene >= CSceneManager::SCENE_NUM)
		{
			nextScene = 0;
		}
		charObj->SetTexture(charTexture[nextScene]);
	}

	if (gInput->GetKeyTrigger(VK_RETURN))
	{
		CScene::SetScene(nextScene);
	}
}

void CSelect::LateUpdate()
{
}

void CSelect::Draw()
{
	charObj->Draw();
}
