#include "CGameClear.h"
#include "TextureFactory.h"
#include "UI.h"
#include "InputManager.h"
#include "ButtonUI.h"
#include "ButtonSelect.h"
#include "CGameClearPlayer.h"
#include "CoinUI.h"

#define BUTTON_POS_Y (-2.4f)
#define BUTTON_SCALE (4.0f)

#define WHITEBG_POS_Z (-0.455f)

CGameClear::CGameClear(CScene::SCENE_NAME _nextScene,CoinUI* _coin)
{
	nextScene = _nextScene;

	D3D_CreateSquare({ 1,1 }, &bgBuffer);
	bgTexture = TextureFactory::GetInstance()->Fetch(L"asset/UI/White.png");

	Bg = new UI(bgBuffer, bgTexture);
	Bg->SetColor({ 255,255,255 });
	Bg->SetAlpha(0.0f);
	Bg->mTransform.pos = { 0,0,WHITEBG_POS_Z };
	Bg->mTransform.scale = { 16.0f,9.0f,1.0f };

	D3D_CreateSquare({ 6,1 }, &textBuffer);
	textTexture = TextureFactory::GetInstance()->Fetch(L"asset/UI/CLEAR.png");

	for (int i = 0; i < 6; i++)
	{
		Text[i] = new UI(textBuffer, textTexture);
		Text[i]->MakeDotween();
	}

	Text[0]->mTransform.pos = { -4.7f,3.0f,WHITEBG_POS_Z - 0.012f };
	Text[0]->mTransform.scale = Vector3::zero;

	Text[1]->mTransform.pos = { -2.7f,3.0f,WHITEBG_POS_Z - 0.013f };
	Text[1]->mTransform.scale = Vector3::zero;
	Text[1]->SetUV(1.0f / 6.0f * 1.0f, 0);

	Text[2]->mTransform.pos = { -0.7f,3.0f,WHITEBG_POS_Z - 0.014f };
	Text[2]->mTransform.scale = Vector3::zero;
	Text[2]->SetUV(1.0f / 6.0f * 2.0f, 0);

	Text[3]->mTransform.pos = { 1.3f,3.0f,WHITEBG_POS_Z - 0.015f };
	Text[3]->mTransform.scale = Vector3::zero;
	Text[3]->SetUV(1.0f / 6.0f * 3.0f, 0);

	Text[4]->mTransform.pos = { 3.3f,3.0f,WHITEBG_POS_Z - 0.016f };
	Text[4]->mTransform.scale = Vector3::zero;
	Text[4]->SetUV(1.0f / 6.0f * 4.0f, 0);

	Text[5]->mTransform.pos = { 5.3f,3.0f,WHITEBG_POS_Z - 0.017f };
	Text[5]->mTransform.scale = Vector3::zero;
	Text[5]->SetUV(1.0f / 6.0f * 5.0f, 0);

	D3D_CreateSquare({ 1,2 }, &textBoxBuffer);
	textBoxTexture = TextureFactory::GetInstance()->Fetch(L"asset/UI/Button.png");

	D3D_CreateSquare({ 1,1 }, &textBuffer);
	text_nextStageTexture = TextureFactory::GetInstance()->Fetch(L"asset/Text/T_NextStage.png");
	text_stageSelectTexture = TextureFactory::GetInstance()->Fetch(L"asset/Text/T_StageSelectBack.png");

	Message[0] = new ButtonUI(textBoxBuffer, textBoxTexture, textBuffer, text_nextStageTexture);
	Message[0]->SetPosition({ -3.0f, BUTTON_POS_Y,WHITEBG_POS_Z - 0.012f });
	Message[0]->SetScale({ BUTTON_SCALE,BUTTON_SCALE,1.0f });
	Message[0]->SetHighlight(true);
	Message[0]->SetFunc([&]() {
		CScene::SetScene(SCENE_NAME::SELECT);
		});

	Message[1] = new ButtonUI(textBoxBuffer, textBoxTexture, textBuffer, text_stageSelectTexture);
	Message[1]->SetPosition({ 3.0f, BUTTON_POS_Y,WHITEBG_POS_Z - 0.012f });
	Message[1]->SetScale({ BUTTON_SCALE,BUTTON_SCALE,1.0f });
	Message[1]->SetFunc([&]() {
		CScene::SetScene(SCENE_NAME::GAMECLEAR);
		});

	D3D_CreateSquare({ 1,1 }, &frameBuffer);
	frameTexture = TextureFactory::GetInstance()->Fetch(L"asset/UI/CLEAR_Frame.png");

	Frame[0] = new UI(frameBuffer, frameTexture);
	Frame[0]->MakeDotween();
	Frame[0]->mTransform.pos = { 16.0f,4.0f,WHITEBG_POS_Z - 0.001f };
	Frame[0]->mTransform.scale = { 16.0f,1,1 };

	Frame[1] = new UI(frameBuffer, frameTexture);
	Frame[1]->MakeDotween();
	Frame[1]->mTransform.pos = { -16.0f,-4.0f,WHITEBG_POS_Z - 0.001f };
	Frame[1]->mTransform.scale = { 16.0f,1,1 };

	D3D_CreateSquare({ 1,1 }, &namiBuffer);
	namiTexture = TextureFactory::GetInstance()->Fetch(L"asset/UI/CLEAR_Namisen.png");

	Nami[0] = new UI(namiBuffer, namiTexture);
	Nami[0]->MakeDotween();
	Nami[0]->mTransform.pos = { 16.0f,3.5f,WHITEBG_POS_Z - 0.011f };
	Nami[0]->mTransform.scale = { 16.0f,1,1 };

	Nami[1] = new UI(namiBuffer, namiTexture);
	Nami[1]->MakeDotween();
	Nami[1]->mTransform.pos = { -16.0f,-3.5f,WHITEBG_POS_Z - 0.011f };
	Nami[1]->mTransform.scale = { 16.0f,1,1 };

	// ボタン選択クラス作成
	selectControl = new ButtonSelect();
	selectControl->Regist(Message[0]);
	selectControl->Regist(Message[1]);

	D3D_CreateSquare({ 3,4 }, &playerBuffer);
	D3D_LoadTexture(L"asset/Player/12komaEat_L.png", &player_EatTexture);
	D3D_LoadTexture(L"asset/Player/N_Walk.png", &player_WalkTexture);

	player = new CGameClearPlayer(playerBuffer, player_WalkTexture);
	player->mTransform.pos = { 9.0f,0,WHITEBG_POS_Z - 0.27f };
	player->mTransform.scale = { 4.0f,4.0f,1.0f };

	Coin = _coin;

	if (Coin != nullptr)
	{
		Coin = new CoinUI(_coin->GetStageCoin());
		Coin->SetPosition({ -9.0f,-0.2f,WHITEBG_POS_Z - 0.512f });
		Coin->SetScale({ 1.5f,1.5f });
		Coin->SetActive(true);
	}
	

	isNoMoving = false;
	isOnce = false;
	isFrame = false;
	isStopAnim = false;
	isCoin = false;
}

