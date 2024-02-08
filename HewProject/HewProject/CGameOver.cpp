#include "CGameOver.h"
#include "TextureFactory.h"
#include "UI.h"
#include "InputManager.h"
#include "CWorldSelectPlayer.h"
#include "ButtonUI.h"
#include "ButtonSelect.h"

CGameOver::CGameOver()
{
	D3D_CreateSquare({ 7,1 }, &text_failedBuffer);
	textTexture = TextureFactory::GetInstance()->Fetch(L"asset/UI/GAMEOVER.png");

	for (int i = 0; i < MAXNUM_TEXT; i++)
	{
		Text[i] = new UI(text_failedBuffer, textTexture);
		Text[i]->MakeDotween();
	}

	D3D_CreateSquare({ 1,2 }, &textBoxBuffer);
	/*textBox1Texture = TextureFactory::GetInstance()->Fetch(L"asset/UI/textBox_Blue.png");
	textBox2Texture = TextureFactory::GetInstance()->Fetch(L"asset/UI/textBox_White.png");
	textBox3Texture = TextureFactory::GetInstance()->Fetch(L"asset/UI/textBox_Pink.png");*/
	textBoxTexture = TextureFactory::GetInstance()->Fetch(L"asset/UI/Button.png");

	D3D_CreateSquare({ 1,1 }, &textBuffer);
	text_restartTexture = TextureFactory::GetInstance()->Fetch(L"asset/Text/T_Restart.png");
	text_undoTexture = TextureFactory::GetInstance()->Fetch(L"asset/Text/T_Undo.png");
	text_backTexture = TextureFactory::GetInstance()->Fetch(L"asset/Text/T_Back.png");

	D3D_CreateSquare({ 3,4 }, &playerBuffer);
	playerTexture = TextureFactory::GetInstance()->Fetch(L"asset/Player/T_Wait.png");


	Text[0]->mTransform.pos = { -3.5f,6.0f,0 };
	Text[0]->mTransform.scale = { 1.0f,1.0f,1.0f };

	Text[1]->mTransform.pos = { -2.5f,6.0f,0 };
	Text[1]->mTransform.scale = { 1.0f,1.0f,1.0f };
	Text[1]->SetUV(1.0f/7.0f*1.0f,0);

	Text[2]->mTransform.pos = { -1.5f,6.0f,0 };
	Text[2]->mTransform.scale = { 1.0f,1.0f,1.0f };
	Text[2]->SetUV(1.0f / 7.0f * 2.0f, 0);

	Text[3]->mTransform.pos = { -0.5f,6.0f,0 };
	Text[3]->mTransform.scale = { 1.0f,1.0f,1.0f };
	Text[3]->SetUV(1.0f / 7.0f * 3.0f, 0);

	Text[4]->mTransform.pos = { 0.5f,6.0f,0 };
	Text[4]->mTransform.scale = { 1.0f,1.0f,1.0f };
	Text[4]->SetUV(1.0f / 7.0f * 4.0f, 0);

	Text[5]->mTransform.pos = { 1.5f,6.0f,0 };
	Text[5]->mTransform.scale = { 1.0f,1.0f,1.0f };
	Text[5]->SetUV(1.0f / 7.0f * 5.0f, 0);

	Text[6]->mTransform.pos = { 2.5f,6.0f,0 };
	Text[6]->mTransform.scale = { 1.0f,1.0f,1.0f };
	Text[6]->SetUV(1.0f / 7.0f * 6.0f, 0);

	Text[7]->mTransform.pos = { 3.5f,6.0f,0 };
	Text[7]->mTransform.scale = { 1.0f,1.0f,1.0f };
	Text[7]->SetUV(1.0f / 7.0f * 3.0f, 0);

	Message[0] = new ButtonUI(textBoxBuffer, textBoxTexture,textBuffer,text_restartTexture);
	Message[0]->SetPosition({ -5.0f,-3.0f,0 });
	Message[0]->SetScale({ 4.0f,4.0f,1.0f });
	Message[0]->SetHighlight(true);
	Message[0]->SetFunc([&]() {
		CScene::SetScene(SCENE_NAME::SELECT);
		});

	Message[1] = new ButtonUI(textBoxBuffer, textBoxTexture,textBuffer,text_undoTexture);
	Message[1]->SetPosition({ 0,-3.0f,0 });
	Message[1]->SetScale({ 4.0f,4.0f,1.0f });
	Message[1]->SetFunc([&]() {
		CScene::SetScene(SCENE_NAME::TITLE);
		});

	Message[2] = new ButtonUI(textBoxBuffer, textBoxTexture,textBuffer,text_backTexture);
	Message[2]->SetPosition({ 5.0f,-3.0f,0 });
	Message[2]->SetScale({ 4.0f,4.0f,1.0f });
	Message[2]->SetFunc([&]() {
		CScene::SetScene(SCENE_NAME::GAMEOVER);
		});

	// ボタン選択クラス作成
	selectControl = new ButtonSelect();
	selectControl->Regist(Message[0]);
	selectControl->Regist(Message[1]);
	selectControl->Regist(Message[2]);

	Player = new CWorldSelectPlayer(playerBuffer, playerTexture);
	Player->mTransform.pos = { 0,0,0 };
	Player->mTransform.scale = { 4.0f,4.0f,1.0f };
	Player->isOnPlayer = false;

	isOnce = false;
	isNoMoving = false;
}

