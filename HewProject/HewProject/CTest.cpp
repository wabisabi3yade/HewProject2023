#include "CTest.h"
#include "CSceneManager.h"

CTest::CTest()
{
	D3D_CreateSquare({ 3.0f, 3.0f }, { 3,4 }, &charBuffer);
	D3D_LoadTexture(L"asset/hashimoto/hashimoto.png", &charTexture);

	charObj = new CObject(charBuffer, charTexture);
}

CTest::~CTest()
{
	CLASS_DELETE(charObj);

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
	charObj->Draw();
}
