#include "CMenu.h"
#include "TextureFactory.h"
#include "UI.h"
#include "InputManager.h"
#include "ButtonSelect.h"
#include "ButtonUI.h"


CMenu::CMenu()
{
	D3D_CreateSquare({ 1,1 }, &bgBuffer);
	bgTexture = TextureFactory::GetInstance()->Fetch(L"asset/UI/FadeBlack.png");
	ruleTexture = TextureFactory::GetInstance()->Fetch(L"asset/UI/Ty_Frame.png");

	Bg = new UI(bgBuffer, bgTexture);
	Bg->SetColor({ 0,0,0 });
	Bg->SetAlpha(0.5f);
	Bg->mTransform.pos = { 0,0,0.1f };
	Bg->mTransform.scale = { 16.0f,9.0f,1.0f };

	Rule[0] = new UI(bgBuffer, ruleTexture);
	Rule[0]->mTransform.pos = { 0,0,0 };
	Rule[0]->mTransform.scale = { 13.0f,8.0f,1.0f };

	D3D_CreateSquare({ 1,1 }, &pauseBuffer);
	pauseTexture = TextureFactory::GetInstance()->Fetch(L"asset/Text/Pause.png");

	Pause = new UI(pauseBuffer, pauseTexture);
	Pause->MakeDotween();
	Pause->mTransform.pos = { 0,3.0f,0 };
	Pause->mTransform.scale = { 0.0f,0.0f,1 };

	D3D_CreateSquare({ 1,2 }, &textBoxBuffer);
	textBoxTexture = TextureFactory::GetInstance()->Fetch(L"asset/UI/Button.png");

	D3D_CreateSquare({ 1,1 }, &textBuffer);
	text_retryTexture = TextureFactory::GetInstance()->Fetch(L"asset/Text/T_Restart.png");
	text_helpTexture = TextureFactory::GetInstance()->Fetch(L"asset/Text/T_Help.png");
	text_escapeTexture = TextureFactory::GetInstance()->Fetch(L"asset/Text/T_Back.png");

	Message[0] = new ButtonUI(textBoxBuffer, textBoxTexture, textBuffer, text_retryTexture);
	Message[0]->SetPosition({ 0,1.0f,0 });
	Message[0]->SetScale({ 4.0f,4.0f,1.0f });
	Message[0]->SetHighlight(true);
	Message[0]->SetFunc([&]() {
		CScene::SetScene(SCENE_NAME::MENU);
		});

	Message[1] = new ButtonUI(textBoxBuffer, textBoxTexture, textBuffer, text_helpTexture);
	Message[1]->SetPosition({ 0,-1.0f,0 });
	Message[1]->SetScale({ 4.0f,4.0f,1.0f });
	Message[1]->SetHighlight(false);
	Message[1]->SetFunc([&]() {
		isHelp = true;
		nRule = 0;
		});

	Message[2] = new ButtonUI(textBoxBuffer, textBoxTexture, textBuffer, text_escapeTexture);
	Message[2]->SetPosition({ 0,-3.0f,0 });
	Message[2]->SetScale({ 4.0f,4.0f,1.0f });
	Message[2]->SetHighlight(false);
	Message[2]->SetFunc([&]() {
		CScene::SetScene(SCENE_NAME::SELECT);
		});

	D3D_CreateSquare({ 2,1 }, &LRBuffer);
	LRTexture = TextureFactory::GetInstance()->Fetch(L"asset/UI/B_LB_RB.png");
	BTexture = TextureFactory::GetInstance()->Fetch(L"asset/UI/B_Return.png");

	B_Button = new UI(textBuffer, BTexture);
	B_Button->mTransform.pos = { -6.5f,-4.0f,-0.1f };
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

	LR_Button[0]->mTransform.pos = { -7.2f,0,-0.1f };
	LR_Button[1]->mTransform.pos = { 7.2f,0,-0.1f };
	LR_Button[1]->SetUV(1.0f / 2.0f * 1.0f, 0);

	// ボタン選択クラス作成
	selectControl = new ButtonSelect();
	selectControl->Regist(Message[0]);
	selectControl->Regist(Message[1]);
	selectControl->Regist(Message[2]);

	isHelp = false;
	isMenu = false;
	isOnce = false;
	isButton = false;

	nRule = 0;
}

CMenu::~CMenu()
{
	CLASS_DELETE(Bg);

	CLASS_DELETE(selectControl);

	CLASS_DELETE(Pause);

	CLASS_DELETE(B_Button);

	for (int i = 0; i < 3; i++)
	{
		CLASS_DELETE(Message[i]);
	}

	for (int i = 0; i < 1; i++)
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
			if (input->GetMovement().y > 0)
			{
				selectControl->ButtonMove(-1);
			}
		}
		else {
			if (input->GetInputTrigger(InputType::L_BUTTON))
			{
				nRule--;

				if (nRule < 0)
				{
					nRule = 3;
				}
			}

			if (input->GetInputTrigger(InputType::R_BUTTON))
			{
				nRule++;

				if (nRule > 3)
				{
					nRule = 0;
				}
			}

			if (input->GetInputTrigger(InputType::CANCEL))
			{
				isHelp = false;
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

	for (int i = 0; i < 1; i++)
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
			if (nRule == 0)
			{
				Rule[0]->Draw();
			}
			
			for (int i = 0; i < 2; i++)
			{
				LR_Button[i]->Draw();
			}

		}
		
		B_Button->Draw();

	}

}
