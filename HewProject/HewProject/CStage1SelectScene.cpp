#include "CStage1SelectScene.h"
#include "CSceneManager.h"
#include "InputManager.h"
#include "CGridObject.h"
#include "TextureFactory.h"
#include "CStageSelectPlayer.h"
#include "Collision.h"
#include "UI.h"
#include "ShadowUI.h"
#include "WorldSelectPic.h"
#include "DoTween.h"

#define STAGE_SCALE_X (4.27f)
#define STAGE_SCALE_Y (3.2f)

#define TEXT_POS_X (16.0f)
#define TEXT_POS_Y (1.5f)
#define TEXT_POS_XX (-18.0f)
#define TEXT_POS_YY (-1.5f)
#define TEXT_POS_Z (-0.01f)
#define TEXT_SCALE_X (7.5f)
#define TEXT_SCALE_Y (3.0f)

#define WORD_SCALE_X (4.0f)
#define WORD_SCALE_Y (1.0f)

#define TARGET_MOVETIME (0.7f)
#define TARGETBACK_MOVETIME (0.5f)

#define WORLD_POS_Y (2.0f)
#define WORLD_POS_YY (-1.0f)

#define FOUR (4)
#define MOVETIME (0.1f)

CStage1SelectScene::CStage1SelectScene()
{
	pSceneManager->SetPlayBgm(SOUND_LABEL::B_WORLDSELECT);

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
	D3D_LoadTexture(L"asset/UI/T_World.png", &worldTexture);

	D3D_CreateSquare({ 3,4 }, &numBuffer);
	D3D_LoadTexture(L"asset/UI/Number.png", &numTexture);

	for (int i = 0; i < FOUR; i++)
	{
		Num[i] = new UI(numBuffer, numTexture);
		Num[i]->MakeDotween();
	}

	Num[0]->mTransform.pos = { TEXT_POS_XX + 2.3f,WORLD_POS_YY,-0.11f };
	Num[0]->SetColor({ 4,111,243 });
	Num[0]->SetUV(1.0f / 3.0f * 2.0f, 0);
	Num[0]->mTransform.scale = { 1,1,1 };

	Num[1]->mTransform.pos = { TEXT_POS_X + 2.3f,WORLD_POS_YY,-0.11f };
	Num[1]->SetColor({ 246,232,120 });
	Num[1]->SetUV(1.0f / 3.0f * 1.0f, 0);
	Num[1]->mTransform.scale = { 1,1,1 };

	Num[2]->mTransform.pos = { TEXT_POS_X + 2.3f,WORLD_POS_Y,-0.11f };
	Num[2]->SetColor({ 231,166,203 });
	Num[2]->SetUV(0, 1.0f / 4.0f * 1.0f);
	Num[2]->mTransform.scale = { 1,1,1 };

	Num[3]->mTransform.pos = { TEXT_POS_XX + 2.3f,WORLD_POS_Y,-0.11f };
	Num[3]->SetColor({ 15,14,88 });
	Num[3]->SetUV(1.0f / 3.0f * 1.0f, 1.0f / 4.0f);
	Num[3]->mTransform.scale = { 1,1,1 };

	for (int i = 0; i < 4; i++)
	{
		Shadow[i] = new ShadowUI(stageBuffer, shadowTexture);
		Shadow[i]->SetAlpha(0.3f);
	}

	stage[0] = new WorldSelectPic(stageBuffer, stage1Texture);
	stage[1] = new WorldSelectPic(stageBuffer, stage3Texture);
	stage[2] = new WorldSelectPic(stageBuffer, stage2Texture);
	stage[3] = new WorldSelectPic(stageBuffer, stage4Texture);
	stage[4] = new WorldSelectPic(stageBuffer, stage1Texture);

	player = new CStageSelectPlayer(playerBuffer, playerTexture);
	player->mTransform.scale = { 2,2,1 };
	player->mTransform.pos = { 0,0,-0.11f };
	player->SetTexture(player_waitTexture);

	Text[0] = new UI(textBuffer, text_world2Texture);
	Text[0]->MakeDotween();
	Text[0]->mTransform.pos = { TEXT_POS_XX,TEXT_POS_YY,TEXT_POS_Z };
	Text[0]->mTransform.scale = { TEXT_SCALE_X,TEXT_SCALE_Y,1 };
	Text[0]->materialDiffuse = { 1,1,1,1 };

	World[0] = new UI(textBuffer, worldTexture);
	World[0]->MakeDotween();
	World[0]->SetColor({ 4,111,243 });
	World[0]->mTransform.pos = { TEXT_POS_XX,WORLD_POS_YY,-0.1f };
	World[0]->mTransform.scale = { WORD_SCALE_X,WORD_SCALE_Y,1 };

	Text[1] = new UI(textBuffer, text_world1Texture);
	Text[1]->MakeDotween();
	Text[1]->mTransform.pos = { TEXT_POS_X,TEXT_POS_YY,TEXT_POS_Z };
	Text[1]->mTransform.scale = { TEXT_SCALE_X,TEXT_SCALE_Y,1 };
	Text[1]->materialDiffuse = { 1,1,1,1 };

	World[1] = new UI(textBuffer, worldTexture);
	World[1]->MakeDotween();
	World[1]->SetColor({ 246,232,120 });
	World[1]->mTransform.pos = { TEXT_POS_X,WORLD_POS_YY,-0.1f };
	World[1]->mTransform.scale = { WORD_SCALE_X,WORD_SCALE_Y,1 };

	Text[2] = new UI(textBuffer, text_world3Texture);
	Text[2]->MakeDotween();
	Text[2]->mTransform.pos = { TEXT_POS_X,TEXT_POS_Y,TEXT_POS_Z };
	Text[2]->mTransform.scale = { TEXT_SCALE_X,TEXT_SCALE_Y,1 };
	Text[2]->materialDiffuse = { 1,1,1,1 };

	World[2] = new UI(textBuffer, worldTexture);
	World[2]->MakeDotween();
	World[2]->SetColor({ 231,166,203 });
	World[2]->mTransform.pos = { TEXT_POS_X,WORLD_POS_Y,-0.1f };
	World[2]->mTransform.scale = { WORD_SCALE_X,WORD_SCALE_Y,1 };

	Text[3] = new UI(textBuffer, text_world4Texture);
	Text[3]->MakeDotween();
	Text[3]->mTransform.pos = { TEXT_POS_XX,TEXT_POS_Y,TEXT_POS_Z };
	Text[3]->mTransform.scale = { TEXT_SCALE_X,TEXT_SCALE_Y,1 };
	Text[3]->materialDiffuse = { 1,1,1,1 };

	World[3] = new UI(textBuffer, worldTexture);
	World[3]->MakeDotween();
	World[3]->SetColor({ 15,14,88 });
	World[3]->mTransform.pos = { TEXT_POS_XX,WORLD_POS_Y,-0.1f };
	World[3]->mTransform.scale = { WORD_SCALE_X,WORD_SCALE_Y,1 };

	Word[0] = new UI(wordBuffer, word_RightUpTexture);
	Word[0]->MakeDotween();
	Word[0]->mTransform.pos = { TEXT_POS_XX,-2.0f,-0.1f };
	Word[0]->mTransform.scale = { WORD_SCALE_X,WORD_SCALE_Y,1 };

	Word[1] = new UI(wordBuffer, word_RightDownTexture);
	Word[1]->MakeDotween();
	Word[1]->mTransform.pos = { TEXT_POS_XX,1.0f,-0.1f };
	Word[1]->mTransform.scale = { WORD_SCALE_X,WORD_SCALE_Y,1 };

	Word[2] = new UI(wordBuffer, word_LeftUpTexture);
	Word[2]->MakeDotween();
	Word[2]->mTransform.pos = { TEXT_POS_X,-2.0f,-0.1f };
	Word[2]->mTransform.scale = { WORD_SCALE_X,WORD_SCALE_Y,1 };

	Word[3] = new UI(wordBuffer, word_LeftDownTexture);
	Word[3]->MakeDotween();
	Word[3]->mTransform.pos = { TEXT_POS_X,1.0f,-0.1f };
	Word[3]->mTransform.scale = { WORD_SCALE_X,WORD_SCALE_Y,1 };

	Word[4] = new UI(wordBuffer, word_RightUpTexture);
	Word[4]->MakeDotween();
	Word[4]->SetUV(0, 1.0f / 2.0f * 1.0f);
	Word[4]->mTransform.pos = { TEXT_POS_XX + 3.0f,-2.0f,-0.11f };
	Word[4]->mTransform.scale = { WORD_SCALE_X,WORD_SCALE_Y,1 };

	Word[5] = new UI(wordBuffer, word_RightDownTexture);
	Word[5]->MakeDotween();
	Word[5]->SetUV(0, 1.0f / 2.0f * 1.0f);
	Word[5]->mTransform.pos = { TEXT_POS_XX + 2.4f,1.0f,-0.11f };
	Word[5]->mTransform.scale = { WORD_SCALE_X,WORD_SCALE_Y,1 };

	Word[6] = new UI(wordBuffer, word_LeftUpTexture);
	Word[6]->MakeDotween();
	Word[6]->SetUV(0, 1.0f / 2.0f * 1.0f);
	Word[6]->mTransform.pos = { TEXT_POS_X + 3.1f,-2.0f,-0.11f };
	Word[6]->mTransform.scale = { WORD_SCALE_X,WORD_SCALE_Y,1 };

	Word[7] = new UI(wordBuffer, word_LeftDownTexture);
	Word[7]->MakeDotween();
	Word[7]->SetUV(0, 1.0f / 2.0f * 1.0f);
	Word[7]->mTransform.pos = { TEXT_POS_X + 3.1f,1.0f,-0.11f };
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

	for (int i = 0; i < FOUR; i++)
	{
		shadowPos[i] = stage[i]->mTransform.pos;
		Shadow[i]->mTransform.pos = { shadowPos[i].x + 0.05f,shadowPos[i].y - 0.05f,0.4f };
		Shadow[i]->mTransform.scale = { stage[i]->mTransform.scale };
		Shadow[i]->mTransform.rotation = { stage[i]->mTransform.rotation };
	}

	Bg = new UI(bgBuffer, bgTexture);
	Bg->mTransform.pos = { 0,0,0.5f };
	Bg->mTransform.scale = { 16,9,1 };

	isPlayerMoving = false;
	isOnce = false;
	isUpDown = false;
	isBigSmall = false;

	for (int i = 0; i < 5; i++)
	{
		c_isHitStage[i] = false;
		o_isHitStage[i] = false;
	}
}

