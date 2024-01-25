#include "CStage1SelectScene.h"
#include "CSceneManager.h"
#include "CInput.h"
#include "CGridObject.h"
#include "TextureFactory.h"
#include "CStageSelectPlayer.h"
#include "Collision.h"
#include "UI.h"

CStage1SelectScene::CStage1SelectScene()
{
	D3D_CreateSquare({ 3,4 }, &playerBuffer);
	playerTexture = TextureFactory::GetInstance()->Fetch(L"asset/Player/N_Walk.png");

	D3D_CreateSquare({ 1,1 }, &stageBuffer);
	stage1Texture = TextureFactory::GetInstance()->Fetch(L"asset/Stage/Castella.png");

	D3D_CreateSquare({ 1,1 }, &textBuffer);
	textTexture = TextureFactory::GetInstance()->Fetch(L"asset/UI/textBox_Blue.png");

	for (int i = 0; i < 4; i++)
	{
		stage[i] = new CGridObject(stageBuffer, stage1Texture);
	}

	player = new CStageSelectPlayer(playerBuffer, playerTexture);
	player->mTransform.scale = { 2,2,1 };
	player->mTransform.pos = { 0,0,0 };

	Text = new UI(textBuffer,textTexture);
	Text->MakeDotween();
	Text->mTransform.pos = { 0,0,0 };
	Text->mTransform.scale = { 0.1f,0.1f,1 };
	Text->materialDiffuse = { 1,1,1,0 };

	stage[0]->mTransform.pos = { -5,2,1 };
	stage[0]->mTransform.scale = { 2,2,1 };
	stage[1]->mTransform.pos = { -5,-2,1 };
	stage[1]->mTransform.scale = { 2,2,1 };
	stage[2]->mTransform.pos = { 5,2,1 };
	stage[2]->mTransform.scale = { 2,2,1 };
	stage[3]->mTransform.pos = { 5,-2,1 };
	stage[3]->mTransform.scale = { 2,2,1 };

	isPlayerMoving = false;
	isOnce = false;
	isUpDown = false;
}

CStage1SelectScene::~CStage1SelectScene()
{
	CLASS_DELETE(player);
	CLASS_DELETE(Text);

	for (int i = 0; i < 4; i++)
	{
		CLASS_DELETE(stage[i]);
	}
}

void CStage1SelectScene::Update()
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
		case 3:
			break;
		default:
			break;
		}
	}
	
	for (int i = 0; i < 4; i++)
	{
		CollsionRect(stage[i], player);

		if (CollsionRect(stage[i], player) == true)
		{
			if (gInput->GetKeyTrigger(VK_RETURN))
			{
				switch (i)
				{
				case 0:
					player->nNumSelectScene = 0;
					player->isChangeScene = true;
					break;
				case 1:
					player->nNumSelectScene = 1;
					player->isChangeScene = true;
					break;
				case 2:
					player->nNumSelectScene = 2;
					player->isChangeScene = true;
					break;
				case 3:
					player->nNumSelectScene = 3;
					player->isChangeScene = true;
					break;
				default:
					break;
				}
			}
		}
	}

	Text->Update();

	if (isPlayerMoving == false)
	{
		if (isUpDown == false)
		{
			Text->materialDiffuse.w += 0.02f;
		}
		else
		{
			Text->materialDiffuse.w -= 0.01f;
		}

		if (isOnce == false)
		{
			Text->dotween->DoScale({ 1,1,1 }, 1.0f);
			Text->dotween->Append(Vector3::zero, 2.0f, DoTweenUI::FUNC::DELAY);
			Text->dotween->Append(Vector3::zero, 1.0f, DoTweenUI::FUNC::SCALE);
			isOnce = true;
		}

		Text->dotween->OnComplete([&]()
			{
				//Text->dotween->DoDelay(2.0f);
				isPlayerMoving = true;
			});
	}
	else {
		player->Update();
	}
	
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
	for (int i = 0; i < 4; i++)
	{
		stage[i]->Draw();
	}

	Text->Draw();

	player->Draw();
	
}