CGameOver::~CGameOver()
{
	for (int i = 0; i < MAXNUM_TEXT; i++)
	{
		CLASS_DELETE(Text[i]);
	}

	for (int i = 0; i < 3; i++)
	{
		CLASS_DELETE(Message[i]);
	}

	CLASS_DELETE(Player);
}

void CGameOver::Update()
{
	InputManager* input = InputManager::GetInstance();
	
	if (isNoMoving == false)
	{
		if (isOnce == false)
		{
			for (int i = 0; i < MAXNUM_TEXT; i++)
			{
				Text[i]->dotween->DoMoveY(3.0f, 1.0f);
			}

			Text[0]->dotween->OnComplete([&]()
				{
					//Text[0]->mTransform.rotation.z = 20.0f;
					isNoMoving = true;
				});

			isOnce = true;

		}
	}
	else {
		
		//if (isLate == false)
		//{
		//	if (input->GetMovement().x < 0)
		//	{
		//		isLate = true;
		//		nSelect--;
		//		if (nSelect < 0)
		//		{
		//			nSelect = 0;
		//		}

		//		if (isOnceBox == false)
		//		{
		//			isOnceBox = true;
		//			//Message[nSelect]->dotween->DoDelay(0.3f);
		//			/*Message[nSelect]->dotween->OnComplete([&]()
		//				{
		//					isLate = false;
		//					isOnceBox = false;
		//				});*/
		//		}
		//		

		//	}
		//	if (input->GetMovement().x > 0)
		//	{
		//		isLate = true;
		//		nSelect++;
		//		if (nSelect > 2)
		//		{
		//			nSelect = 2;
		//		}

		//		if (isOnceBox == false)
		//		{
		//			isOnceBox = true;
		//			/*Message[nSelect]->dotween->DoDelay(0.3f);
		//			Message[nSelect]->dotween->OnComplete([&]()
		//				{
		//					isLate = false;
		//					isOnceBox = false;
		//				});*/
		//		}
		//	}

			/*if (input->GetInputTrigger(InputType::DECIDE) && nSelect == 0)
			{
				CScene::SetScene(SCENE_NAME::SELECT);
			}

			if (input->GetInputTrigger(InputType::DECIDE) && nSelect == 1)
			{
				CScene::SetScene(SCENE_NAME::TITLE);
			}

			if (input->GetInputTrigger(InputType::DECIDE) && nSelect == 2)
			{
				CScene::SetScene(SCENE_NAME::GAMEOVER);
			}*/
		//}
		
		/*if (nSelect == 0)
		{
			Message[0]->SetHighlight(true);
			Message[1]->SetHighlight(false);
			Message[2]->SetHighlight(false);
		}
		else if (nSelect == 1)
		{
			Message[0]->SetHighlight(false);
			Message[1]->SetHighlight(true);
			Message[2]->SetHighlight(false);
		}
		else if (nSelect == 2)
		{
			Message[0]->SetHighlight(false);
			Message[1]->SetHighlight(false);
			Message[2]->SetHighlight(true);
		}*/

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
	
	
	Player->Update();
	
	for (int i = 0; i < 3; i++)
	{
		Message[i]->Update();
	}

	for (int i = 0; i < MAXNUM_TEXT; i++)
	{
		Text[i]->Update();
	}
}

void CGameOver::LateUpdate()
{
}

void CGameOver::Draw()
{
	for (int i = 0; i < MAXNUM_TEXT; i++)
	{
		Text[i]->Draw();
	}

	if (isNoMoving == true)
	{
		Message[0]->Draw();
		Message[1]->Draw();
		Message[2]->Draw();

		Player->Draw();

	}
}
