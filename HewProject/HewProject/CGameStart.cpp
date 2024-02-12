#include "CGameStart.h"
#include "UI.h"
#include "TextureFactory.h"
#include "ProteinUI.h"


CGameStart::CGameStart()
{
	D3D_CreateSquare({ 1,1 }, &bgBuffer);
	bgTexture = TextureFactory::GetInstance()->Fetch(L"asset/UI/FadeBlack.png");

	Bg = new UI(bgBuffer, bgTexture);
	Bg->SetColor({ 0,0,0 });
	Bg->SetAlpha(0.5f);
	Bg->mTransform.pos = { 0,0,0.1f };
	Bg->mTransform.scale = { 16.0f,9.0f,1.0f };

	D3D_CreateSquare({ 1,1 }, &textBuffer);
	textTexture = TextureFactory::GetInstance()->Fetch(L"asset/Text/T_Back.png");

	Text = new UI(textBuffer, textTexture);
	Text->MakeDotween();
	Text->mTransform.pos = { 8.0f,3.0f,0 };
	Text->mTransform.scale = { 4.0f,1.0f,1.0f };

	Protein = new ProteinUI(2, false);
	Protein->SetPosition({ 8.0f,0,0 });
	Protein->SetScale({ 2,2});

	isProtein = false;
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

		Text->dotween->DoMoveX(0, 0.4f);
		Text->dotween->Join(0, 2.0f, DoTweenUI::FUNC::DELAY);
		Text->dotween->Append({-10.0f,3.0f,0}, 0.5f, DoTweenUI::FUNC::EASE_INBACK);
		Text->dotween->OnComplete([&]() {
			Text->SetActive(false);
			});

		Protein->GetDotween()->DoMoveX(0, 0.8f);
		Protein->GetDotween()->Append({ -10.0f,0,0 }, 0.8f, DoTweenUI::FUNC::DELAY);
		Protein->GetDotween()->OnComplete([&]() {
			Protein->AddProtein();
			Protein->GetDotween()->DelayedCall(0.2f, [&]() {
				Protein->AddProtein();
				Protein->GetDotween()->DelayedCall(0.8f, [&]() {
					Protein->GetDotween()->DoEaseInBack({ -10.0f,0,0 }, 0.5f);
					Protein->GetDotween()->DelayedCall(0.8f, [&]() {
						Bg->SetActive(false);
						});
					});
				});
			
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
