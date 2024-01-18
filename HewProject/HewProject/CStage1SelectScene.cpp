#include "CStage1SelectScene.h"
#include "CSceneManager.h"
#include "CInput.h"
#include "CGridObject.h"
#include "TextureFactory.h"
#include "CStageSelectPlayer.h"

CStage1SelectScene::CStage1SelectScene()
{
	D3D_CreateSquare({ 3,4 }, &playerBuffer);
	playerTexture = TextureFactory::GetInstance()->Fetch(L"asset/Player/N_Walk.png");

	D3D_CreateSquare({ 1,1 }, &stageBuffer);
	stage1Texture = TextureFactory::GetInstance()->Fetch(L"asset/Stage/Castella.png");

	for (int i = 0; i < 4; i++)
	{
		stage[i] = new CGridObject(stageBuffer, stage1Texture);
	}

	player = new CStageSelectPlayer(playerBuffer, playerTexture);
	player->mTransform.scale = { 2,2,1 };
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

CStage1SelectScene::~CStage1SelectScene()
{
	CLASS_DELETE(player);

	for (int i = 0; i < 4; i++)
	{
		CLASS_DELETE(stage[i]);
	}
}

void CStage1SelectScene::Update()
{
	player->Update();
	
	for (int i = 0; i < 4; i++)
	{
		stage[i]->Update();
	}
}

void CStage1SelectScene::LateUpdate()
{
}

void CStage1SelectScene::Draw()
{
	player->Draw();
	
	for (int i = 0; i < 4; i++)
	{
		stage[i]->Draw();
	}
}
