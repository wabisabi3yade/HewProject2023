#include "CKawadaScene.h"
#include "CSceneManager.h"
#include "xa2.h"

CKawadaScene::CKawadaScene()
{
	//========�T�E���h������=======//
	HRESULT hr;
	hr = XA_Initialize();
	if (FAILED(hr)) // XA_Initialize�֐������s����������
	{
		MessageBoxA(NULL, "�T�E���h���������s", "�G���[",MB_ICONERROR | MB_OK);      
	}
	//=============================//
	
	//BGM�Đ�
	XA_Play(SOUND_LABEL_BGM000);
}

CKawadaScene::~CKawadaScene()
{
	//===�T�E���h�������===//
	XA_Release();
	//======================//
}

void CKawadaScene::Update()
{
	if (gInput->GetKeyTrigger(VK_SPACE))
	{
		//SE�Đ�
		XA_Play(SOUND_LABEL_SE000);
	}
		
}

void CKawadaScene::LateUpdate()
{
	
}

void CKawadaScene::Draw()
{
	//BGM�Đ�
	//XA_Play(SOUND_LABEL_BGM000);
	//BGM��~
	//XA_Stop(SOUND_LABEL_BGM000);
}
