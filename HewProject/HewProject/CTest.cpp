#include "CTest.h"
#include "CSceneManager.h"

CTest::CTest()
{
	D3D_CreateSquare({ 3.0f, 3.0f }, { 3,4 }, &charBuffer);
	D3D_LoadTexture(L"asset/hashimoto/char01.png", &charTexture);

	charObj1 = new CObject(charBuffer, charTexture);
}

CTest::~CTest()
{
	CLASS_DELETE(charObj1);

	SAFE_RELEASE(charBuffer);

	SAFE_RELEASE(charTexture);
}

void CTest::Update()
{
	if (gInput->GetKeyTrigger(VK_RETURN))
	{
		CScene::SetScene(CSceneManager::WAKAMURA);
	}
}

void CTest::LateUpdate()
{
}

void CTest::Draw()
{
	charObj1->Draw();
}
