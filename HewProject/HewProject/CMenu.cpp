#include "CMenu.h"
#include "TextureFactory.h"
#include "UI.h"
#include "InputManager.h"
#include "ButtonSelect.h"
#include "ButtonUI.h"

#define HELP_POSX (-3.0f)
#define HELP_POSY (3.0f)

#define BG_POS_Z (-0.488f)
#define UI_POS_Z (-0.489f)

#define MESSAGE_SCALE (4.0f)

CMenu::CMenu()
{
	D3D_CreateSquare({ 1,1 }, &bgBuffer);
	bgTexture = TextureFactory::GetInstance()->Fetch(L"asset/UI/FadeBlack.png");

	Bg = new UI(bgBuffer, bgTexture);
	Bg->SetColor({ 0,0,0 });
	Bg->SetAlpha(0.5f);
	Bg->mTransform.pos = { 0,0,BG_POS_Z };
	Bg->mTransform.scale = { 16.0f,9.0f,1.0f };

	D3D_LoadTexture(L"asset/Tutorial/T_1.png", &T_1Texture);
	D3D_LoadTexture(L"asset/Tutorial/T_2.png", &T_2Texture);
	D3D_LoadTexture(L"asset/Tutorial/T_3.png", &T_3Texture);
	D3D_LoadTexture(L"asset/Tutorial/T_4.png", &T_4Texture);
	D3D_LoadTexture(L"asset/Tutorial/T_5.png", &T_5Texture);
	D3D_LoadTexture(L"asset/Tutorial/T_6.png", &T_6Texture);
	D3D_LoadTexture(L"asset/Tutorial/T_7.png", &T_7Texture);
	D3D_LoadTexture(L"asset/Tutorial/T_8.png", &T_8Texture);
	D3D_LoadTexture(L"asset/Tutorial/T_9.png", &T_9Texture);
	D3D_LoadTexture(L"asset/Tutorial/T_10.png", &T_10Texture);

	D3D_LoadTexture(L"asset/Text/ty/T._Kihonsousa.png", &text_T_1Texture);
	D3D_LoadTexture(L"asset/Text/ty/T._Keki_Huto.png", &text_T_2Texture);
	D3D_LoadTexture(L"asset/Text/ty/T_Macho.png", &text_T_3Texture);
	D3D_LoadTexture(L"asset/Text/ty/T_YaseJyoutai.png", &text_T_4Texture);
	D3D_LoadTexture(L"asset/Text/ty/T_ItaChoco.png", &text_T_5Texture);
	D3D_LoadTexture(L"asset/Text/ty/T_Wataame.png", &text_T_6Texture);
	D3D_LoadTexture(L"asset/Text/ty/T_FuroaIdou.png", &text_T_7Texture);
	D3D_LoadTexture(L"asset/Text/ty/T_Tougarasi.png", &text_T_8Texture);
	D3D_LoadTexture(L"asset/Text/ty/T_Taihou.png", &text_T_9Texture);
	D3D_LoadTexture(L"asset/Text/ty/T_Coin.png", &text_T_10Texture);

	Tutorial = new UI(bgBuffer, T_1Texture);
	Tutorial->mTransform.pos = { 0,0,UI_POS_Z};
	Tutorial->mTransform.scale = { 12.44f,7.0f,1 };

	D3D_CreateSquare({ 1,1 }, &pauseBuffer);
	pauseTexture = TextureFactory::GetInstance()->Fetch(L"asset/Text/Pause.png");

	Pause = new UI(pauseBuffer, pauseTexture);
	Pause->MakeDotween();
	Pause->mTransform.pos = { 0,3.0f,UI_POS_Z };
	Pause->mTransform.scale = { 0.0f,0.0f,1 };

	D3D_CreateSquare({ 1,2 }, &textBoxBuffer);
	textBoxTexture = TextureFactory::GetInstance()->Fetch(L"asset/UI/Button.png");

	D3D_CreateSquare({ 1,1 }, &textBuffer);
	text_retryTexture = TextureFactory::GetInstance()->Fetch(L"asset/Text/T_Restart.png");
	text_helpTexture = TextureFactory::GetInstance()->Fetch(L"asset/Text/T_Help.png");
	text_escapeTexture = TextureFactory::GetInstance()->Fetch(L"asset/Text/T_Back.png");

	Message[0] = new ButtonUI(textBoxBuffer, textBoxTexture, textBuffer, text_retryTexture);
	Message[0]->SetPosition({ 0,1.0f,UI_POS_Z });
	Message[0]->SetScale({ MESSAGE_SCALE,MESSAGE_SCALE,1.0f });
	Message[0]->SetHighlight(true);
	Message[0]->SetFunc([&]() {
		Fade::GetInstance()->FadeIn(Fade::STATE::FADE_OUT, nullptr);
		isMenu = false;
		});

	Message[1] = new ButtonUI(textBoxBuffer, textBoxTexture, textBuffer, text_helpTexture);
	Message[1]->SetPosition({ 0,-1.0f,UI_POS_Z });
	Message[1]->SetScale({ MESSAGE_SCALE,MESSAGE_SCALE,1.0f });
	Message[1]->SetHighlight(false);
	Message[1]->SetFunc([&]() {
		isHelp = true;
		nRule = 0;
		});

	Message[2] = new ButtonUI(textBoxBuffer, textBoxTexture, textBuffer, text_escapeTexture);
	Message[2]->SetPosition({ 0,-3.0f,UI_POS_Z });
	Message[2]->SetScale({ MESSAGE_SCALE,MESSAGE_SCALE,1.0f });
	Message[2]->SetHighlight(false);
	Message[2]->SetFunc([&]() {
		Fade::GetInstance()->FadeIn(Fade::STATE::FADE_OUT, nullptr, CScene::SCENE_NAME::STAGE1);
		});

	D3D_CreateSquare({ 2,1 }, &LRBuffer);
	LRTexture = TextureFactory::GetInstance()->Fetch(L"asset/UI/B_LB_RB.png");
	BTexture = TextureFactory::GetInstance()->Fetch(L"asset/UI/B_Return.png");

	B_Button = new UI(textBuffer, BTexture);
	B_Button->mTransform.pos = { -6.5f,-4.0f,UI_POS_Z - 0.0001f };
	B_Button->mTransform.scale = { 2.4f,0.8f,1.0f };

	for (int i = 0; i < 2; i++)
	{
		LR_Button[i] = new UI(LRBuffer, LRTexture);
		LR_Button[i]->MakeDotween();
		LR_Button[i]->mTransform.scale = { 1.0f,1.0f,1.0f };
		Vector3 Big = LR_Button[i]->mTransform.scale * 1.15f;
		Big.z = 1.0f;
		Vector3 Small = LR_Button[i]->mTransform.scale * 1.0f;
		LR_Button[i]->dotween->DoScale(Big, 1.0f);
		LR_Button[i]->dotween->Append(Small, 1.0f, DoTweenUI::FUNC::SCALE);
		LR_Button[i]->dotween->SetLoop(-1);
	}

	LR_Button[0]->mTransform.pos = { -7.2f,0,UI_POS_Z };
	LR_Button[1]->mTransform.pos = { 7.2f,0,UI_POS_Z };
	LR_Button[1]->SetUV(1.0f / 2.0f * 1.0f, 0);

	helpMessage[0] = new ButtonUI(textBoxBuffer, textBoxTexture, textBuffer, text_T_1Texture);
	helpMessage[0]->SetPosition({ HELP_POSX,HELP_POSY,UI_POS_Z });
	helpMessage[0]->SetScale({ MESSAGE_SCALE,MESSAGE_SCALE,1.0f });
	helpMessage[0]->SetHighlight(true);
	helpMessage[0]->SetFunc([&]() {
		nRule = 0;
		Tutorial->SetTexture(T_1Texture);
		isExplanation = true;
		});

	helpMessage[1] = new ButtonUI(textBoxBuffer, textBoxTexture, textBuffer, text_T_2Texture);
	helpMessage[1]->SetPosition({ HELP_POSX,HELP_POSY - 2.0f,UI_POS_Z });
	helpMessage[1]->SetScale({ MESSAGE_SCALE,MESSAGE_SCALE,1.0f });
	helpMessage[1]->SetFunc([&]() {
		nRule = 1;
		Tutorial->SetTexture(T_2Texture);
		isExplanation = true;
		});

	helpMessage[2] = new ButtonUI(textBoxBuffer, textBoxTexture, textBuffer, text_T_3Texture);
	helpMessage[2]->SetPosition({ HELP_POSX,HELP_POSY - 4.0f,UI_POS_Z });
	helpMessage[2]->SetScale({ MESSAGE_SCALE,MESSAGE_SCALE,1.0f });
	helpMessage[2]->SetFunc([&]() {
		nRule = 2;
		Tutorial->SetTexture(T_3Texture);
		isExplanation = true;
		});

	helpMessage[3] = new ButtonUI(textBoxBuffer, textBoxTexture, textBuffer, text_T_4Texture);
	helpMessage[3]->SetPosition({ HELP_POSX,HELP_POSY - 6.0f,UI_POS_Z });
	helpMessage[3]->SetScale({ MESSAGE_SCALE,MESSAGE_SCALE,1.0f });
	helpMessage[3]->SetFunc([&]() {
		nRule = 3;
		Tutorial->SetTexture(T_4Texture);
		isExplanation = true;
		});

	helpMessage[4] = new ButtonUI(textBoxBuffer, textBoxTexture, textBuffer, text_T_5Texture);
	helpMessage[4]->SetPosition({ HELP_POSX + 6.0f,HELP_POSY,UI_POS_Z });
	helpMessage[4]->SetScale({ MESSAGE_SCALE,MESSAGE_SCALE,1.0f });
	helpMessage[4]->SetFunc([&]() {
		nRule = 4;
		Tutorial->SetTexture(T_5Texture);
		isExplanation = true;
		});

	helpMessage[5] = new ButtonUI(textBoxBuffer, textBoxTexture, textBuffer, text_T_6Texture);
	helpMessage[5]->SetPosition({ HELP_POSX + 6.0f,HELP_POSY - 2.0f,UI_POS_Z });
	helpMessage[5]->SetScale({ MESSAGE_SCALE,MESSAGE_SCALE,1.0f });
	helpMessage[5]->SetFunc([&]() {
		nRule = 5;
		Tutorial->SetTexture(T_6Texture);
		isExplanation = true;
		});

	helpMessage[6] = new ButtonUI(textBoxBuffer, textBoxTexture, textBuffer, text_T_7Texture);
	helpMessage[6]->SetPosition({ HELP_POSX + 6.0f,HELP_POSY - 4.0f,UI_POS_Z });
	helpMessage[6]->SetScale({ MESSAGE_SCALE,MESSAGE_SCALE,1.0f });
	helpMessage[6]->SetFunc([&]() {
		nRule = 6;
		Tutorial->SetTexture(T_7Texture);
		isExplanation = true;
		});

	helpMessage[7] = new ButtonUI(textBoxBuffer, textBoxTexture, textBuffer, text_T_8Texture);
	helpMessage[7]->SetPosition({ HELP_POSX + 6.0f,HELP_POSY - 6.0f,UI_POS_Z });
	helpMessage[7]->SetScale({ MESSAGE_SCALE,MESSAGE_SCALE,1.0f });
	helpMessage[7]->SetFunc([&]() {
		nRule = 7;
		Tutorial->SetTexture(T_8Texture);
		isExplanation = true;
		});

	helpMessage[8] = new ButtonUI(textBoxBuffer, textBoxTexture, textBuffer, text_T_9Texture);
	helpMessage[8]->SetPosition({ HELP_POSX,HELP_POSY ,UI_POS_Z });
	helpMessage[8]->SetScale({ MESSAGE_SCALE,MESSAGE_SCALE,1.0f });
	helpMessage[8]->SetHighlight(true);
	helpMessage[8]->SetFunc([&]() {
		nRule = 8;
		Tutorial->SetTexture(T_9Texture);
		isExplanation = true;
		});

	helpMessage[9] = new ButtonUI(textBoxBuffer, textBoxTexture, textBuffer, text_T_10Texture);
	helpMessage[9]->SetPosition({ HELP_POSX,HELP_POSY - 2.0f,UI_POS_Z });
	helpMessage[9]->SetScale({ MESSAGE_SCALE,MESSAGE_SCALE,1.0f });
	helpMessage[9]->SetFunc([&]() {
		nRule = 9;
		Tutorial->SetTexture(T_10Texture);
		isExplanation = true;
		});

	// ボタン選択クラス作成
	selectControl = new ButtonSelect();
	selectControl->Regist(Message[0]);
	selectControl->Regist(Message[1]);
	selectControl->Regist(Message[2]);

	helpControl = new ButtonSelect();
	helpControl->Regist(helpMessage[0]);
	helpControl->Regist(helpMessage[1]);
	helpControl->Regist(helpMessage[2]);
	helpControl->Regist(helpMessage[3]);
	helpControl->Regist(helpMessage[4]);
	helpControl->Regist(helpMessage[5]);
	helpControl->Regist(helpMessage[6]);
	helpControl->Regist(helpMessage[7]);

	help_2PageControl = new ButtonSelect();
	help_2PageControl->Regist(helpMessage[8]);
	help_2PageControl->Regist(helpMessage[9]);

	isHelp = false;
	isMenu = false;
	isOnce = false;
	isButton = false;
	isExplanation = false;
	isChangeExplanation = false;

	nRule = 0;
}

