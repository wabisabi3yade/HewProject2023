#include "CWorldSelectScene.h"
#include "CWorldSelectPlayer.h"
#include "CInput.h"
#include "CGridObject.h"
#include "TextureFactory.h"
#include "CPlayerAnim.h"

CWorldSelectScene::CWorldSelectScene()
{
	D3D_CreateSquare({ 3,4 }, &playerBuffer);
	playerTexture = TextureFactory::GetInstance()->Fetch(L"asset/Player/N_Walk.png");

	D3D_CreateSquare({ 1,1 }, &stageBuffer);
	stage1Texture = TextureFactory::GetInstance()->Fetch(L"asset/Stage/Castella.png");

	for (int i = 0; i < 4; i++)
	{
		stage[i] = new CGridObject(stageBuffer, stage1Texture);
	}

	player = new CWorldSelectPlayer(playerBuffer, playerTexture);

	player->mTransform.scale = { 4,4,1 };
	player->mTransform.pos = { 0,-2,0 };

	stage[0]->mTransform.pos = { -6,2,-1 };
	stage[0]->mTransform.scale = { 2,2,1 };
	stage[1]->mTransform.pos = { -3,2,-1 };
	stage[1]->mTransform.scale = { 2,2,1 };
	stage[2]->mTransform.pos = { 3,2,-1 };
	stage[2]->mTransform.scale = { 2,2,1 };
	stage[3]->mTransform.pos = { 6,2,-1 };
	stage[3]->mTransform.scale = { 2,2,1 };

}

CWorldSelectScene::~CWorldSelectScene()
{
	CLASS_DELETE(player);

	for (int i = 0; i < 4; i++)
	{
		CLASS_DELETE(stage[i]);
	}
}

void CWorldSelectScene::Update()
{
	if (player->isChangeScene == true)
	{
		switch (player->nNumSelectScene)
		{
		case 0:
			CScene::SetScene(SCENE_NAME::STAGE1);
			player->FlagInit();
			break;
		case 1:
			break;
		case 2:
			CScene::SetScene(SCENE_NAME::SELECT);
			player->FlagInit();
			break;
		default:
			break;
		}
	}

	for (int i = 0; i < 4; i++)
	{
		stage[i]->Update();
	}

	player->Update();

}

void CWorldSelectScene::LateUpdate()
{
}

void CWorldSelectScene::Draw()
{
	player->Draw();

	for (int i = 0; i < 4; i++)
	{
		stage[i]->Draw();
	}
}
