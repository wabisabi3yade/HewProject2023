#include "CMenu.h"
#include "TextureFactory.h"
#include "UI.h"
#include "InputManager.h"
#include "ButtonSelect.h"
#include "ButtonUI.h"

#define HELP_POSX (-3.0f)
#define HELP_POSY (3.0f)

#define BG_POS_Z (-0.11f)
#define UI_POS_Z (-0.12f)

CMenu::CMenu()
{
	D3D_CreateSquare({ 1,1 }, &bgBuffer);
	bgTexture = TextureFactory::GetInstance()->Fetch(L"asset/UI/FadeBlack.png");
	ruleTexture = TextureFactory::GetInstance()->Fetch(L"asset/UI/Ty_Frame.png");

	Bg = new UI(bgBuffer, bgTexture);
	Bg->SetColor({ 0,0,0 });
	Bg->SetAlpha(0.5f);
	Bg->mTransform.pos = { 0,0,BG_POS_Z };
	Bg->mTransform.scale = { 16.0f,9.0f,1.0f };

	for (int i = 0; i < MAXNUM_HELP; i++)
	{
		Rule[i] = new UI(bgBuffer, ruleTexture);
		Rule[i]->mTransform.pos = { 0,0,UI_POS_Z };
		Rule[i]->mTransform.scale = { 13.0f - i * 1.0f,8.0f,1.0f };
	}

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
	Message[0]->SetScale({ 4.0f,4.0f,1.0f });
	Message[0]->SetHighlight(true);
	Message[0]->SetFunc([&]() {
		CScene::SetScene(SCENE_NAME::MENU);
		});

	Message[1] = new ButtonUI(textBoxBuffer, textBoxTexture, textBuffer, text_helpTexture);
	Message[1]->SetPosition({ 0,-1.0f,UI_POS_Z });
	Message[1]->SetScale({ 4.0f,4.0f,1.0f });
	Message[1]->SetHighlight(false);
	Message[1]->SetFunc([&]() {
		isHelp = true;
		//nRule = 0;
		});

	Message[2] = new ButtonUI(textBoxBuffer, textBoxTexture, textBuffer, text_escapeTexture);
	Message[2]->SetPosition({ 0,-3.0f,UI_POS_Z });
	Message[2]->SetScale({ 4.0f,4.0f,1.0f });
	Message[2]->SetHighlight(false);
	Message[2]->SetFunc([&]() {
		CScene::SetScene(SCENE_NAME::SELECT);
		});

	D3D_CreateSquare({ 2,1 }, &LRBuffer);
	LRTexture = TextureFactory::GetInstance()->Fetch(L"asset/UI/B_LB_RB.png");
	BTexture = TextureFactory::GetInstance()->Fetch(L"asset/UI/B_Return.png");

	B_Button = new UI(textBuffer, BTexture);
	B_Button->mTransform.pos = { -6.5f,-4.0f,UI_POS_Z-0.01f };
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
		LR_Button[i]->dotween->Append(Small, 1.0f,DoTweenUI::FUNC::SCALE);
		LR_Button[i]->dotween->SetLoop(-1);
	}

	LR_Button[0]->mTransform.pos = { -7.2f,0,UI_POS_Z };
	LR_Button[1]->mTransform.pos = { 7.2f,0,UI_POS_Z };
	LR_Button[1]->SetUV(1.0f / 2.0f * 1.0f, 0);

	helpMessage[0] = new ButtonUI(textBoxBuffer, textBoxTexture, textBuffer, text_escapeTexture);
	helpMessage[0]->SetPosition({ HELP_POSX,HELP_POSY,UI_POS_Z });
	helpMessage[0]->SetScale({ 4.0f,4.0f,1.0f });
	helpMessage[0]->SetHighlight(true);
	helpMessage[0]->SetFunc([&]() {
		nRule = 0;
		isExplanation = true;
		});

	helpMessage[1] = new ButtonUI(textBoxBuffer, textBoxTexture, textBuffer, text_helpTexture);
	helpMessage[1]->SetPosition({ HELP_POSX,HELP_POSY - 2.0f,UI_POS_Z });
	helpMessage[1]->SetScale({ 4.0f,4.0f,1.0f });
	helpMessage[1]->SetFunc([&]() {
		nRule = 1;
		isExplanation = true;
		});

	helpMessage[2] = new ButtonUI(textBoxBuffer, textBoxTexture, textBuffer, text_retryTexture);
	helpMessage[2]->SetPosition({ HELP_POSX,HELP_POSY - 4.0f,UI_POS_Z });
	helpMessage[2]->SetScale({ 4.0f,4.0f,1.0f });
	helpMessage[2]->SetFunc([&]() {
		nRule = 2;
		isExplanation = true;
		});

	helpMessage[3] = new ButtonUI(textBoxBuffer, textBoxTexture, textBuffer, text_retryTexture);
	helpMessage[3]->SetPosition({ HELP_POSX,HELP_POSY - 6.0f,UI_POS_Z });
	helpMessage[3]->SetScale({ 4.0f,4.0f,1.0f });
	helpMessage[3]->SetFunc([&]() {
		nRule = 3;
		isExplanation = true;
		});

	helpMessage[4] = new ButtonUI(textBoxBuffer, textBoxTexture, textBuffer, text_escapeTexture);
	helpMessage[4]->SetPosition({ HELP_POSX + 6.0f,HELP_POSY,UI_POS_Z });
	helpMessage[4]->SetScale({ 4.0f,4.0f,1.0f });
	helpMessage[4]->SetFunc([&]() {
		nRule = 4;
		isExplanation = true;
		});

	helpMessage[5] = new ButtonUI(textBoxBuffer, textBoxTexture, textBuffer, text_escapeTexture);
	helpMessage[5]->SetPosition({ HELP_POSX + 6.0f,HELP_POSY - 2.0f,UI_POS_Z });
	helpMessage[5]->SetScale({ 4.0f,4.0f,1.0f });
	helpMessage[5]->SetFunc([&]() {
		nRule = 5;
		isExplanation = true;
		});

	helpMessage[6] = new ButtonUI(textBoxBuffer, textBoxTexture, textBuffer, text_escapeTexture);
	helpMessage[6]->SetPosition({ HELP_POSX + 6.0f,HELP_POSY - 4.0f,UI_POS_Z });
	helpMessage[6]->SetScale({ 4.0f,4.0f,1.0f });
	helpMessage[6]->SetFunc([&]() {
		nRule = 6;
		isExplanation = true;
		});

	helpMessage[7] = new ButtonUI(textBoxBuffer, textBoxTexture, textBuffer, text_escapeTexture);
	helpMessage[7]->SetPosition({ HELP_POSX + 6.0f,HELP_POSY - 6.0f,UI_POS_Z });
	helpMessage[7]->SetScale({ 4.0f,4.0f,1.0f });
	helpMessage[7]->SetFunc([&]() {
		nRule = 7;
		isExplanation = true;
		});

	helpMessage[8] = new ButtonUI(textBoxBuffer, textBoxTexture, textBuffer, text_escapeTexture);
	helpMessage[8]->SetPosition({ HELP_POSX,HELP_POSY ,UI_POS_Z });
	helpMessage[8]->SetScale({ 4.0f,4.0f,1.0f });
	helpMessage[8]->SetHighlight(true);
	helpMessage[8]->SetFunc([&]() {
		nRule = 8;
		isExplanation = true;
		});

	helpMessage[9] = new ButtonUI(textBoxBuffer, textBoxTexture, textBuffer, text_escapeTexture);
	helpMessage[9]->SetPosition({ HELP_POSX,HELP_POSY -2.0f,UI_POS_Z });
	helpMessage[9]->SetScale({ 4.0f,4.0f,1.0f });
	helpMessage[9]->SetFunc([&]() {
		nRule = 9;
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

	for (int i = 0; i < 3; i++)
	{
		CLASS_DELETE(Message[i]);
	}

	for (int i = 0; i < MAXNUM_HELP; i++)
	{
		CLASS_DELETE(helpMessage[i]);
	}

	for (int i = 0; i < MAXNUM_HELP; i++)
	{
		CLASS_DELETE(Rule[i]);
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
					}
				}
				else {
					
					helpControl->FlagUpdate();
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
					}
				}
				
			}
			else {
				
				if (isChangeExplanation == false)
				{
					if (input->GetInputTrigger(InputType::L_BUTTON))
					{
						nRule--;
						helpControl->ButtonMove(-1);
						if (nRule < 0)
						{
							nRule = MAXNUM_HELP - 3;
						}
					}
					else if (input->GetInputTrigger(InputType::R_BUTTON))
					{
						nRule++;
						helpControl->ButtonMove(1);

						if (nRule > MAXNUM_HELP - 3)
						{
							nRule = 0;
						}
					}
					else if (input->GetInputTrigger(InputType::CANCEL))
					{
						isExplanation = false;
					}
				}
				else {
					if (input->GetInputTrigger(InputType::L_BUTTON))
					{
						nRule--;
						help_2PageControl->ButtonMove(-1);

						if (nRule < 8)
						{
							nRule = MAXNUM_HELP - 1;
						}
					}
					else if (input->GetInputTrigger(InputType::R_BUTTON))
					{
						nRule++;
						help_2PageControl->ButtonMove(1);
						if (nRule > MAXNUM_HELP - 1)
						{
							nRule = 8;
						}
					}
					else if (input->GetInputTrigger(InputType::CANCEL))
					{
						isExplanation = false;
					}
				}
				
			}
			
		}
	}
	
	Bg->Update();

	Pause->Update();

	B_Button->Update();

	for (int i = 0; i < 3; i++)
	{
		Message[i]->Update();
	}

	for (int i = 0; i < MAXNUM_HELP; i++)
	{
		helpMessage[i]->Update();
	}

	for (int i = 0; i < MAXNUM_HELP; i++)
	{
		Rule[i]->Update();
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
			if (isExplanation==false)
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
				if (nRule == 0)
				{
					Rule[0]->Draw();
				}
				else if (nRule == 1)
				{
					Rule[1]->Draw();
				}
				else if (nRule == 2)
				{
					Rule[2]->Draw();
				}
				else if (nRule == 3)
				{
					Rule[3]->Draw();
				}
				else if (nRule == 4)
				{
					Rule[4]->Draw();
				}
				else if (nRule == 5)
				{
					Rule[5]->Draw();
				}
				else if (nRule == 6)
				{
					Rule[6]->Draw();
				}
				else if (nRule == 7)
				{
					Rule[7]->Draw();
				}
				else if (nRule == 8)
				{
					Rule[8]->Draw();
				}
				else if (nRule == 9)
				{
					Rule[9]->Draw();
				}

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