CMenu::~CMenu()
{
	CLASS_DELETE(Bg);

	CLASS_DELETE(selectControl);

	CLASS_DELETE(helpControl);

	CLASS_DELETE(help_2PageControl);

	CLASS_DELETE(Pause);

	CLASS_DELETE(B_Button);

	CLASS_DELETE(Tutorial);

	for (int i = 0; i < 3; i++)
	{
		CLASS_DELETE(Message[i]);
	}

	for (int i = 0; i < MAXNUM_HELP; i++)
	{
		CLASS_DELETE(helpMessage[i]);
	}

	for (int i = 0; i < 2; i++)
	{
		CLASS_DELETE(LR_Button[i]);
	}

	SAFE_RELEASE(bgBuffer);
	SAFE_RELEASE(pauseBuffer);
	SAFE_RELEASE(textBoxBuffer);
	SAFE_RELEASE(textBuffer);
	SAFE_RELEASE(LRBuffer);
	SAFE_RELEASE(T_1Texture);
	SAFE_RELEASE(T_2Texture);
	SAFE_RELEASE(T_3Texture);
	SAFE_RELEASE(T_4Texture);
	SAFE_RELEASE(T_5Texture);
	SAFE_RELEASE(T_6Texture);
	SAFE_RELEASE(T_7Texture);
	SAFE_RELEASE(T_8Texture);
	SAFE_RELEASE(T_9Texture);
	SAFE_RELEASE(T_10Texture);
	SAFE_RELEASE(text_T_1Texture);
	SAFE_RELEASE(text_T_2Texture);
	SAFE_RELEASE(text_T_3Texture);
	SAFE_RELEASE(text_T_4Texture);
	SAFE_RELEASE(text_T_5Texture);
	SAFE_RELEASE(text_T_6Texture);
	SAFE_RELEASE(text_T_7Texture);
	SAFE_RELEASE(text_T_8Texture);
	SAFE_RELEASE(text_T_9Texture);
	SAFE_RELEASE(text_T_10Texture);
}

