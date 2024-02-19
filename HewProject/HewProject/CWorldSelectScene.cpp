#include "CWorldSelectScene.h"
#include "CWorldSelectPlayer.h"
#include "InputManager.h"
#include "TextureFactory.h"
#include "CPlayerAnim.h"
#include "UI.h"

CWorldSelectScene::CWorldSelectScene()
{
	D3D_CreateSquare({ 3,4 }, &playerBuffer);
	playerTexture = TextureFactory::GetInstance()->Fetch(L"asset/Player/N_Walk.png");
	player_stopTexture = TextureFactory::GetInstance()->Fetch(L"asset/Player/N_Wait.png");

	D3D_CreateSquare({ 1,1 }, &stageBuffer);
	stage1Texture = TextureFactory::GetInstance()->Fetch(L"asset/Stage/Castella.png");

	for (int i = 0; i < 4; i++)
	{
		stage[i] = new UI(stageBuffer, stage1Texture);
		stage[i]->MakeDotween();
	}

	player = new CWorldSelectPlayer(playerBuffer, playerTexture);

	player->mTransform.scale = { 4,4,1 };
	player->mTransform.pos = { 0,-2.0f,0 };
	player->SetTexture(player_stopTexture);

	stage[0]->mTransform.pos = { 8.0f,2.0f,-1.0f };
	stage[0]->mTransform.scale = { 2,2,1 };
	stage[1]->mTransform.pos = { 16.0f,2.0f,-1.0f };
	stage[1]->mTransform.scale = { 2,2,1 };
	stage[2]->mTransform.pos = { 24.0f,2.0f,-1.0f };
	stage[2]->mTransform.scale = { 2,2,1 };
	stage[3]->mTransform.pos = { 32.0f,2.0f,-1.0f };
	stage[3]->mTransform.scale = { 2,2,1 };

	isStageMove = false;

}

CWorldSelectScene::~CWorldSelectScene()
{
	CLASS_DELETE(player);

	for (int i = 0; i < 4; i++)
	{
		CLASS_DELETE(stage[i]);
	}

	SAFE_RELEASE(playerBuffer);
	SAFE_RELEASE(stageBuffer);
}

void CWorldSelectScene::Update()
{
	InputManager* input = InputManager::GetInstance();
	
	if (isStageMove == false)
	{
		//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
		//＝＝＝右スティックを傾けたら＝＝＝
		//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
		if (input->GetMovement().x > 0)
		{
			if (player->nNumSelectScene < 4)
			{
				isStageMove = true;
				for (int i = 0; i < 4; i++)
				{
					Vector2 playerXY;
					playerXY.x = stage[i]->mTransform.pos.x - 8.0f;
					playerXY.y = stage[i]->mTransform.pos.y;

					stage[i]->dotween->DoMoveX(playerXY.x, 3.0f);
					if (i == 3)
					{
						stage[i]->dotween->OnComplete([&]()
							{
								isStageMove = false;
							});
					}
				}
			}
			
		}


		//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
		//＝＝＝左スティックを傾けたら＝＝＝
		//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
		if (input->GetMovement().x < 0)
		{
			if (player->nNumSelectScene > 0)
			{
				isStageMove = true;
				for (int i = 0; i < 4; i++)
				{
					Vector2 playerXY;
					playerXY.x = stage[i]->mTransform.pos.x + 8.0f;
					playerXY.y = stage[i]->mTransform.pos.y;

					stage[i]->dotween->DoMoveX(playerXY.x, 3.0f);

					if (i == 3)
					{
						stage[i]->dotween->OnComplete([&]()
							{
								isStageMove = false;
							});
					}
				}
			}
			
		}
	}

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	//＝＝＝＝＝シーンチェンジ＝＝＝＝＝
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	if (player->isChangeScene == true)
	{
		switch (player->nNumSelectScene)
		{
		case 0:
			CScene::SetScene(SCENE_NAME::STAGE1);
			break;
		case 1:
			break;
		case 2:
			CScene::SetScene(SCENE_NAME::SELECT);
			break;
		case 3:
			break;
		case 4:
			break;
		default:
			break;
		}
	}

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	//＝＝待機中と移動中でテクスチャを変える＝＝
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	if (player->isMoving == false)
	{
		player->SetTexture(player_stopTexture);
	}
	else {
		player->SetTexture(playerTexture);
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
