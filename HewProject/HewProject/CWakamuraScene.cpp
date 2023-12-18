#include "CWakamuraScene.h"
#include "CSceneManager.h"
#include "CDirectWrite.h"
#include "Ckcal_gauge.h"
#include <string>


extern DirectWrite* Write;
CWakamuraScene::CWakamuraScene()
{
	test = new Ckcal_gauge();
}

CWakamuraScene::~CWakamuraScene()
{
	CLASS_DELETE(test);
}

void CWakamuraScene::Update()
{
	test->Update();
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

	Write->SetFont(Font::HG_Gyosyo);
	Write->DrawString(std::to_string(Write->nKcal), DirectX::XMFLOAT2(90, 180), D2D1_DRAW_TEXT_OPTIONS_NONE);

	Write->SetFont(Font::komadorimini);
	Write->DrawString("こまどりみに らいめいとともにちれ！", DirectX::XMFLOAT2(90, 200), D2D1_DRAW_TEXT_OPTIONS_NONE);

	Write->SetFont(Font::marker);
	Write->DrawString("メイリオ まぁ頑張れ", DirectX::XMFLOAT2(90, 250), D2D1_DRAW_TEXT_OPTIONS_NONE);


}
