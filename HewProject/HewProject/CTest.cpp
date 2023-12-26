#include "CTest.h"
#include "CSceneManager.h"

#include "Player.h"

CTest::CTest()
{
	D3D_CreateSquare({ 1,1 }, &playerBuffer);
	D3D_LoadTexture(L"asset/hashimoto/N_Walk01_Back.png", &playerTexture);

	/*player = new Player(playerBuffer, playerTexture);*/

	player = std::make_shared<Player>(playerBuffer, playerTexture);
	
}

CTest::~CTest()
{
	/*CLASS_DELETE(player);*/

	SAFE_RELEASE(playerBuffer);

	SAFE_RELEASE(playerTexture);
}

void CTest::Update()
{
	player->Update();
}

void CTest::LateUpdate()
{
}

void CTest::Draw()
{
	player->Draw();
}
