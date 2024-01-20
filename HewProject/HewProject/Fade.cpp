#include "Fade.h"
#include "CObject.h"

Fade* Fade::instance = nullptr;

using namespace DirectX;

Fade::Fade()
{
	empty = new CObject(NULL, NULL);

	state = STATE::STAY;

	D3D_LoadTexture(L"asset/BackGround/fadeBack_Blue.png", &mTexture);

	D3D_CreateSquare({ 1,1 }, &mVertexBuffer);

}

// �`��Ɏg�p����e�N�X�`��
Fade::~Fade()
{

}

Fade* Fade::GetInstance()
{
	// �쐬���Ă��Ȃ��Ȃ�
	if (instance == nullptr)
	{
		instance = new Fade();
	}

	return instance;
}

void Fade::Delete()
{
	CLASS_DELETE(instance);
}

void Fade::Update()
{
	if (!isActive) return;

	switch (state)
	{
	case STATE::STAY:
		break;

	case STATE::FADE_IN:
		break;

	case STATE::LOADING:
		break;

	case STATE::FADE_OUT:
		break;

	default:
		MessageBoxA(NULL, "Fade�N���XUpdate��state�̒l���͈͊O�ł�", "�G���[", MB_ICONERROR | MB_OK);
		break;
	}
}

void Fade::StayUpdate()
{
}

void Fade::FadeInUpdate()
{
}

void Fade::LoadingUpdate()
{
}

void Fade::FadeOutUpdate()
{
}

void Fade::Draw()
{
	if (!isActive) return;

	
}

