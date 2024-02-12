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
}

CGameStart::~CGameStart()
{
	CLASS_DELETE(Bg);

	SAFE_RELEASE(bgBuffer);
}

void CGameStart::Update()
{
	Bg->Update();
}

void CGameStart::LateUpdate()
{
}

void CGameStart::Draw()
{
	Bg->Draw();
}
