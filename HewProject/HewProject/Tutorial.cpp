#include "Tutorial.h"
#include "TextureFactory.h"
#include "InputManager.h"

#define FADEIN_TIME (0.6f)
#define FADEOUT_TIME (0.6f)
#define FADE_ALPHATIMES (0.5f)

#define BASE_POSZ (-0.488f)

Tutorial::Tutorial(D3DTEXTURE _tex)
{
	base = new UI();
	base->MakeDotween();

	tutorialTex = _tex;

	D3D_CreateSquare({ 1,1 }, &tutorialBuf);

	D3DTEXTURE white = TextureFactory::GetInstance()->Fetch(L"asset/UI/White.png");
	fade = new UI(tutorialBuf, white);
	fade->mTransform.pos.z = BASE_POSZ;
	fade->mTransform.scale = {16.0f, 9.0f, 1.0f};
	fade->SetColor({});

	tutorialUI = new UI(tutorialBuf, tutorialTex);
	tutorialUI->mTransform.pos.z = BASE_POSZ - UI_OFFSETZ;
	tutorialUI->mTransform.scale = { 12.44f, 7.0f, 1.0f };

	backUI = new UI();
	backUI->mTransform.scale = {};
}

Tutorial::~Tutorial()
{
	CLASS_DELETE(tutorialUI);
	SAFE_RELEASE(tutorialBuf);
	CLASS_DELETE(base);
	CLASS_DELETE(fade);
}

void Tutorial::Display()
{
	isActive = true;
	state = STATE::FADE_IN;

	base->SetAlpha(0.0f);
}

void Tutorial::FeadOut()
{
}

void Tutorial::Update()
{
	if (!isActive) return;

	switch (state)
	{
	case Tutorial::STAY:
		break;
	case Tutorial::FADE_IN:
		FadeInUpdate();
		break;
	case Tutorial::DISPLAY:
		DisplayUpdate();
		break;
	case Tutorial::FADE_OUT:
		FadeOutUpdate();
		break;
	case Tutorial::END:
		break;
	default:
		break;
	}

	// ‘S‘Ì‚Ì“§–¾“x‚É‡‚í‚¹‚é
	tutorialUI->SetAlpha(base->materialDiffuse.w);
	fade->SetAlpha(base->materialDiffuse.w - FADE_ALPHATIMES);
}

void Tutorial::FadeInUpdate()
{
	float alphaSpeed = 1.0f / (FADEIN_TIME * 60);

	base->materialDiffuse.w += alphaSpeed;

	if (base->materialDiffuse.w > 1.0f)
	{
		base->materialDiffuse.w = 1.0f;
		state = STATE::DISPLAY;
	}
}

void Tutorial::DisplayUpdate()
{
	InputManager* input = InputManager::GetInstance();

	if (input->GetInputTrigger(InputType::CANCEL))
	{
		state = STATE::FADE_OUT;
	}
}

void Tutorial::FadeOutUpdate()
{
	float alphaSpeed = 1.0f / (FADEOUT_TIME * 60);

	base->materialDiffuse.w -= alphaSpeed;

	if (base->materialDiffuse.w < 0.0f)
	{
		base->materialDiffuse.w = 0.0f;
		state = STATE::END;
	}
}

void Tutorial::Draw()
{
	if (!isActive) return;

	fade->Draw();

	tutorialUI->Draw();
}

void Tutorial::SetPosition(const Vector3& _p)
{
	base->mTransform.pos = _p;
}
