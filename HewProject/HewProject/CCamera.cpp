#include "CCamera.h"
#include "CScene.h"
float CCamera::scaleScreen = 1.0f;	// 画像の大きさ（値が小さくなるほど画像は大きくなる）

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
