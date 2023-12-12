#include "CWakamuraScene.h"
#include "CSceneManager.h"
#include "CDirectWrite.h"

extern DirectWrite* Write;

CWakamuraScene::CWakamuraScene()
{
}

CWakamuraScene::~CWakamuraScene()
{
}

void CWakamuraScene::Update()
{
	
}

void CWakamuraScene::LateUpdate()
{
}

void CWakamuraScene::Draw()
{
	Write->DrawString("‚ ‚¢‚¤‚¦‚¨", DirectX::XMFLOAT2(90, 90), D2D1_DRAW_TEXT_OPTIONS_NONE);
	Write->DrawString("‚ ‚¢‚¤‚¦‚¨", DirectX::XMFLOAT2(90, 390), D2D1_DRAW_TEXT_OPTIONS_NONE);
}
