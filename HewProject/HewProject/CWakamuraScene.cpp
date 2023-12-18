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
	Write->DrawString("�n�V���g�C�b�p�c�M���O", DirectX::XMFLOAT2(90, 0), D2D1_DRAW_TEXT_OPTIONS_NONE);

	Write->SetFont(Font::HG_Gyosyo);
	Write->DrawString("MS���� �p�̖����i��", DirectX::XMFLOAT2(90, 100), D2D1_DRAW_TEXT_OPTIONS_NONE);

	test->Draw();

	Write->SetFont(Font::HG_Gyosyo);
	Write->DrawString(std::to_string(Write->nKcal), DirectX::XMFLOAT2(90, 180), D2D1_DRAW_TEXT_OPTIONS_NONE);

	Write->SetFont(Font::komadorimini);
	Write->DrawString("���܂ǂ�݂� �炢�߂��ƂƂ��ɂ���I", DirectX::XMFLOAT2(90, 200), D2D1_DRAW_TEXT_OPTIONS_NONE);

	Write->SetFont(Font::marker);
	Write->DrawString("���C���I �܂��撣��", DirectX::XMFLOAT2(90, 250), D2D1_DRAW_TEXT_OPTIONS_NONE);


}
