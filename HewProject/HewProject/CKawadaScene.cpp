#include "CKawadaScene.h"
#include "CSceneManager.h"
#include "xa2.h"
#include "CEffectManeger.h"
#include "CDirectWrite.h"
#include <string>

extern DirectWrite* Write;
CKawadaScene::CKawadaScene()
{
	////========�T�E���h������=======//
	//HRESULT hr;
	//hr = XA_Initialize();
	//if (FAILED(hr)) // XA_Initialize�֐������s����������
	//{
	//	MessageBoxA(NULL, "�T�E���h���������s", "�G���[",MB_ICONERROR | MB_OK);      
	//}
	////=============================//
	//
	////BGM�Đ�
	//XA_Play(SOUND_LABEL_BGM000);

	FXinstance = EffectManeger::GetInstance();
}

CKawadaScene::~CKawadaScene()
{
	////===�T�E���h�������===//
	//XA_Release();
	////======================//
}

void CKawadaScene::Update()
{
	//if (gInput->GetKeyTrigger(VK_SPACE))
	//{
	//	//SE�Đ�
	//	XA_Play(SOUND_LABEL_SE000);
	//}

	//if (gInput->GetKeyTrigger(VK_TAB))
	//{
	//	XA_Stop(SOUND_LABEL_BGM000);

	//	Vector3 v = Vector3::zero;
	//	Vector3 v2 = Vector3::one;
	//	EffectManeger* x = EffectManeger::GetInstance();
	//	x->Play(v, v2, x->CHARE, false);
	//}

	static Vector3 scale = { 2.0f,2.0f,1.0f };

	if (gInput->GetKeyTrigger(VK_UP))
	{
		scale.x += 0.2f;
		scale.y += 0.2f;
	}

	if (gInput->GetKeyTrigger(VK_DOWN))
	{
		scale.x -= 0.2f;
		scale.y -= 0.2f;

		if (scale.x < 0.1f)
		{
			scale.x = 0.1f;
		}

		if (scale.y < 0.1f)
		{
			scale.y = 0.1f;
		}
	}

	if (gInput->GetKeyTrigger(VK_RIGHT))
	{
		test++;
		if (test > FXinstance->GetTexBoxSize() - 1)
			test = FXinstance->GetTexBoxSize() - 1;
	}

	if (gInput->GetKeyTrigger(VK_LEFT))
	{
		test--;
		if (test < 0) test = 0;
	}

	if (gInput->GetKeyTrigger(VK_RETURN))
		FXinstance->Play(Vector3::zero, scale, (EffectManeger::FX_TYPE)test, false);



}

void CKawadaScene::LateUpdate()
{

}

void CKawadaScene::Draw()
{
	Write->SetFont(Font::Arial);
	Write->DrawString("�G�t�F�N�g�^�C�v", DirectX::XMFLOAT2(90, 0), D2D1_DRAW_TEXT_OPTIONS_NONE);

	Write->DrawString(std::to_string(test), DirectX::XMFLOAT2(400, 0), D2D1_DRAW_TEXT_OPTIONS_NONE);
}
