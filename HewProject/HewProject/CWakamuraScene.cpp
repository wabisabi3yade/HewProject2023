#include "CWakamuraScene.h"
#include "CSceneManager.h"
#include "CDirectWrite.h"
#include "Ckcal_gauge.h"

#include "Player.h"
#include <string>


extern DirectWrite* Write;
CWakamuraScene::CWakamuraScene()
{
	D3D_CreateSquare({ 3,4 }, &playerBuffer);
	D3D_LoadTexture(L"asset/wakamura/char01.png", &playerTexture);

	D3D_CreateSquare({ 3,4 }, &playerBuffer);
	D3D_LoadTexture(L"asset/wakamura/char02.png", &playerTexture1);

	player = new Player(playerBuffer, playerTexture);
	
	test = new Ckcal_gauge();
}

CWakamuraScene::~CWakamuraScene()
{
	CLASS_DELETE(test);
	CLASS_DELETE(player);
}

void CWakamuraScene::Update()
{
	player->Update();
	test->Update();

	if (isFlashTime == true)
	{
		if (isGO == false)
		{
			player->SetTexture(playerTexture);
			isGO = true;
		}
		else {
			player->SetTexture(playerTexture1);

			isGO = false;
		}

		if (GetTickCount64() > pushTime + 1 * 1000)
		{
			if (isChange == false)
			{
				player->SetTexture(playerTexture1);
				isChange = true;
				isFlashTime = false;
			}
			else {
				player->SetTexture(playerTexture);
				isChange = false;
				isFlashTime = false;
			}

		}
	}


	if (gInput->GetKeyTrigger(VK_SPACE))
	{
		pushTime = GetTickCount64();
		isFlashTime = true;
	}
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

	Write->SetFont(Font::HG_Gyosyo);
	Write->DrawString(std::to_string(Write->nKcal), DirectX::XMFLOAT2(90, 180), D2D1_DRAW_TEXT_OPTIONS_NONE);

	Write->SetFont(Font::komadorimini);
	Write->DrawString("こまどりみに らいめいとともにちれ！", DirectX::XMFLOAT2(90, 200), D2D1_DRAW_TEXT_OPTIONS_NONE);

	Write->SetFont(Font::marker);
	Write->DrawString("メイリオ まぁ頑張れ", DirectX::XMFLOAT2(90, 250), D2D1_DRAW_TEXT_OPTIONS_NONE);


}
