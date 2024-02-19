#include "CWakamuraScene.h"
#include "CSceneManager.h"
#include "CDirectWrite.h"
#include "Ckcal_gauge.h"

#include "Player.h"
#include <string>


CWakamuraScene::CWakamuraScene()
{
	D3D_CreateSquare({ 3,4 }, &playerBuffer);
	D3D_LoadTexture(L"asset/wakamura/char01.png", &playerTexture);

	player = new Player(playerBuffer, playerTexture);
	
	test = new Ckcal_gauge();
}

CWakamuraScene::~CWakamuraScene()
{
	CLASS_DELETE(test);
	CLASS_DELETE(player);

	SAFE_RELEASE(playerBuffer);
}

void CWakamuraScene::Update()
{
	player->Update();
}

void CWakamuraScene::LateUpdate()
{

}

void CWakamuraScene::Draw()
{

	Write->SetFont(Font::MelodyLine);
	Write->DrawString("ハシモトイッパツギャグ", DirectX::XMFLOAT2(90, 0), D2D1_DRAW_TEXT_OPTIONS_NONE);

	Write->SetFont(Font::HG_Gyosyo);
	Write->DrawString("MS明朝 術の名は麒麟", DirectX::XMFLOAT2(90, 100), D2D1_DRAW_TEXT_OPTIONS_NONE);

	test->Draw();
	player->Draw();

	Write->SetFont(Font::komadorimini);
	Write->DrawString("こまどりみに らいめいとともにちれ！", DirectX::XMFLOAT2(90, 200), D2D1_DRAW_TEXT_OPTIONS_NONE);

	Write->SetFont(Font::marker);
	Write->DrawString("メイリオ まぁ頑張れ", DirectX::XMFLOAT2(90, 250), D2D1_DRAW_TEXT_OPTIONS_NONE);


}
