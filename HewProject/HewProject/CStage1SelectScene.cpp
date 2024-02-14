#include "CStage1SelectScene.h"
#include "CSceneManager.h"
#include "InputManager.h"
#include "CGridObject.h"
#include "TextureFactory.h"
#include "CStageSelectPlayer.h"
#include "Collision.h"
#include "UI.h"
#include "ShadowUI.h"

#define STAGE_SCALE_X (3.95f)
#define STAGE_SCALE_Y (3.0f)

#define TEXT_POS_X (18.0f)
#define TEXT_POS_Y (2.5f)
#define TEXT_POS_XX (-18.0f)
#define TEXT_POS_YY (-2.5f)
#define TEXT_POS_Z (-0.01f)
#define TEXT_SCALE_X (9.0f)
#define TEXT_SCALE_Y (3.0f)

#define WORD_SCALE_X (4.0f)
#define WORD_SCALE_Y (1.0f)

CStage1SelectScene::CStage1SelectScene()
{
	D3D_CreateSquare({ 3,4 }, &playerBuffer);
	playerTexture = TextureFactory::GetInstance()->Fetch(L"asset/Player/N_Walk.png");
	player_waitTexture = TextureFactory::GetInstance()->Fetch(L"asset/Player/N_Wait.png");

	D3D_CreateSquare({ 1,1 }, &stageBuffer);
	stage1Texture = TextureFactory::GetInstance()->Fetch(L"asset/Background/World1_pic.png");
	stage2Texture = TextureFactory::GetInstance()->Fetch(L"asset/Background/World2_pic.png");
	stage3Texture = TextureFactory::GetInstance()->Fetch(L"asset/Background/World3_pic.png");
	stage4Texture = TextureFactory::GetInstance()->Fetch(L"asset/Background/World4_pic.png");
	shadowTexture = TextureFactory::GetInstance()->Fetch(L"asset/UI/FadeBlack.png");

	D3D_CreateSquare({ 1,1 }, &bgBuffer);
	bgTexture = TextureFactory::GetInstance()->Fetch(L"asset/Background/WorldSelectBack.png");

	D3D_CreateSquare({ 1,2 }, &wordBuffer);
	D3D_LoadTexture(L"asset/Text/World1Name.png", &word_LeftUpTexture);
	D3D_LoadTexture(L"asset/Text/World2Name.png", &word_RightUpTexture);
	D3D_LoadTexture(L"asset/Text/World3Name.png", &word_LeftDownTexture);
	D3D_LoadTexture(L"asset/Text/World4Name.png", &word_RightDownTexture);
	
	D3D_CreateSquare({ 1,1 }, &textBuffer);
	D3D_LoadTexture(L"asset/Background/Stage1SelectBack.png", &text_world1Texture);
	D3D_LoadTexture(L"asset/Background/Stage2SelectBack.png", &text_world2Texture);
	D3D_LoadTexture(L"asset/Background/Stage3SelectBack.png", &text_world3Texture);
	D3D_LoadTexture(L"asset/Background/Stage4SelectBack.png", &text_world4Texture);
	
	for (int i = 0; i < 4; i++)
	{
		Shadow[i] = new ShadowUI(stageBuffer, shadowTexture);
		Shadow[i]->SetAlpha(0.3f);
	}

	stage[0] = new CGridObject(stageBuffer, stage1Texture);
	stage[1] = new CGridObject(stageBuffer, stage3Texture);
	stage[2] = new CGridObject(stageBuffer, stage2Texture);
	stage[3] = new CGridObject(stageBuffer, stage4Texture);
	stage[4] = new CGridObject(stageBuffer, stage1Texture);

	player = new CStageSelectPlayer(playerBuffer, playerTexture);
	player->mTransform.scale = { 2,2,1 };
	player->mTransform.pos = { 0,0,-0.11f };
	player->SetTexture(player_waitTexture);

	Text[0] = new UI(textBuffer, text_world2Texture);
	Text[0]->MakeDotween();
	Text[0]->mTransform.pos = { TEXT_POS_XX,TEXT_POS_YY,TEXT_POS_Z};
	Text[0]->mTransform.scale = {TEXT_SCALE_X,TEXT_SCALE_Y,1};
	Text[0]->materialDiffuse = {1,1,1,1};

	Text[1] = new UI(textBuffer, text_world1Texture);
	Text[1]->MakeDotween();
	Text[1]->mTransform.pos = { TEXT_POS_X,TEXT_POS_YY,TEXT_POS_Z };
	Text[1]->mTransform.scale = { TEXT_SCALE_X,TEXT_SCALE_Y,1 };
	Text[1]->materialDiffuse = { 1,1,1,1 };

	Text[2] = new UI(textBuffer, text_world3Texture);
	Text[2]->MakeDotween();
	Text[2]->mTransform.pos = { TEXT_POS_X,TEXT_POS_Y,TEXT_POS_Z };
	Text[2]->mTransform.scale = { TEXT_SCALE_X,TEXT_SCALE_Y,1 };
	Text[2]->materialDiffuse = { 1,1,1,1 };

	Text[3] = new UI(textBuffer, text_world4Texture);
	Text[3]->MakeDotween();
	Text[3]->mTransform.pos = { TEXT_POS_XX,TEXT_POS_Y,TEXT_POS_Z };
	Text[3]->mTransform.scale = { TEXT_SCALE_X,TEXT_SCALE_Y,1 };
	Text[3]->materialDiffuse = { 1,1,1,1 };

	Word[0] = new UI(wordBuffer, word_RightUpTexture);
	Word[0]->MakeDotween();
	Word[0]->mTransform.pos = {-20.0f,-3.0f,-0.1f};
	Word[0]->mTransform.scale = {WORD_SCALE_X,WORD_SCALE_Y,1};

	Word[1] = new UI(wordBuffer, word_RightDownTexture);
	Word[1]->MakeDotween();
	Word[1]->mTransform.pos = { -20.0f,2.0f,-0.1f };
	Word[1]->mTransform.scale = { WORD_SCALE_X,WORD_SCALE_Y,1 };

	Word[2] = new UI(wordBuffer, word_LeftUpTexture);
	Word[2]->MakeDotween();
	Word[2]->mTransform.pos = { 18.0f,-3.0f,-0.1f };
	Word[2]->mTransform.scale = { WORD_SCALE_X,WORD_SCALE_Y,1 };

	Word[3] = new UI(wordBuffer, word_LeftDownTexture);
	Word[3]->MakeDotween();
	Word[3]->mTransform.pos = { 18.0f,2.0f,-0.1f };
	Word[3]->mTransform.scale = { WORD_SCALE_X,WORD_SCALE_Y,1 };

	Word[4] = new UI(wordBuffer, word_RightUpTexture);
	Word[4]->MakeDotween();
	Word[4]->SetUV(0, 1.0f / 2.0f * 1.0f);
	Word[4]->mTransform.pos = { -16.0f,-3.0f,-0.11f };
	Word[4]->mTransform.scale = { WORD_SCALE_X,WORD_SCALE_Y,1 };

	Word[5] = new UI(wordBuffer, word_RightDownTexture);
	Word[5]->MakeDotween();
	Word[5]->SetUV(0, 1.0f / 2.0f * 1.0f);
	Word[5]->mTransform.pos = { -16.0f,2.0f,-0.11f };
	Word[5]->mTransform.scale = { WORD_SCALE_X,WORD_SCALE_Y,1 };

	Word[6] = new UI(wordBuffer, word_LeftUpTexture);
	Word[6]->MakeDotween();
	Word[6]->SetUV(0, 1.0f / 2.0f * 1.0f);
	Word[6]->mTransform.pos = { 20.0f,-3.0f,-0.11f };
	Word[6]->mTransform.scale = { WORD_SCALE_X,WORD_SCALE_Y,1 };

	Word[7] = new UI(wordBuffer, word_LeftDownTexture);
	Word[7]->MakeDotween();
	Word[7]->SetUV(0, 1.0f / 2.0f * 1.0f);
	Word[7]->mTransform.pos = { 20.0f,2.0f,-0.11f };
	Word[7]->mTransform.scale = { WORD_SCALE_X,WORD_SCALE_Y,1 };

	stage[0]->mTransform.pos = { -4.0f,2.0f,-0.1f };
	stage[0]->mTransform.scale = { STAGE_SCALE_X,STAGE_SCALE_Y,1 };
	stage[0]->mTransform.rotation = { 0,0,-5.0f };

	stage[1]->mTransform.pos = { -2.8f,-2.0f,-0.1f };
	stage[1]->mTransform.scale = { STAGE_SCALE_X,STAGE_SCALE_Y,1 };
	stage[1]->mTransform.rotation = { 0,0,2.0f };

	stage[2]->mTransform.pos = { 4.0f,1.6f,-0.1f };
	stage[2]->mTransform.scale = { STAGE_SCALE_X,STAGE_SCALE_Y,1 };
	stage[2]->mTransform.rotation = { 0,0,5.0f };

	stage[3]->mTransform.pos = { 3.0f,-2.7f,-0.1f };
	stage[3]->mTransform.scale = { STAGE_SCALE_X,STAGE_SCALE_Y,1 };
	stage[3]->mTransform.rotation = { 0,0,-7.0f };

	stage[4]->mTransform.pos = { 0,-2,-0.1f };
	stage[4]->mTransform.scale = { STAGE_SCALE_X,STAGE_SCALE_Y,1 };

	Vector3 shadowPos[4];

	for (int i = 0; i < 4; i++)
	{
		shadowPos[i] = stage[i]->mTransform.pos;
		Shadow[i]->mTransform.pos = { shadowPos[i].x + 0.05f,shadowPos[i].y - 0.05f,0.4f};
		Shadow[i]->mTransform.scale = { stage[i]->mTransform.scale };
		Shadow[i]->mTransform.rotation = { stage[i]->mTransform.rotation };
	}
	
	Bg = new UI(bgBuffer, bgTexture);
	Bg->mTransform.pos = { 0,0,0.5f };
	Bg->mTransform.scale = { 16,9,1 };

	isPlayerMoving = false;
	isOnce = false;
	isUpDown = false;
}

