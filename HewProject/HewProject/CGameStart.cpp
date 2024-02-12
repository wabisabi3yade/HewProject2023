#include "CGameStart.h"
#include "UI.h"
#include "TextureFactory.h"


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

	isProtein = false;
}

CGameStart::~CGameStart()
{
	CLASS_DELETE(Bg);
	CLASS_DELETE(Text);

	SAFE_RELEASE(bgBuffer);
	SAFE_RELEASE(textBuffer);
}

void CGameStart::Update()
{
	
	if (isProtein == false)
	{
		isProtein = true;

		Text->dotween->DoMoveX(0, 0.5f);
		Text->dotween->Join(0, 1.0f, DoTweenUI::FUNC::DELAY);
		Text->dotween->Append({-10.0f,3.0f,0}, 0.5f, DoTweenUI::FUNC::EASE_INBACK);
		Text->dotween->OnComplete([&]() {
			Text->SetActive(false);
			Bg->SetActive(false);
			});
		
	}
	
	Bg->Update();

	Text->Update();
}

void CGameStart::LateUpdate()
{
}

void CGameStart::Draw()
{
	Bg->Draw();
	
	Text->Draw();
}
