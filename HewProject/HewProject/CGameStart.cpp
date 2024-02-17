#include "CGameStart.h"
#include "UI.h"
#include "TextureFactory.h"
#include "ProteinUI.h"

#define GAMESTART_POS_Z (-0.496f)

CGameStart::CGameStart(int _num)
{
	D3D_CreateSquare({ 1,1 }, &bgBuffer);
	bgTexture = TextureFactory::GetInstance()->Fetch(L"asset/UI/FadeBlack.png");

	Bg = new UI(bgBuffer, bgTexture);
	Bg->MakeDotween();
	Bg->SetColor({ 0,0,0 });
	Bg->SetAlpha(0);
	Bg->mTransform.pos = { 0,0,GAMESTART_POS_Z };
	Bg->mTransform.scale = { 16.0f,9.0f,1.0f };

	D3D_CreateSquare({ 1,1 }, &textBuffer);
	textTexture = TextureFactory::GetInstance()->Fetch(L"asset/Text/T_GoalAt.png");

	Text = new UI(textBuffer, textTexture);
	Text->MakeDotween();
	Text->mTransform.pos = { 12.0f,2.0f,GAMESTART_POS_Z-0.00001f };
	Text->mTransform.scale = { 6.0f,1.5f,1.0f };

	nNumProtein = _num;
	fProteinZ = GAMESTART_POS_Z - 0.00002f;

	Protein = new ProteinUI(nNumProtein, false);
	Protein->SetPosition({ 11.0f,0,fProteinZ });
	Protein->SetScale({ 2,2});
	Protein->SetActive(false);


	isProtein = false;
	isMoveing = false;
}

CGameStart::~CGameStart()
{
	CLASS_DELETE(Bg);
	CLASS_DELETE(Text);
	CLASS_DELETE(Protein)

	SAFE_RELEASE(bgBuffer);
	SAFE_RELEASE(textBuffer);
}

void CGameStart::Update()
{
	
	if (isProtein == false)
	{
		isProtein = true;

		Bg->dotween->DoAlpha(0.5f, 0.2f);
		Bg->dotween->OnComplete([&]() {
			Text->dotween->DoEaseOutBack({ 0,2.0f,GAMESTART_POS_Z - 0.00001f }, 0.4f);
			Text->dotween->Join(0, 2.0f, DoTweenUI::FUNC::DELAY);
			Text->dotween->Append({ -10.0f,2.0f,GAMESTART_POS_Z - 0.00001f }, 0.3f, DoTweenUI::FUNC::EASE_INBACK);
			Text->dotween->OnComplete([&]() {
				Text->SetActive(false);
				});

			if (nNumProtein == 1)
			{
				Protein->GetDotween()->DoEaseOutBack(0, 0.8f);
				Protein->GetDotween()->Append({ -10.0f,0,GAMESTART_POS_Z - 0.00002f }, 0.3f, DoTweenUI::FUNC::DELAY);
				Protein->GetDotween()->OnComplete([&]() {
					Protein->SetActive(true);
					Protein->AddProtein();
					Protein->GetDotween()->DelayedCall(0.9f, [&]() {
						Protein->GetDotween()->DoEaseInBack({ -10.0f,0,GAMESTART_POS_Z - 0.00002f }, 0.5f);
						Protein->GetDotween()->OnComplete([&]() {
							Bg->dotween->DoAlpha(0, 0.2f);
							Protein->SetProtein(false);
							isMoveing = true;
							});
						});
					});
			}
			else if (nNumProtein == 2)
			{
				Protein->GetDotween()->DoEaseOutBack(0, 0.8f);
				Protein->GetDotween()->Append({ -10.0f,0,GAMESTART_POS_Z - 0.00002f }, 0.1f, DoTweenUI::FUNC::DELAY);
				Protein->GetDotween()->OnComplete([&]() {
					Protein->SetActive(true);
					Protein->AddProtein();
					Protein->GetDotween()->DelayedCall(0.1f, [&]() {
						Protein->AddProtein();
						Protein->GetDotween()->DelayedCall(1.0f, [&]() {
							Protein->GetDotween()->DoEaseInBack({ -10.0f,0,GAMESTART_POS_Z - 0.00002f }, 0.5f);
							Protein->GetDotween()->OnComplete([&]() {
								Bg->dotween->DoAlpha(0, 0.2f);
								Protein->SetProtein(false);
								isMoveing = true;
								});
							});
						});

					});
			}
			else if (nNumProtein == 3)
			{
				Protein->GetDotween()->DoEaseOutBack(0, 0.8f);
				Protein->GetDotween()->Append({ -10.0f,0,GAMESTART_POS_Z - 0.00002f }, 0.1f, DoTweenUI::FUNC::DELAY);
				Protein->GetDotween()->OnComplete([&]() {
					Protein->SetActive(true);
					Protein->AddProtein();
					Protein->GetDotween()->DelayedCall(0.1f, [&]() {
						Protein->AddProtein();
						Protein->GetDotween()->DelayedCall(0.1f, [&]() {
							Protein->AddProtein();
							Protein->GetDotween()->DelayedCall(1.0f, [&]() {
								Protein->GetDotween()->DoEaseInBack({ -12.0f,0,GAMESTART_POS_Z - 0.00002f }, 0.5f);
								Protein->GetDotween()->OnComplete([&]() {
									Bg->dotween->DoAlpha(0, 0.2f);
									Protein->SetProtein(false);
									isMoveing = true;
									});
								});
							});
						});
					});
			}
			});

		
		
		
	}
	
	Bg->Update();

	Text->Update();

	Protein->Update();
}

void CGameStart::LateUpdate()
{
}

void CGameStart::Draw()
{
	Bg->Draw();
	
	Text->Draw();

	Protein->Draw();
}
