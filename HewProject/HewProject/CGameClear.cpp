#include "CGameClear.h"
#include "TextureFactory.h"
#include "UI.h"
#include "InputManager.h"
#include "ButtonUI.h"
#include "ButtonSelect.h"

CGameClear::CGameClear()
{
	D3D_CreateSquare({ 1,1 }, &bgBuffer);
	bgTexture = TextureFactory::GetInstance()->Fetch(L"asset/UI/FadeBlack.png");

	Bg = new UI(bgBuffer, bgTexture);
	Bg->materialDiffuse = { 1,1,1,0 };
	Bg->mTransform.pos = { 0,0,0.1f };
	Bg->mTransform.scale = { 16.0f,9.0f,1.0f };

	D3D_CreateSquare({ 6,1 }, &textBuffer);
	textTexture = TextureFactory::GetInstance()->Fetch(L"asset/UI/CLEAR.png");

	for (int i = 0; i < 6; i++)
	{
		Text[i] = new UI(textBuffer, textTexture);
		Text[i]->MakeDotween();
	}

	Text[0]->mTransform.pos = { -4.7f,6.0f,0 };
	Text[0]->mTransform.scale = { 2.0f,2.0f,1.0f };

	Text[1]->mTransform.pos = { -2.7f,6.0f,-0.01f };
	Text[1]->mTransform.scale = { 2.0f,2.0f,1.0f };
	Text[1]->SetUV(1.0f / 6.0f * 1.0f, 0);

	Text[2]->mTransform.pos = { -0.7f,6.0f,-0.02 };
	Text[2]->mTransform.scale = { 2.0f,2.0f,1.0f };
	Text[2]->SetUV(1.0f / 6.0f * 2.0f, 0);

	Text[3]->mTransform.pos = { 1.3f,6.0f,-0.03 };
	Text[3]->mTransform.scale = { 2.0f,2.0f,1.0f };
	Text[3]->SetUV(1.0f / 6.0f * 3.0f, 0);

	Text[4]->mTransform.pos = { 3.3f,6.0f,-0.04 };
	Text[4]->mTransform.scale = { 2.0f,2.0f,1.0f };
	Text[4]->SetUV(1.0f / 6.0f * 4.0f, 0);

	Text[5]->mTransform.pos = { 5.3f,6.0f,-0.05 };
	Text[5]->mTransform.scale = { 2.0f,2.0f,1.0f };
	Text[5]->SetUV(1.0f / 6.0f * 5.0f, 0);

	D3D_CreateSquare({ 1,2 }, &textBoxBuffer);
	textBoxTexture = TextureFactory::GetInstance()->Fetch(L"asset/UI/Button.png");

	D3D_CreateSquare({ 1,1 }, &textBuffer);
	text_nextStageTexture = TextureFactory::GetInstance()->Fetch(L"asset/Text/T_NextStage.png");
	text_stageSelectTexture = TextureFactory::GetInstance()->Fetch(L"asset/Text/T_StageSelectBack.png");

	Message[0] = new ButtonUI(textBoxBuffer, textBoxTexture, textBuffer, text_nextStageTexture);
	Message[0]->SetPosition({ -3.0f,-3.0f,0 });
	Message[0]->SetScale({ 4.0f,4.0f,1.0f });
	Message[0]->SetHighlight(true);
	Message[0]->SetFunc([&]() {
		CScene::SetScene(SCENE_NAME::SELECT);
		});

	Message[1] = new ButtonUI(textBoxBuffer, textBoxTexture, textBuffer, text_stageSelectTexture);
	Message[1]->SetPosition({ 3.0f,-3.0f,0 });
	Message[1]->SetScale({ 4.0f,4.0f,1.0f });
	Message[1]->SetFunc([&]() {
		CScene::SetScene(SCENE_NAME::GAMECLEAR);
		});

	// ボタン選択クラス作成
	selectControl = new ButtonSelect();
	selectControl->Regist(Message[0]);
	selectControl->Regist(Message[1]);

	isNoMoving = false;
	isOnce = false;
}

CGameClear::~CGameClear()
{
	for (int i = 0; i < 6; i++)
	{
		CLASS_DELETE(Text[i]);
	}

	for (int i = 0; i < 2; i++)
	{
		CLASS_DELETE(Message[i]);
	}

	CLASS_DELETE(Bg);
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

		if (isOnce == false)
		{
			for (int i = 0; i < 6; i++)
			{
				Text[i]->dotween->DoMoveY(3.0f, 1.0f);
			}

			Text[5]->dotween->OnComplete([&]()
				{
					isNoMoving = true;
				});

			isOnce = true;

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
	}

	Bg->Update();

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
}
