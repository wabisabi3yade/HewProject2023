#include "CCamera.h"
#include "CScene.h"
float CCamera::scaleScreen = 1.0f;	// ‰æ‘œ‚Ì‘å‚«‚³i’l‚ª¬‚³‚­‚È‚é‚Ù‚Ç‰æ‘œ‚Í‘å‚«‚­‚È‚éj
#include"DoTween.h"
#include<iostream>
#include <random>
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

void CCamera::Zoom(float _targetScale, float _stageScale, Vector3 _targetPos)
{
	mTransform.scale.x = _targetScale * _stageScale;
	mTransform.scale.y = _targetScale * _stageScale;
	mTransform.pos = _targetPos;
}

void CCamera::Shake(float _duration, float _magnitude)
{
	isShake = true;
	endTime = 0.0f;
	o_pos = mTransform.pos;
	duration = _duration;
	magnitude = _magnitude;
}

void CCamera::ShakeUpdate()
{
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_real_distribution<float> distr(-1.0f, 1.0f);

	mTransform.pos.x = o_pos.x + distr(eng) * magnitude;
	mTransform.pos.y = o_pos.y + distr(eng) * magnitude;
	endTime += 1.0f / 60.0f;
	if(magnitude > 0.0f )
	magnitude -= 1.0f / 60.0f * 1.3f;
	if (endTime > duration)
	{
		isShake = false;
		mTransform.pos = o_pos;
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
	mTransform.scale = { 1.0f,1.0f,1.0f };
}


CCamera::~CCamera()
{
}
