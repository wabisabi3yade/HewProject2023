#include "CTest.h"
#include "CSceneManager.h"
#include "Player.h"
#include "CGrid.h"

CTest::CTest()
{
	D3D_CreateSquare({ 3,4 }, &charBuffer);
	D3D_LoadTexture(L"asset/hashimoto/char01.png", &charTexture);

	charObj = new CObject(charBuffer, charTexture);
	charObj->mTransform.scale = { 3.0f,3.0f,1.0f };

	Player* player = new Player(charBuffer, charTexture);

	CGrid* grid = player->GetGrid();
	grid->gridPos.y = 10;
}

CTest::~CTest()
{
	CLASS_DELETE(charObj);

	SAFE_RELEASE(charBuffer);

	SAFE_RELEASE(charTexture);
}

void CTest::Update()
{
	
}

void CTest::LateUpdate()
{
}

void CTest::Draw()
{
	charObj->Draw();
}
