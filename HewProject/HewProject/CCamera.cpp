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
	pos = { 0, 0, 0 };
	rotZ = 0;
}


CCamera::~CCamera()
{
}
