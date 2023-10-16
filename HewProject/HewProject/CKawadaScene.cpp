#include "CKawadaScene.h"
#include "CSceneManager.h"
#include "xa2.h"

CKawadaScene::CKawadaScene()
{
	//========サウンド初期化=======//
	HRESULT hr;
	hr = XA_Initialize();
	if (FAILED(hr)) // XA_Initialize関数が失敗したか判定
	{
		MessageBoxA(NULL, "サウンド初期化失敗", "エラー",MB_ICONERROR | MB_OK);      
	}
	//=============================//
	
	//BGM再生
	XA_Play(SOUND_LABEL_BGM000);
}

CKawadaScene::~CKawadaScene()
{
	//===サウンド解放処理===//
	XA_Release();
	//======================//
}

void CKawadaScene::Update()
{
	if (gInput->GetKeyTrigger(VK_SPACE))
	{
		//SE再生
		XA_Play(SOUND_LABEL_SE000);
	}
		
}

void CKawadaScene::LateUpdate()
{
	
}

void CKawadaScene::Draw()
{
	//BGM再生
	//XA_Play(SOUND_LABEL_BGM000);
	//BGM停止
	//XA_Stop(SOUND_LABEL_BGM000);
}