CStage1SelectScene::~CStage1SelectScene()
{
	CLASS_DELETE(player);

	CLASS_DELETE(Bg);

	for (int i = 0; i < 8; i++)
	{
		CLASS_DELETE(Word[i]);
	}

	for (int i = 0; i < 4; i++)
	{
		CLASS_DELETE(Shadow[i]);
	}

	for (int i = 0; i < 4; i++)
	{
		CLASS_DELETE(Text[i]);
	}

	for (int i = 0; i < 5; i++)
	{
		CLASS_DELETE(stage[i]);
	}

	SAFE_RELEASE(playerBuffer);
	SAFE_RELEASE(stageBuffer);
	SAFE_RELEASE(bgBuffer);
	SAFE_RELEASE(wordBuffer);
	SAFE_RELEASE(textBuffer);
	SAFE_RELEASE(text_world1Texture);
	SAFE_RELEASE(text_world2Texture);
	SAFE_RELEASE(text_world3Texture);
	SAFE_RELEASE(text_world4Texture);
	SAFE_RELEASE(word_LeftDownTexture);
	SAFE_RELEASE(word_LeftUpTexture);
	SAFE_RELEASE(word_RightDownTexture);
	SAFE_RELEASE(word_RightUpTexture);
}

void CStage1SelectScene::Update()
{
	InputManager* input = InputManager::GetInstance();

	Bg->Update();

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

		if (CollsionRect(stage[i], player) == true)
		{
			switch (i)
			{
			case 0:
			{
				//ワールド１
				Vector3 target = Text[1]->mTransform.pos;
				target.x = 3.0f;
				Vector3 target_word = Word[2]->mTransform.pos;
				target_word.x = 2.0f;
				Vector3 target_word2 = Word[6]->mTransform.pos;
				target_word2.x = 5.0f;

				Text[1]->dotween->DoEaseOutBack(target, 1.0f);
				Text[1]->dotween->Append(Vector3::zero, 1.0f, DoTweenUI::FUNC::NONE);
				
				Word[2]->dotween->DoEaseOutBack(target_word, 1.0f);
				Word[2]->dotween->Append(Vector3::zero, 1.0f, DoTweenUI::FUNC::NONE);

				Word[6]->dotween->DoEaseOutBack(target_word2, 1.0f);
				Word[6]->dotween->Append(Vector3::zero, 1.0f, DoTweenUI::FUNC::NONE);

				Text[1]->dotween->OnComplete([&]() {isOnce = true; });
			}
				break;
			case 1:
			{
				//ワールド3
				Vector3 target = Text[2]->mTransform.pos;
				target.x = 3.0f;
				Vector3 target_word = Word[3]->mTransform.pos;
				target_word.x = 2.0f;
				Vector3 target_word2 = Word[7]->mTransform.pos;
				target_word2.x = 5.5f;

				Text[2]->dotween->DoEaseOutBack(target, 1.0f);
				Text[2]->dotween->Append(Vector3::zero, 1.0f, DoTweenUI::FUNC::NONE);
				
				Word[3]->dotween->DoEaseOutBack(target_word, 1.0f);
				Word[3]->dotween->Append(Vector3::zero, 1.0f, DoTweenUI::FUNC::NONE);
				
				Word[7]->dotween->DoEaseOutBack(target_word2, 1.0f);
				Word[7]->dotween->Append(Vector3::zero, 1.0f, DoTweenUI::FUNC::NONE);

				Text[2]->dotween->OnComplete([&]() {isOnce = true; });
			}
				break;
			case 2:
			{
				//ワールド２
				Vector3 target = Text[0]->mTransform.pos;
				target.x = -3.0f;
				Vector3 target_word = Word[0]->mTransform.pos;
				target_word.x = -3.3f;

				Vector3 target_word2 = Word[4]->mTransform.pos;
				target_word2.x = -0.5f;

				Text[0]->dotween->DoEaseOutBack(target, 1.0f);
				Text[0]->dotween->Append(Vector3::zero, 1.0f, DoTweenUI::FUNC::NONE);
				
				Word[0]->dotween->DoEaseOutBack(target_word, 1.0f);
				Word[0]->dotween->Append(Vector3::zero, 1.0f, DoTweenUI::FUNC::NONE);

				Word[4]->dotween->DoEaseOutBack(target_word2, 1.0f);
				Word[4]->dotween->Append(Vector3::zero, 1.0f, DoTweenUI::FUNC::NONE);

				Text[0]->dotween->OnComplete([&]() {isOnce = true; });
			}
				break;
			case 3:
			{
				//ワールド４
				Vector3 target = Text[3]->mTransform.pos;
				target.x = -3.0f;
				Vector3 target_word = Word[1]->mTransform.pos;
				target_word.x = -3.8f;
				Vector3 target_word2 = Word[5]->mTransform.pos;
				target_word2.x = -1.0f;

				Text[3]->dotween->DoEaseOutBack(target, 1.0f);
				Text[3]->dotween->Append(Vector3::zero, 1.0f, DoTweenUI::FUNC::NONE);
				
				Word[1]->dotween->DoEaseOutBack(target_word, 1.0f);
				Word[1]->dotween->Append(Vector3::zero, 1.0f, DoTweenUI::FUNC::NONE);

				Word[5]->dotween->DoEaseOutBack(target_word2, 1.0f);
				Word[5]->dotween->Append(Vector3::zero, 1.0f, DoTweenUI::FUNC::NONE);

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
		//ワールド１
		if (CollsionRect(stage[0], player) == false)
		{
			Vector3 target = Text[1]->mTransform.pos;
			target.x = 18.0f;
			Vector3 target_word = Word[2]->mTransform.pos;
			target_word.x = 18.0f;
			Vector3 target_word2 = Word[6]->mTransform.pos;
			target_word2.x = 20.0f;

			Text[1]->dotween->DoEaseOutBack(target, 1.0f);
			Word[2]->dotween->DoEaseOutBack(target_word, 1.0f);
			Word[6]->dotween->DoEaseOutBack(target_word2, 1.0f);
			isOnce = false;
		}
		
		//ワールド3
		if (CollsionRect(stage[1], player) == false)
		{
			Vector3 target = Text[2]->mTransform.pos;
			target.x = 18.0f;
			Vector3 target_word = Word[3]->mTransform.pos;
			target_word.x = 18.0f;
			Vector3 target_word2 = Word[7]->mTransform.pos;
			target_word2.x = 20.0f;

			Text[2]->dotween->DoEaseOutBack(target, 1.0f);
			Word[3]->dotween->DoEaseOutBack(target_word, 1.0f);
			Word[7]->dotween->DoEaseOutBack(target_word2, 1.0f);
			isOnce = false;
		}

		//ワールド２
		if (CollsionRect(stage[2], player) == false)
		{
			Vector3 target = Text[0]->mTransform.pos;
			target.x = -18.0f;
			Vector3 target_word = Word[0]->mTransform.pos;
			target_word.x = -18.0f;
			Vector3 target_word2 = Word[4]->mTransform.pos;
			target_word2.x = -16.0f;
			Text[0]->dotween->DoEaseOutBack(target, 1.0f);
			Word[0]->dotween->DoEaseOutBack(target_word, 1.0f);
			Word[4]->dotween->DoEaseOutBack(target_word2, 1.0f);
			isOnce = false;
		}

		//ワールド４
		if (CollsionRect(stage[3], player) == false)
		{
			Vector3 target = Text[3]->mTransform.pos;
			target.x = -18.0f;
			Vector3 target_word = Word[1]->mTransform.pos;
			target_word.x = -18.0f;
			Vector3 target_word2 = Word[5]->mTransform.pos;
			target_word2.x = -16.0f;
			Text[3]->dotween->DoEaseOutBack(target, 1.0f);
			Word[1]->dotween->DoEaseOutBack(target_word, 1.0f);
			Word[5]->dotween->DoEaseOutBack(target_word2, 1.0f);
			isOnce = false;
		}
	}

	for (int i = 0; i < 4; i++)
	{
		Text[i]->Update();
	}
	
	for (int i = 0; i < 8; i++)
	{
		Word[i]->Update();
	}

	for (int i = 0; i < 4; i++)
	{
		Shadow[i]->Update();
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
	Bg->Draw();
	
	for (int i = 0; i < 4; i++)
	{
		Shadow[i]->Draw();
	}

	for (int i = 0; i < 4; i++)
	{
		stage[i]->Draw();
	}

	player->Draw();

	for (int i = 0; i < 4; i++)
	{
		Text[i]->Draw();
	}

	for (int i = 0; i < 8; i++)
	{
		Word[i]->Draw();
	}
}
