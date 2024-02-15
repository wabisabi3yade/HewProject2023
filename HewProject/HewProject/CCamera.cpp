#include "CCamera.h"
#include "CScene.h"
float CCamera::scaleScreen = 1.0f;	// ‰æ‘œ‚Ì‘å‚«‚³i’l‚ª¬‚³‚­‚È‚é‚Ù‚Ç‰æ‘œ‚Í‘å‚«‚­‚È‚éj

using namespace DirectX;

CCamera* CCamera::instance = nullptr;

CCamera::CCamera()
{
	Init();
}

CCamera* CCamera::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new CCamera();
	}

	return instance;
}

void CCamera::Update()
{
}

void CCamera::Zoom()
{
	if (gInput->GetKeyTrigger(VK_SPACE))
	{
		scaleScreen -= 0.1f;
		if (scaleScreen < 0.1f)
		{
			scaleScreen = 0.1f;
		}
	}
}

void CCamera::Zoom(float _targetScale, float _stageScale)
{
	scaleScreen = _targetScale * _stageScale;
}

void CCamera::Reduction()
{
	if (gInput->GetKeyTrigger(VK_BACK))
	{
		scaleScreen += 0.1f;
		if (scaleScreen > 2.0f)
		{
			scaleScreen = 2.0f;
		}
	}
}

void CCamera::Delete()
{
	CLASS_DELETE(instance);
}

void CCamera::Init()
{
	mTransform.pos = { 0, 0, 0 };
	mTransform.rotation.z = 0.0f;
}


CCamera::~CCamera()
{
}