CGameClear::~CGameClear()
{
	for (int i = 0; i < 2; i++)
	{
		CLASS_DELETE(Frame[i]);
	}
	
	for (int i = 0; i < 2; i++)
	{
		CLASS_DELETE(Nami[i]);
	}

	for (int i = 0; i < 6; i++)
	{
		CLASS_DELETE(Text[i]);
	}

	for (int i = 0; i < 2; i++)
	{
		CLASS_DELETE(Message[i]);
	}

	CLASS_DELETE(Bg);

	CLASS_DELETE(selectControl);

	CLASS_DELETE(player);

	CLASS_DELETE(Coin);

	SAFE_RELEASE(bgBuffer);
	SAFE_RELEASE(textBuffer);
	SAFE_RELEASE(textBoxBuffer);
	SAFE_RELEASE(frameBuffer);
	SAFE_RELEASE(namiBuffer);
	SAFE_RELEASE(playerBuffer);
	SAFE_RELEASE(player_EatTexture);
	SAFE_RELEASE(player_WalkTexture);
}

void CGameClear::Update()
{
	InputManager* input = InputManager::GetInstance();

	if (isNoMoving == false)
	{
		Bg->materialDiffuse.w += 0.01f;

		if (Bg->materialDiffuse.w > 0.5f)
		{
			Bg->SetAlpha(0.5f);
		}

		if (isFrame == false)
		{

			Vector3 t = Frame[0]->mTransform.pos;
			t.x = 0.0f;
			Frame[0]->dotween->DoEaseOutCubic(t ,1.0f);

			t = Nami[0]->mTransform.pos;
			t.x = 0.0f;
			Nami[0]->dotween->DoEaseOutCubic(t, 1.0f);

			Frame[1]->dotween->DelayedCall(0.5f, [&]()
				{
					Vector3 p = Frame[1]->mTransform.pos;
					p.x = 0.0f;
					Frame[1]->dotween->DoEaseOutCubic(p, 1.0f);
					p = Nami[1]->mTransform.pos;
					p.x = 0.0f;
					Nami[1]->dotween->DoEaseOutCubic(p, 1.0f);
					Frame[1]->dotween->OnComplete([&]() {
						isOnce = true;
						isCoin = true;

						if (Coin != nullptr)
						{
							Coin->GetDotween()->DoEaseOutBack({ -5.0f,-0.2f,WHITEBG_POS_Z - 0.512f }, 1.0f);
						}
						
						});
				});
			
			isFrame = true;

		}

		if (isOnce == true)
		{
			
			for (int i = 0; i < 6; i++)
			{
				Text[i]->dotween->DoEaseElasticScale({2.0f, 2.0f,1.0f }, 2.0f);
			}

			

			Text[5]->dotween->OnComplete([&]()
				{
					isNoMoving = true;

					if (Coin != nullptr)
					{
						if (Coin->GetCoin() == 0)
						{

						}
						else if (Coin->GetCoin() == 1)
						{
							Coin->AddProtein();
						}
						else if (Coin->GetCoin() == 2)
						{
							Coin->AddProtein();
							Coin->GetDotween()->DelayedCall(0.1f, [&]() {
								Coin->AddProtein();
								});
						}
					}
					
				});

			isOnce = false;

		}
		
	}
	else {

		if (input->GetInputTrigger(InputType::DECIDE))
		{
			selectControl->PushButton();
		}

		selectControl->FlagUpdate();
		if (input->GetMovement().x < 0)
		{
			selectControl->ButtonMove(-1);
		}
		if (input->GetMovement().x > 0)
		{
			selectControl->ButtonMove(1);
		}

		if (player->isWalkAnim == true && isStopAnim == false)
		{
			player->mTransform.pos.x -= 0.1f;
			if (player->mTransform.pos.x < 0)
			{
				player->mTransform.pos.x = 0;
				player->SetTexture(player_EatTexture);
				isStopAnim = true;
				player->isEatAnim = false;

			}
		}

	}

	if (Coin != nullptr)
	{
		Coin->Update();
	}
	
	player->Update();

	Bg->Update();

	for (int i = 0; i < 2; i++)
	{
		Frame[i]->Update();
	}

	for (int i = 0; i < 2; i++)
	{
		Nami[i]->Update();
	}

	for (int i = 0; i < 2; i++)
	{
		Message[i]->Update();
	}

	for (int i = 0; i < 6; i++)
	{
		Text[i]->Update();
	}
}

void CGameClear::LateUpdate()
{
}

void CGameClear::Draw()
{
	Bg->Draw();

	for (int i = 0; i < 2; i++)
	{
		Frame[i]->Draw();
	}

	for (int i = 0; i < 2; i++)
	{
		Nami[i]->Draw();
	}

	for (int i = 0; i < 6; i++)
	{
		Text[i]->Draw();
	}

	if (isNoMoving == true)
	{
		for (int i = 0; i < 2; i++)
		{
			Message[i]->Draw();
		}

	}

	if (isCoin == true)
	{
		if (Coin != nullptr)
		{
			Coin->Draw();
		}
	}
	

	if (isNoMoving == true)
	{
		player->Draw();
	}
	
}

void CGameClear::SetFunc(int _num, std::function<void()> _onComplete)
{
	Message[_num]->SetFunc(_onComplete);
}