void CMenu::Update()
{
	InputManager* input = InputManager::GetInstance();

	if (isMenu == false)
	{
		if (input->GetInputTrigger(InputType::OPTION))
		{
			isMenu = true;
			isOnce = false;
			isButton = false;
		}
	}
	else {
		if (isHelp == false)
		{
			if (isOnce == false)
			{
				Pause->dotween->DoScale({ 4.0f,1.0f,1.0f }, 0.1f);
				Pause->dotween->OnComplete([&]() {
					isButton = true;
					});
				isOnce = true;
			}

			if (input->GetInputTrigger(InputType::DECIDE))
			{
				selectControl->PushButton();
			}

			if (input->GetInputTrigger(InputType::CANCEL))
			{
				isMenu = false;
				Pause->mTransform.scale = { 0,0,1.0f };
			}

			selectControl->FlagUpdate();
			if (input->GetMovement().y < 0)
			{
				selectControl->ButtonMove(1);
			}
			else if (input->GetMovement().y > 0)
			{
				selectControl->ButtonMove(-1);
			}
		}
		else {

			if (isExplanation == false)
			{

				if (input->GetInputTrigger(InputType::CANCEL))
				{
					isHelp = false;
				}

				if (isChangeExplanation == true)
				{
					helpControl->FlagUpdate();
					help_2PageControl->FlagUpdate();
					if (input->GetMovement().y < 0)
					{
						help_2PageControl->ButtonMove(1);
					}

					else if (input->GetMovement().y > 0)
					{
						help_2PageControl->ButtonMove(-1);
					}

					else if (input->GetInputTrigger(InputType::DECIDE))
					{
						help_2PageControl->PushButton();
					}

					else if (input->GetInputTrigger(InputType::L_BUTTON))
					{
						isChangeExplanation = false;
						helpControl->SetButtonID(0);
					}
				}
				else {

					helpControl->FlagUpdate();
					help_2PageControl->FlagUpdate();
					if (input->GetMovement().y < 0)
					{
						helpControl->ButtonMove(1);
					}

					else if (input->GetMovement().y > 0)
					{
						helpControl->ButtonMove(-1);
					}

					else if (input->GetMovement().x < 0)
					{
						helpControl->ButtonMove(-4);
					}

					else if (input->GetMovement().x > 0)
					{
						helpControl->ButtonMove(4);
					}

					else if (input->GetInputTrigger(InputType::DECIDE))
					{
						helpControl->PushButton();
					}

					else if (input->GetInputTrigger(InputType::R_BUTTON))
					{
						isChangeExplanation = true;
						help_2PageControl->SetButtonID(0);
					}
				}

			}
			else {

				if (input->GetInputTrigger(InputType::L_BUTTON))
				{
					nRule--;
					if (nRule < 0)
					{
						nRule = MAXNUM_HELP - 1;
					}
				}
				else if (input->GetInputTrigger(InputType::R_BUTTON))
				{
					nRule++;

					if (nRule > MAXNUM_HELP - 1)
					{
						nRule = 0;
					}
				}
				else if (input->GetInputTrigger(InputType::CANCEL))
				{
					isExplanation = false;
				}

			}

			if (nRule == 0)
			{
				Tutorial->SetTexture(T_1Texture);
			}
			else if (nRule == 1)
			{
				Tutorial->SetTexture(T_2Texture);
			}
			else if (nRule == 2)
			{
				Tutorial->SetTexture(T_3Texture);
			}
			else if (nRule == 3)
			{
				Tutorial->SetTexture(T_4Texture);
			}
			else if (nRule == 4)
			{
				Tutorial->SetTexture(T_5Texture);
			}
			else if (nRule == 5)
			{
				Tutorial->SetTexture(T_6Texture);
			}
			else if (nRule == 6)
			{
				Tutorial->SetTexture(T_7Texture);
			}
			else if (nRule == 7)
			{
				Tutorial->SetTexture(T_8Texture);
			}
			else if (nRule == 8)
			{
				Tutorial->SetTexture(T_9Texture);
			}
			else if (nRule == 9)
			{
				Tutorial->SetTexture(T_10Texture);
			}

		}
	}

	Bg->Update();

	Pause->Update();

	B_Button->Update();

	Tutorial->Update();

	for (int i = 0; i < 3; i++)
	{
		Message[i]->Update();
	}

	for (int i = 0; i < MAXNUM_HELP; i++)
	{
		helpMessage[i]->Update();
	}


	for (int i = 0; i < 2; i++)
	{
		LR_Button[i]->Update();
	}
}

void CMenu::LateUpdate()
{

}

void CMenu::Draw()
{
	if (isMenu == true)
	{
		Bg->Draw();

		if (isHelp == false)
		{
			Pause->Draw();

			if (isButton == true)
			{
				for (int i = 0; i < 3; i++)
				{
					Message[i]->Draw();
				}
			}

		}
		else {
			if (isExplanation == false)
			{
				if (isChangeExplanation == false)
				{
					for (int i = 0; i < MAXNUM_HELP - 2; i++)
					{
						helpMessage[i]->Draw();
					}

					LR_Button[1]->Draw();

				}
				else {
					for (int i = MAXNUM_HELP - 2; i < MAXNUM_HELP; i++)
					{
						helpMessage[i]->Draw();
					}

					LR_Button[0]->Draw();

				}

			}
			else {
				
				Tutorial->Draw();

				for (int i = 0; i < 2; i++)
				{
					LR_Button[i]->Draw();
				}
			}

		}

		B_Button->Draw();

	}

}

bool CMenu::GetisMenu()
{
	return isMenu;
}

void CMenu::SetFunc(std::function<void()> _onComplete)
{
	Message[0]->SetFunc(_onComplete);
}
