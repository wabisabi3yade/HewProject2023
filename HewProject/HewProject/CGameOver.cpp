#include "CGameOver.h"
#include "TextureFactory.h"
#include "UI.h"
#include "InputManager.h"

CGameOver::CGameOver()
{
	D3D_CreateSquare({ 1,1 }, &textBuffer);
	textTexture = TextureFactory::GetInstance()->Fetch(L"asset/Stage/Castella.png");

	for (int i = 0; i < MAXNUM; i++)
	{
		Text[i] = new UI(textBuffer, textTexture);
		Text[i]->MakeDotween();
	}

	D3D_CreateSquare({ 1,1 }, &textBoxBuffer);
	textBox1Texture = TextureFactory::GetInstance()->Fetch(L"asset/UI/textBox_Blue.png");
	textBox2Texture = TextureFactory::GetInstance()->Fetch(L"asset/UI/textBox_Green.png");
	textBox3Texture = TextureFactory::GetInstance()->Fetch(L"asset/UI/textBox_Pink.png");

	Text[0]->mTransform.pos = { -1.5f,6.0f,0 };
	Text[0]->mTransform.scale = { 2.0f,2.0f,1.0f };

	Text[1]->mTransform.pos = { 1.5f,6.0f,0 };
	Text[1]->mTransform.scale = { 2.0f,2.0f,1.0f };

	Message[0] = new UI(textBoxBuffer, textBox1Texture);
	Message[0]->MakeDotween();
	Message[0]->mTransform.pos = { -5.0f,-2.0f,0 };
	Message[0]->mTransform.scale = { 2.0f,2.0f,1.0f };

	Message[1] = new UI(textBoxBuffer, textBox2Texture);
	Message[1]->MakeDotween();
	Message[1]->mTransform.pos = { 0,-2.0f,0 };
	Message[1]->mTransform.scale = { 2.0f,2.0f,1.0f };

	Message[2] = new UI(textBoxBuffer, textBox3Texture);
	Message[2]->MakeDotween();
	Message[2]->mTransform.pos = { 5.0f,-2.0f,0 };
	Message[2]->mTransform.scale = { 2.0f,2.0f,1.0f };

	isOnce = false;
	isOnceBox = false;
	isNoMoving = false;
	isLate = false;
	nSelect = 0;
	m_DrawCount = 0;
}

CGameOver::~CGameOver()
{
	for (int i = 0; i < MAXNUM; i++)
	{
		CLASS_DELETE(Text[i]);
	}

	for (int i = 0; i < 3; i++)
	{
		CLASS_DELETE(Message[i]);
	}
}

void CGameOver::Update()
{
	InputManager* input = InputManager::GetInstance();
	
	if (isNoMoving == false)
	{
		if (isOnce == false)
		{
			for (int i = 0; i < MAXNUM; i++)
			{
				Text[i]->dotween->DoMoveY(3.0f, 1.0f);
			}

			Text[0]->dotween->OnComplete([&]()
				{
					Text[0]->mTransform.rotation.z = 45.0f;
					isNoMoving = true;
				});

			isOnce = true;

		}
	}
	else {
		
		if (isLate == false)
		{
			if (input->GetMovement().x < 0)
			{
				isLate = true;
				nSelect--;
				if (nSelect < 0)
				{
					nSelect = 0;
				}

				if (isOnceBox == false)
				{
					isOnceBox = true;
					Message[nSelect]->dotween->DoDelay(1.0f);
					Message[nSelect]->dotween->OnComplete([&]()
						{
							isLate = false;
							isOnceBox = false;
						});
				}
				

			}
			if (input->GetMovement().x > 0)
			{
				isLate = true;
				nSelect++;
				if (nSelect > 2)
				{
					nSelect = 2;
				}

				if (isOnceBox == false)
				{
					isOnceBox = true;
					Message[nSelect]->dotween->DoDelay(1.0f);
					Message[nSelect]->dotween->OnComplete([&]()
						{
							isLate = false;
							isOnceBox = false;
						});
				}
			}
		}
		
	}
	
	

	
	for (int i = 0; i < 3; i++)
	{
		Message[i]->Update();
	}

	for (int i = 0; i < MAXNUM; i++)
	{
		Text[i]->Update();
	}
}

void CGameOver::LateUpdate()
{
}

void CGameOver::Draw()
{
	for (int i = 0; i < MAXNUM; i++)
	{
		Text[i]->Draw();
	}

	if (isNoMoving == true)
	{
		if (nSelect == 0)
		{
			if (m_DrawCount % 5 == 0)
			{
				Message[0]->Draw();
			}

			Message[1]->Draw();
			Message[2]->Draw();
		}
		else if(nSelect == 1)
		{
			if (m_DrawCount % 5 == 0)
			{
				Message[1]->Draw();
			}
			Message[0]->Draw();
			Message[2]->Draw();
		}
		else if (nSelect == 2)
		{
			if (m_DrawCount % 5 == 0)
			{
				Message[2]->Draw();
			}
			Message[0]->Draw();
			Message[1]->Draw();
		}

		++m_DrawCount;

	}
}
