#include "CStage1SelectScene.h"
#include "CSceneManager.h"
#include "InputManager.h"
#include "CGridObject.h"
#include "TextureFactory.h"
#include "CStageSelectPlayer.h"
#include "Collision.h"
#include "UI.h"

CStage1SelectScene::CStage1SelectScene()
{
	D3D_CreateSquare({ 3,4 }, &playerBuffer);
	playerTexture = TextureFactory::GetInstance()->Fetch(L"asset/Player/N_Walk.png");
	player_waitTexture = TextureFactory::GetInstance()->Fetch(L"asset/Player/N_Wait.png");

	D3D_CreateSquare({ 1,1 }, &stageBuffer);
	stage1Texture = TextureFactory::GetInstance()->Fetch(L"asset/Stage/Castella.png");

	D3D_CreateSquare({ 1,1 }, &wordBuffer);
	wordTexture = TextureFactory::GetInstance()->Fetch(L"asset/Item/Chili.png");

	D3D_CreateSquare({ 1,1 }, &textBuffer);
	textTexture = TextureFactory::GetInstance()->Fetch(L"asset/UI/textBox_Blue.png");

	for (int i = 0; i < 5; i++)
	{
		stage[i] = new CGridObject(stageBuffer, stage1Texture);
	}

	player = new CStageSelectPlayer(playerBuffer, playerTexture);
	player->mTransform.scale = { 2,2,1 };
	player->mTransform.pos = { 0,0,0 };
	player->SetTexture(player_waitTexture);

	Text = new UI(textBuffer,textTexture);
	Text->MakeDotween();
	Text->mTransform.pos = { 2.0f,0.75f,0 };
	Text->mTransform.scale = { 0.4f,0.4f,1 };
	Text->materialDiffuse = { 1,1,1,1 };

	Word = new UI(wordBuffer, wordTexture);
	Word->MakeDotween();
	Word->mTransform.pos = { 2.0f,0.75,-0.1f };
	Word->mTransform.scale = { 0.4f,0.4f,1 };

	stage[0]->mTransform.pos = { -5,2,1 };
	stage[0]->mTransform.scale = { 2,2,1 };
	stage[1]->mTransform.pos = { -5,-2,1 };
	stage[1]->mTransform.scale = { 2,2,1 };
	stage[2]->mTransform.pos = { 5,2,1 };
	stage[2]->mTransform.scale = { 2,2,1 };
	stage[3]->mTransform.pos = { 5,-2,1 };
	stage[3]->mTransform.scale = { 2,2,1 };
	stage[4]->mTransform.pos = { 0,-2,1 };
	stage[4]->mTransform.scale = { 2,2,1 };

	isPlayerMoving = false;
	isOnce = false;
	isUpDown = false;
}

CStage1SelectScene::~CStage1SelectScene()
{
	CLASS_DELETE(player);
	CLASS_DELETE(Text);
	CLASS_DELETE(Word);

	for (int i = 0; i < 5; i++)
	{
		CLASS_DELETE(stage[i]);
	}
}

void CStage1SelectScene::Update()
{
	InputManager* input = InputManager::GetInstance();

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
			CScene::SetScene(SCENE_NAME::TITLE);
			break;
		default:
			break;
		}
	}
	
	for (int i = 0; i < 5; i++)
	{
		CollsionRect(stage[i], player);

		if (CollsionRect(stage[i], player) == true)
		{
			switch (i)
			{
			case 0:
				break;
			case 1:
				break;
			case 2:
			{
				Vector3 target = Text->mTransform.pos;
				target.x = 0.6f;
				Vector3 target_word = Word->mTransform.pos;
				target_word.x = 0.6f;

				Text->dotween->DoEaseOutBack(target, 2.0f);
				Text->dotween->Append(Vector3::zero, 1.0f, DoTweenUI::FUNC::NONE);
				
				Word->dotween->DoEaseOutBack(target_word, 2.0f);
				Word->dotween->Append(Vector3::zero, 1.0f, DoTweenUI::FUNC::NONE);

				Text->dotween->OnComplete([&]() {isOnce = true; });
			}
				break;
			case 3:
				break;
			case 4:
				break;
			default:
				break;
			}
			
			if (input->GetInputTrigger(InputType::DECIDE))
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
				case 4:
					player->nNumSelectScene = 4;
					player->isChangeScene = true;
					break;
				default:
					break;
				}
			}
		}
	}

	if (isOnce == true)
	{
		if (CollsionRect(stage[2], player) == false)
		{
			Vector3 target = Text->mTransform.pos;
			target.x = 2.0f;
			Vector3 target_word = Word->mTransform.pos;
			target_word.x = 2.0f;
			Text->dotween->DoEaseOutBack(target, 2.0f);
			Word->dotween->DoEaseOutBack(target_word, 2.0f);
			isOnce = false;
		}
	}

	Text->Update();
	Word->Update();
	/*if (isPlayerMoving == false)
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
				isPlayerMoving = true;
			});
	}
	else {
		
	}*/
	
	player->Update();

	if (player->isWait == false)
	{
		player->SetTexture(playerTexture);
	}
	else {
		player->SetTexture(player_waitTexture);
	}

	for (int i = 0; i < 5; i++)
	{
		stage[i]->Update();
	}
}

void CStage1SelectScene::LateUpdate()
{
}

void CStage1SelectScene::Draw()
{
	for (int i = 0; i < 5; i++)
	{
		stage[i]->Draw();
	}

	Text->Draw();

	Word->Draw();
	
	player->Draw();
}