CStage1SelectScene::~CStage1SelectScene()
{
	CLASS_DELETE(player);

	CLASS_DELETE(Bg);

	for (int i = 0; i < 8; i++)
	{
		CLASS_DELETE(Word[i]);
	}

	for (int i = 0; i < FOUR; i++)
	{
		CLASS_DELETE(Shadow[i]);
	}

	for (int i = 0; i < FOUR; i++)
	{
		CLASS_DELETE(Text[i]);
	}

	for (int i = 0; i < FOUR; i++)
	{
		CLASS_DELETE(Num[i]);
	}

	for (int i = 0; i < 5; i++)
	{
		CLASS_DELETE(stage[i]);
	}

	for (int i = 0; i < FOUR; i++)
	{
		CLASS_DELETE(World[i]);
	}

	SAFE_RELEASE(playerBuffer);
	SAFE_RELEASE(stageBuffer);
	SAFE_RELEASE(bgBuffer);
	SAFE_RELEASE(wordBuffer);
	SAFE_RELEASE(textBuffer);
	SAFE_RELEASE(numBuffer);
	SAFE_RELEASE(text_world1Texture);
	SAFE_RELEASE(text_world2Texture);
	SAFE_RELEASE(text_world3Texture);
	SAFE_RELEASE(text_world4Texture);
	SAFE_RELEASE(word_LeftDownTexture);
	SAFE_RELEASE(word_LeftUpTexture);
	SAFE_RELEASE(word_RightDownTexture);
	SAFE_RELEASE(word_RightUpTexture);
	SAFE_RELEASE(worldTexture);
	SAFE_RELEASE(numTexture);
}

