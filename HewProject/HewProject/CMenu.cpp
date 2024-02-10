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

	Bg = new UI(bgBuffer, bgTexture);
	Bg->SetColor({ 0,0,0 });
	Bg->SetAlpha(0.5f);
	Bg->mTransform.pos = { 0,0,0.1f };
	Bg->mTransform.scale = { 16.0f,9.0f,1.0f };

	D3D_CreateSquare({ 1,1 }, &pauseBuffer);
	pauseTexture = TextureFactory::GetInstance()->Fetch(L"asset/Text/Pause.png");

	Pause = new UI(pauseBuffer, pauseTexture);
	Pause->mTransform.pos = { 0,3.0f,0 };
	Pause->mTransform.scale = { 4.0f,3.0f,1 };

	D3D_CreateSquare({ 1,2 }, &textBoxBuffer);
	textBoxTexture = TextureFactory::GetInstance()->Fetch(L"asset/UI/Button.png");

	D3D_CreateSquare({ 1,1 }, &textBuffer);
	text_retryTexture = TextureFactory::GetInstance()->Fetch(L"asset/Text/T_Restart.png");
	text_helpTexture = TextureFactory::GetInstance()->Fetch(L"asset/Text/T_Help.png");
	text_escapeTexture = TextureFactory::GetInstance()->Fetch(L"asset/Text/T_Back.png");

	Message[0] = new ButtonUI(textBoxBuffer, textBoxTexture, textBuffer, text_retryTexture);
	Message[0]->SetPosition({ 0,3.0f,0 });
	Message[0]->SetScale({ 4.0f,4.0f,1.0f });
	Message[0]->SetHighlight(true);
	Message[0]->SetFunc([&]() {
		CScene::SetScene(SCENE_NAME::MENU);
		});

	Message[1] = new ButtonUI(textBoxBuffer, textBoxTexture, textBuffer, text_helpTexture);
	Message[1]->SetPosition({ 0,0,0 });
	Message[1]->SetScale({ 4.0f,4.0f,1.0f });
	Message[1]->SetHighlight(false);
	Message[1]->SetFunc([&]() {
		isHelp = true;
		});

	Message[2] = new ButtonUI(textBoxBuffer, textBoxTexture, textBuffer, text_escapeTexture);
	Message[2]->SetPosition({ 0,-3.0f,0 });
	Message[2]->SetScale({ 4.0f,4.0f,1.0f });
	Message[2]->SetHighlight(false);
	Message[2]->SetFunc([&]() {
		CScene::SetScene(SCENE_NAME::SELECT);
		});

	// ボタン選択クラス作成
	selectControl = new ButtonSelect();
	selectControl->Regist(Message[0]);
	selectControl->Regist(Message[1]);
	selectControl->Regist(Message[2]);

	isHelp = false;
	isMenu = false;
}

CMenu::~CMenu()
{
	CLASS_DELETE(Bg);

	CLASS_DELETE(selectControl);

	CLASS_DELETE(Pause);

	for (int i = 0; i < 3; i++)
	{
		CLASS_DELETE(Message[i]);
	}
}

void CMenu::Update()
{
	InputManager* input = InputManager::GetInstance();
	
	if (input->GetInputTrigger(InputType::OPTION))
	{
		isMenu = true;
	}

	if (isMenu == true)
	{
		if (isHelp == false)
		{
			if (input->GetInputTrigger(InputType::DECIDE))
			{
				selectControl->PushButton();
			}

			if (input->GetInputTrigger(InputType::CANCEL))
			{
				isMenu = false;
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
				
			}

			if (input->GetInputTrigger(InputType::R_BUTTON))
			{

			}

			if (input->GetInputTrigger(InputType::CANCEL))
			{
				isHelp = false;
			}
		}

		
	}

	

	Bg->Update();

	Pause->Update();

	for (int i = 0; i < 3; i++)
	{
		Message[i]->Update();
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

			for (int i = 0; i < 3; i++)
			{
				Message[i]->Draw();
			}
		}
		
	}

}
