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
	word_RightUpTexture = TextureFactory::GetInstance()->Fetch(L"asset/Item/Chili.png");
	word_RightDownTexture = TextureFactory::GetInstance()->Fetch(L"asset/Item/Cake.png");
	word_LeftUpTexture = TextureFactory::GetInstance()->Fetch(L"asset/Item/Coin.png");
	word_LeftDownTexture = TextureFactory::GetInstance()->Fetch(L"asset/Item/Protein.png");

	D3D_CreateSquare({ 1,1 }, &textBuffer);
	text_blueTexture = TextureFactory::GetInstance()->Fetch(L"asset/UI/textBox_Blue.png");
	text_greenTexture = TextureFactory::GetInstance()->Fetch(L"asset/UI/textBox_Green.png");
	text_pinkTexture = TextureFactory::GetInstance()->Fetch(L"asset/UI/textBox_Pink.png");
	text_purpleTexture = TextureFactory::GetInstance()->Fetch(L"asset/UI/textBox_Purple.png");

	for (int i = 0; i < 5; i++)
	{
		stage[i] = new CGridObject(stageBuffer, stage1Texture);
	}

	player = new CStageSelectPlayer(playerBuffer, playerTexture);
	player->mTransform.scale = { 2,2,1 };
	player->mTransform.pos = { 0,0,0 };
	player->SetTexture(player_waitTexture);

	Text[0] = new UI(textBuffer, text_blueTexture);
	Text[0]->MakeDotween();
	Text[0]->mTransform.pos = {2.0f,0.75f,-0.01f};
	Text[0]->mTransform.scale = {0.4f,0.4f,1};
	Text[0]->materialDiffuse = {1,1,1,1};

	Text[1] = new UI(textBuffer, text_greenTexture);
	Text[1]->MakeDotween();
	Text[1]->mTransform.pos = { -2.0f,0.75f,-0.01f };
	Text[1]->mTransform.scale = { 0.4f,0.4f,1 };
	Text[1]->materialDiffuse = { 1,1,1,1 };

	Text[2] = new UI(textBuffer, text_pinkTexture);
	Text[2]->MakeDotween();
	Text[2]->mTransform.pos = { -2.0f,-0.75f,-0.01f };
	Text[2]->mTransform.scale = { 0.4f,0.4f,1 };
	Text[2]->materialDiffuse = { 1,1,1,1 };

	Text[3] = new UI(textBuffer, text_purpleTexture);
	Text[3]->MakeDotween();
	Text[3]->mTransform.pos = { 2.0f,-0.75f,-0.01f };
	Text[3]->mTransform.scale = { 0.4f,0.4f,1 };
	Text[3]->materialDiffuse = { 1,1,1,1 };

	Word[0] = new UI(wordBuffer, word_RightUpTexture);
	Word[0]->MakeDotween();
	Word[0]->mTransform.pos = {2.0f,0.75,-0.1f};
	Word[0]->mTransform.scale = {0.4f,0.4f,1};

	Word[1] = new UI(wordBuffer, word_RightDownTexture);
	Word[1]->MakeDotween();
	Word[1]->mTransform.pos = { 2.0f,-0.75,-0.1f };
	Word[1]->mTransform.scale = { 0.4f,0.4f,1 };

	Word[2] = new UI(wordBuffer, word_LeftUpTexture);
	Word[2]->MakeDotween();
	Word[2]->mTransform.pos = { -2.0f,0.75,-0.1f };
	Word[2]->mTransform.scale = { 0.4f,0.4f,1 };

	Word[3] = new UI(wordBuffer, word_LeftDownTexture);
	Word[3]->MakeDotween();
	Word[3]->mTransform.pos = { -2.0f,-0.75,-0.1f };
	Word[3]->mTransform.scale = { 0.4f,0.4f,1 };

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

	for (int i = 0; i < 4; i++)
	{
		CLASS_DELETE(Word[i]);
	}

	for (int i = 0; i < 4; i++)
	{
		CLASS_DELETE(Text[i]);
	}

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
			{
				Vector3 target = Text[1]->mTransform.pos;
				target.x = -0.6f;
				Vector3 target_word = Word[2]->mTransform.pos;
				target_word.x = -0.6f;

				Text[1]->dotween->DoEaseOutBack(target, 2.0f);
				Text[1]->dotween->Append(Vector3::zero, 1.0f, DoTweenUI::FUNC::NONE);
				
				Word[2]->dotween->DoEaseOutBack(target_word, 2.0f);
				Word[2]->dotween->Append(Vector3::zero, 1.0f, DoTweenUI::FUNC::NONE);

				Text[1]->dotween->OnComplete([&]() {isOnce = true; });
			}
				break;
			case 1:
			{
				Vector3 target = Text[2]->mTransform.pos;
				target.x = -0.6f;
				Vector3 target_word = Word[3]->mTransform.pos;
				target_word.x = -0.6f;

				Text[2]->dotween->DoEaseOutBack(target, 2.0f);
				Text[2]->dotween->Append(Vector3::zero, 1.0f, DoTweenUI::FUNC::NONE);
				
				Word[3]->dotween->DoEaseOutBack(target_word, 2.0f);
				Word[3]->dotween->Append(Vector3::zero, 1.0f, DoTweenUI::FUNC::NONE);
				
				Text[2]->dotween->OnComplete([&]() {isOnce = true; });
			}
				break;
			case 2:
			{
				Vector3 target = Text[0]->mTransform.pos;
				target.x = 0.6f;
				Vector3 target_word = Word[0]->mTransform.pos;
				target_word.x = 0.6f;

				Text[0]->dotween->DoEaseOutBack(target, 2.0f);
				Text[0]->dotween->Append(Vector3::zero, 1.0f, DoTweenUI::FUNC::NONE);
				
				Word[0]->dotween->DoEaseOutBack(target_word, 2.0f);
				Word[0]->dotween->Append(Vector3::zero, 1.0f, DoTweenUI::FUNC::NONE);

				Text[0]->dotween->OnComplete([&]() {isOnce = true; });
			}
				break;
			case 3:
			{
				Vector3 target = Text[3]->mTransform.pos;
				target.x = 0.6f;
				Vector3 target_word = Word[1]->mTransform.pos;
				target_word.x = 0.6f;

				Text[3]->dotween->DoEaseOutBack(target, 2.0f);
				Text[3]->dotween->Append(Vector3::zero, 1.0f, DoTweenUI::FUNC::NONE);
				
				Word[1]->dotween->DoEaseOutBack(target_word, 2.0f);
				Word[1]->dotween->Append(Vector3::zero, 1.0f, DoTweenUI::FUNC::NONE);

				Text[3]->dotween->OnComplete([&]() {isOnce = true; });
			}
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
		if (CollsionRect(stage[0], player) == false)
		{
			Vector3 target = Text[1]->mTransform.pos;
			target.x = -2.0f;
			Vector3 target_word = Word[2]->mTransform.pos;
			target_word.x = -2.0f;

			Text[1]->dotween->DoEaseOutBack(target, 2.0f);
			Word[2]->dotween->DoEaseOutBack(target_word, 2.0f);
			isOnce = false;
		}
		
		if (CollsionRect(stage[1], player) == false)
		{
			Vector3 target = Text[2]->mTransform.pos;
			target.x = -2.0f;
			Vector3 target_word = Word[3]->mTransform.pos;
			target_word.x = -2.0f;

			Text[2]->dotween->DoEaseOutBack(target, 2.0f);
			Word[3]->dotween->DoEaseOutBack(target_word, 2.0f);
			isOnce = false;
		}

		if (CollsionRect(stage[2], player) == false)
		{
			Vector3 target = Text[0]->mTransform.pos;
			target.x = 2.0f;
			Vector3 target_word = Word[0]->mTransform.pos;
			target_word.x = 2.0f;
			Text[0]->dotween->DoEaseOutBack(target, 2.0f);
			Word[0]->dotween->DoEaseOutBack(target_word, 2.0f);
			isOnce = false;
		}

		if (CollsionRect(stage[3], player) == false)
		{
			Vector3 target = Text[3]->mTransform.pos;
			target.x = 2.0f;
			Vector3 target_word = Word[1]->mTransform.pos;
			target_word.x = 2.0f;
			Text[3]->dotween->DoEaseOutBack(target, 2.0f);
			Word[1]->dotween->DoEaseOutBack(target_word, 2.0f);
			isOnce = false;
		}
	}

	for (int i = 0; i < 4; i++)
	{
		Text[i]->Update();
	}
	
	for (int i = 0; i < 4; i++)
	{
		Word[i]->Update();
	}

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

	player->Draw();

	for (int i = 0; i < 4; i++)
	{
		Text[i]->Draw();
	}

	for (int i = 0; i < 4; i++)
	{
		Word[i]->Draw();
	}
}
