#include "CWakamuraScene.h"
#include "CSceneManager.h"
#include "Ckcal_gauge.h"

#include "Player.h"
#include <string>


CWakamuraScene::CWakamuraScene()
{
	D3D_CreateSquare({ 3,4 }, &playerBuffer);
	D3D_LoadTexture(L"asset/wakamura/char01.png", &playerTexture);

	player = new Player(playerBuffer, playerTexture);
	
	test = new Ckcal_gauge();
}

CWakamuraScene::~CWakamuraScene()
{
	CLASS_DELETE(test);
	CLASS_DELETE(player);

	SAFE_RELEASE(playerBuffer);
}

void CWakamuraScene::Update()
{
	player->Update();
}

void CWakamuraScene::LateUpdate()
{

}

void CWakamuraScene::Draw()
{



}