void CStage1SelectScene::Update()
{
	InputManager* input = InputManager::GetInstance();

	Bg->Update();

	for (int i = 0; i < 4; i++)
	{
		stage[i]->Update();
		Shadow[i]->mTransform.scale = { stage[i]->mTransform.scale };
	}

	if (player->isChangeScene == true && !isSceneChange)
	{

		CScene::SCENE_NAME nextScene = CScene::SCENE_NAME::NONE;
		switch (player->nNumSelectScene)
		{
		case 0:
			nextScene = SCENE_NAME::WORLD1_SELECT;
			break;
		case 1:
			nextScene = SCENE_NAME::WORLD3_SELECT;
			break;
		case 2:
			nextScene = SCENE_NAME::WORLD2_SELECT;
			break;
		case 3:
			nextScene = SCENE_NAME::WORLD4_SELECT;
			break;
		case 4:
			nextScene = SCENE_NAME::TITLE;
			break;
		default:
			break;
		}

		if (Fade::GetInstance()->GetState() == Fade::STATE::STAY)
		{
			XA_Play(SOUND_LABEL::S_PUSH_STAGEBTN);
			Fade::GetInstance()->FadeIn(Fade::STATE::LOADING, nullptr, nextScene);
			isSceneChanging = true;
		}
	}
	player->isChangeScene = false;


	Vector3 target = Vector3::zero;
	Vector3 target_word = Vector3::zero;
	Vector3 target_word2 = Vector3::zero;
	Vector3 target_world = Vector3::zero;
	Vector3 target_num = Vector3::zero;
	for (int i = 0; i < 5; i++)
	{
		o_isHitStage[i] = c_isHitStage[i];	// 次フレームのために更新する
		c_isHitStage[i] = false;	// 初期化しておく

		if (CollsionRect(stage[i], player) == true)
		{
			c_isHitStage[i] = true;	// 今フレームで当たっている


			// 一回しか呼ばれない
			if (!o_isHitStage[i])
			{

				// ここにステージのスケールをいじってね
				Vector3 Big = stage[i]->mTransform.scale * 1.2f;
				Big.z = 1.0f;
				Vector3 Small = stage[i]->mTransform.scale * 1.0f;
				stage[i]->dotween->DoEaseOutCubicScale(Big, 2.5f);
				stage[i]->dotween->Append(Small, 2.5f, DoTween::FUNC::EASE_OUTCUBIC_SCALE);
				stage[i]->dotween->SetLoop(-1);


				switch (i)
				{
				case 0:
				{
					//ワールド１
					target = Text[1]->mTransform.pos;
					target.x = 2.0f;
					target_word = Word[2]->mTransform.pos;
					target_word.x = 1.0f;
					target_word2 = Word[6]->mTransform.pos;
					target_word2.x = 4.0f;
					target_world = World[1]->mTransform.pos;
					target_world.x = 1.5f;

					target_num = Num[1]->mTransform.pos;
					target_num.x = 3.8f;

					Text[1]->dotween->DoEaseOutBack(target, TARGET_MOVETIME);
					Text[1]->dotween->Append(Vector3::zero, MOVETIME, DoTweenUI::FUNC::NONE);

					World[1]->dotween->DoEaseOutBack(target_world, TARGET_MOVETIME);
					World[1]->dotween->Append(Vector3::zero, MOVETIME, DoTweenUI::FUNC::NONE);

					Num[1]->dotween->DoEaseOutBack(target_num, TARGET_MOVETIME);
					Num[1]->dotween->Append(Vector3::zero, MOVETIME, DoTweenUI::FUNC::NONE);

					Word[2]->dotween->DoEaseOutBack(target_word, TARGET_MOVETIME);
					Word[2]->dotween->Append(Vector3::zero, MOVETIME, DoTweenUI::FUNC::NONE);

					Word[6]->dotween->DoEaseOutBack(target_word2, TARGET_MOVETIME);
					Word[6]->dotween->Append(Vector3::zero, MOVETIME, DoTweenUI::FUNC::NONE);

					Text[1]->dotween->OnComplete([&]() {isOnce = true; });
				}
				break;
				case 1:
				{
					//ワールド3
					target = Text[2]->mTransform.pos;
					target.x = 2.5f;
					target_word = Word[3]->mTransform.pos;
					target_word.x = 2.0f;
					target_word2 = Word[7]->mTransform.pos;
					target_word2.x = 5.0f;
					target_world = World[2]->mTransform.pos;
					target_world.x = 2.2f;
					target_num = Num[2]->mTransform.pos;
					target_num.x = 4.5f;

					Text[2]->dotween->DoEaseOutBack(target, TARGET_MOVETIME);
					Text[2]->dotween->Append(Vector3::zero, MOVETIME, DoTweenUI::FUNC::NONE);

					World[2]->dotween->DoEaseOutBack(target_world, TARGET_MOVETIME);
					World[2]->dotween->Append(Vector3::zero, MOVETIME, DoTweenUI::FUNC::NONE);

					Num[2]->dotween->DoEaseOutBack(target_num, TARGET_MOVETIME);
					Num[2]->dotween->Append(Vector3::zero, MOVETIME, DoTweenUI::FUNC::NONE);

					Word[3]->dotween->DoEaseOutBack(target_word, TARGET_MOVETIME);
					Word[3]->dotween->Append(Vector3::zero, MOVETIME, DoTweenUI::FUNC::NONE);

					Word[7]->dotween->DoEaseOutBack(target_word2, TARGET_MOVETIME);
					Word[7]->dotween->Append(Vector3::zero, MOVETIME, DoTweenUI::FUNC::NONE);

					Text[2]->dotween->OnComplete([&]() {isOnce = true; });
				}
				break;
				case 2:
				{
					//ワールド２
					target = Text[0]->mTransform.pos;
					target.x = -2.0f;
					target_word = Word[0]->mTransform.pos;
					target_word.x = -2.3f;

					target_word2 = Word[4]->mTransform.pos;
					target_word2.x = 0.5f;

					target_world = World[0]->mTransform.pos;
					target_world.x = -2.2f;

					target_num = Num[0]->mTransform.pos;
					target_num.x = 0.1f;

					Text[0]->dotween->DoEaseOutBack(target, TARGET_MOVETIME);
					Text[0]->dotween->Append(Vector3::zero, MOVETIME, DoTweenUI::FUNC::NONE);

					World[0]->dotween->DoEaseOutBack(target_world, TARGET_MOVETIME);
					World[0]->dotween->Append(Vector3::zero, MOVETIME, DoTweenUI::FUNC::NONE);

					Num[0]->dotween->DoEaseOutBack(target_num, TARGET_MOVETIME);
					Num[0]->dotween->Append(Vector3::zero, MOVETIME, DoTweenUI::FUNC::NONE);

					Word[0]->dotween->DoEaseOutBack(target_word, TARGET_MOVETIME);
					Word[0]->dotween->Append(Vector3::zero, MOVETIME, DoTweenUI::FUNC::NONE);

					Word[4]->dotween->DoEaseOutBack(target_word2, TARGET_MOVETIME);
					Word[4]->dotween->Append(Vector3::zero, MOVETIME, DoTweenUI::FUNC::NONE);

					Text[0]->dotween->OnComplete([&]() {isOnce = true; });
				}
				break;
				case 3:
				{
					//ワールド４
					target = Text[3]->mTransform.pos;
					target.x = -2.0f;
					target_word = Word[1]->mTransform.pos;
					target_word.x = -2.7f;
					target_word2 = Word[5]->mTransform.pos;
					target_word2.x = -0.1f;
					target_world = World[3]->mTransform.pos;
					target_world.x = -2.2f;
					target_num = Num[3]->mTransform.pos;
					target_num.x = 0.1f;

					Text[3]->dotween->DoEaseOutBack(target, TARGET_MOVETIME);
					Text[3]->dotween->Append(Vector3::zero, MOVETIME, DoTweenUI::FUNC::NONE);

					World[3]->dotween->DoEaseOutBack(target_world, TARGET_MOVETIME);
					World[3]->dotween->Append(Vector3::zero, MOVETIME, DoTweenUI::FUNC::NONE);

					Num[3]->dotween->DoEaseOutBack(target_num, TARGET_MOVETIME);
					Num[3]->dotween->Append(Vector3::zero, MOVETIME, DoTweenUI::FUNC::NONE);

					Word[1]->dotween->DoEaseOutBack(target_word, TARGET_MOVETIME);
					Word[1]->dotween->Append(Vector3::zero, MOVETIME, DoTweenUI::FUNC::NONE);

					Word[5]->dotween->DoEaseOutBack(target_word2, TARGET_MOVETIME);
					Word[5]->dotween->Append(Vector3::zero, MOVETIME, DoTweenUI::FUNC::NONE);

					Text[3]->dotween->OnComplete([&]() {isOnce = true; });
				}
				break;
				case 4:
					break;
				default:
					break;
				}
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

		else if (!c_isHitStage[i] && o_isHitStage[i])
		{
			stage[i]->dotween->Stop();
			stage[i]->mTransform.scale = { STAGE_SCALE_X, STAGE_SCALE_Y, 1.0f };

			switch (i)
			{
			case 0:
				target = Text[1]->mTransform.pos;
				target.x = TEXT_POS_X;
				target_world = World[1]->mTransform.pos;
				target_world.x = TEXT_POS_X;
				target_num = Num[1]->mTransform.pos;
				target_num.x = TEXT_POS_X + 2.3f;
				target_word = Word[2]->mTransform.pos;
				target_word.x = TEXT_POS_X;
				target_word2 = Word[6]->mTransform.pos;
				target_word2.x = TEXT_POS_X + 3.1f;

				Text[1]->dotween->Stop();
				World[1]->dotween->Stop();
				Num[1]->dotween->Stop();
				Word[2]->dotween->Stop();
				Word[6]->dotween->Stop();


				Text[1]->dotween->DoEaseOutBack(target, TARGETBACK_MOVETIME);
				World[1]->dotween->DoEaseOutBack(target_world, TARGETBACK_MOVETIME);
				Num[1]->dotween->DoEaseOutBack(target_num, TARGETBACK_MOVETIME);
				Word[2]->dotween->DoEaseOutBack(target_word, TARGETBACK_MOVETIME);
				Word[6]->dotween->DoEaseOutBack(target_word2, TARGETBACK_MOVETIME);
				isOnce = false;

				break;
			case 1:
				target = Text[2]->mTransform.pos;
				target.x = TEXT_POS_X;
				target_world = World[2]->mTransform.pos;
				target_world.x = TEXT_POS_X;
				target_num = Num[2]->mTransform.pos;
				target_num.x = TEXT_POS_X + 2.3f;
				target_word = Word[3]->mTransform.pos;
				target_word.x = TEXT_POS_X;
				target_word2 = Word[7]->mTransform.pos;
				target_word2.x = TEXT_POS_X + 3.1f;


				Text[2]->dotween->Stop();
				World[2]->dotween->Stop();
				Num[2]->dotween->Stop();
				Word[3]->dotween->Stop();
				Word[7]->dotween->Stop();

				Text[2]->dotween->DoEaseOutBack(target, TARGETBACK_MOVETIME);
				World[2]->dotween->DoEaseOutBack(target_world, TARGETBACK_MOVETIME);
				Num[2]->dotween->DoEaseOutBack(target_num, TARGETBACK_MOVETIME);
				Word[3]->dotween->DoEaseOutBack(target_word, TARGETBACK_MOVETIME);
				Word[7]->dotween->DoEaseOutBack(target_word2, TARGETBACK_MOVETIME);
				isOnce = false;
				break;
			case 2:
				target = Text[0]->mTransform.pos;
				target.x = TEXT_POS_XX;
				target_world = World[0]->mTransform.pos;
				target_world.x = TEXT_POS_XX;
				target_num = Num[0]->mTransform.pos;
				target_num.x = TEXT_POS_XX + 2.3f;
				target_word = Word[0]->mTransform.pos;
				target_word.x = TEXT_POS_XX;
				target_word2 = Word[4]->mTransform.pos;
				target_word2.x = TEXT_POS_XX + 3.0f;


				Text[0]->dotween->Stop();
				World[0]->dotween->Stop();
				Num[0]->dotween->Stop();
				Word[0]->dotween->Stop();
				Word[4]->dotween->Stop();

				Text[0]->dotween->DoEaseOutBack(target, TARGETBACK_MOVETIME);
				World[0]->dotween->DoEaseOutBack(target_world, TARGETBACK_MOVETIME);
				Num[0]->dotween->DoEaseOutBack(target_num, TARGETBACK_MOVETIME);
				Word[0]->dotween->DoEaseOutBack(target_word, TARGETBACK_MOVETIME);
				Word[4]->dotween->DoEaseOutBack(target_word2, TARGETBACK_MOVETIME);
				isOnce = false;
				break;

			case 3:
				target = Text[3]->mTransform.pos;
				target.x = TEXT_POS_XX;
				target_world = World[3]->mTransform.pos;
				target_world.x = TEXT_POS_XX;
				target_num = Num[3]->mTransform.pos;
				target_num.x = TEXT_POS_XX + 2.3f;
				target_word = Word[1]->mTransform.pos;
				target_word.x = TEXT_POS_XX;
				target_word2 = Word[5]->mTransform.pos;
				target_word2.x = TEXT_POS_XX + 2.4f;

				Text[3]->dotween->Stop();
				World[3]->dotween->Stop();
				Num[3]->dotween->Stop();
				Word[1]->dotween->Stop();
				Word[5]->dotween->Stop();

				Text[3]->dotween->DoEaseOutBack(target, TARGETBACK_MOVETIME);
				World[3]->dotween->DoEaseOutBack(target_world, TARGETBACK_MOVETIME);
				Num[3]->dotween->DoEaseOutBack(target_num, TARGETBACK_MOVETIME);
				Word[1]->dotween->DoEaseOutBack(target_word, TARGETBACK_MOVETIME);
				Word[5]->dotween->DoEaseOutBack(target_word2, TARGETBACK_MOVETIME);
				isOnce = false;
				break;
				// 戻るボタン
			case 4:
				break;
			}
		}

		
	}

	

	for (int i = 0; i < FOUR; i++)
	{
		Text[i]->Update();
	}

	for (int i = 0; i < FOUR; i++)
	{
		Num[i]->Update();
	}

	for (int i = 0; i < FOUR; i++)
	{
		World[i]->Update();
	}

	for (int i = 0; i < 8; i++)
	{
		Word[i]->Update();
	}

	for (int i = 0; i < FOUR; i++)
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

	for (int i = 0; i < FOUR; i++)
	{
		Shadow[i]->Draw();
	}

	for (int i = 0; i < 5; i++)
	{
		stage[i]->Draw();
	}

	player->Draw();

	for (int i = 0; i < FOUR; i++)
	{
		Text[i]->Draw();
	}

	for (int i = 0; i < FOUR; i++)
	{
		World[i]->Draw();
	}

	for (int i = 0; i < FOUR; i++)
	{
		Num[i]->Draw();
	}

	for (int i = 0; i < 8; i++)
	{
		Word[i]->Draw();
	}
}
