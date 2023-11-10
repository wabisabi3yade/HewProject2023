#include "CCamera.h"

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
