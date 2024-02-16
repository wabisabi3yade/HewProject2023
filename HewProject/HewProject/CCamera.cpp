#include "CCamera.h"
#include "CScene.h"
float CCamera::scaleScreen = 1.0f;	// �摜�̑傫���i�l���������Ȃ�قǉ摜�͑傫���Ȃ�j
#include"DoTween.h"
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
	dotween->Update();
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

void CCamera::Zoom(float _targetScale, float _stageScale, Vector3 _targetPos)
{
	mTransform.scale.x = _targetScale * _stageScale;
	mTransform.scale.y = _targetScale * _stageScale;
	mTransform.pos = _targetPos;
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
	mTransform.scale = { 1.0f,1.0f,1.0f };
}


CCamera::~CCamera()
{
}
