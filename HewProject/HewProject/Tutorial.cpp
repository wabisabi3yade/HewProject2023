#include "Tutorial.h"
#include "TextureFactory.h"
#include "InputManager.h"

#define FADEIN_TIME (0.5f)
#define FADEOUT_TIME (0.5f)
#define FADE_ALPHATIMES (0.5f)

#define BASE_POSZ (-0.488f)

#define LR_BIGSCALE_TIMES (1.15f)
#define LR_SMOLLSCALE_TIMES (1.0f)
#define LR_SCALING_TIME (1.0f)

Tutorial::Tutorial(bool _is1_1)
{
	base = new UI();
	base->MakeDotween();

	isStage1_1 = _is1_1;

	if (isStage1_1)
	{
		D3D_LoadTexture(L"asset/Tutorial/T_3.png", &tex1_1);
	}

	D3D_CreateSquare({ 1,1 }, &tutorialBuf);

	D3DTEXTURE work = TextureFactory::GetInstance()->Fetch(L"asset/UI/White.png");
	fade = new UI(tutorialBuf, work);
	fade->mTransform.pos.z = BASE_POSZ;
	fade->mTransform.scale = { 16.0f, 9.0f, 1.0f };
	fade->SetColor({});

	tutorialUI = new UI(tutorialBuf, NULL);
	tutorialUI->mTransform.pos.z = BASE_POSZ - UI_OFFSETZ;
	tutorialUI->mTransform.scale = { 12.44f, 7.0f, 1.0f };


	work = TextureFactory::GetInstance()->Fetch(L"asset/UI/B_Return.png");
	backUI = new UI(tutorialBuf, work);
	backUI->mTransform.pos = { -6.5f,-4.0f,BASE_POSZ - UI_OFFSETZ };
	backUI->mTransform.scale = { 2.4f,0.8f,1.0f };

	D3D_CreateSquare({ 2,1 }, &LR_Buf);
	work = TextureFactory::GetInstance()->Fetch(L"asset/UI/B_LB_RB.png");
	for (int i = 0; i < 2; i++)
	{
		LR_UI[i] = new UI(LR_Buf, work);
		LR_UI[i]->mTransform.scale = { 1.0f,1.0f,1.0f };
		LR_UI[i]->MakeDotween();
		LR_UI[i]->SetUV(i * 0.5f, 0.0f);

		Vector3 Big = LR_UI[i]->mTransform.scale * LR_BIGSCALE_TIMES;
		Big.z = 1.0f;
		Vector3 Small = LR_UI[i]->mTransform.scale * LR_SMOLLSCALE_TIMES;
		LR_UI[i]->dotween->DoScale(Big, LR_SCALING_TIME);
		LR_UI[i]->dotween->Append(Small, LR_SCALING_TIME, DoTweenUI::FUNC::SCALE);
		LR_UI[i]->dotween->SetLoop(-1);
	}

	LR_UI[0]->mTransform.pos = { -7.2f, 0.0f, BASE_POSZ - UI_OFFSETZ };
	LR_UI[1]->mTransform.pos = { 7.2f, 0.0f, BASE_POSZ - UI_OFFSETZ };
}

Tutorial::~Tutorial()
{
	CLASS_DELETE(tutorialUI);
	SAFE_RELEASE(tutorialBuf);

	for (auto a : tutorialTex)
	{
		SAFE_RELEASE(a);
	}

	CLASS_DELETE(base);
	CLASS_DELETE(fade);
	CLASS_DELETE(backUI);

	for (int i = 0; i < 2; i++)
	{
		CLASS_DELETE(LR_UI[i]);
	}
	SAFE_RELEASE(LR_Buf);

	SAFE_RELEASE(tex1_1);

}

void Tutorial::Display()
{
	isActive = true;
	state = STATE::FADE_IN;
	ChangeLR(1);
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

	if (state == STATE::FADE_IN || state == STATE::FADE_OUT)
	{
		float a = base->materialDiffuse.w;
		// 全体の透明度に合わせる
		tutorialUI->SetAlpha(a);
		fade->SetAlpha(a - FADE_ALPHATIMES);
		backUI->SetAlpha(a);

		for (int i = 0; i < 2; i++)
		{
			LR_UI[i]->SetAlpha(a);
		}
	}

	for (int i = 0; i < 2; i++)
	{
		LR_UI[i]->dotween->Update();
	}
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

	if (tutorialTex.size() <= 2)
	{	//1ページ目
		if (nowPage == 1 && input->GetInputTrigger(InputType::R_BUTTON))
		{
			nowPage = 2;
			ChangeLR(nowPage);
			tutorialUI->SetTexture(tutorialTex[nowPage - 1]);
		}
		//2ページ目
		else if (nowPage == 2 && input->GetInputTrigger(InputType::L_BUTTON))
		{
			nowPage = 1;
			ChangeLR(nowPage);
			tutorialUI->SetTexture(tutorialTex[nowPage - 1]);
		}
	}

	if (input->GetInputTrigger(InputType::CANCEL) && isCanBack)
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
		isActive = false;

		if (isMacho)
		{
			isMachoOnce = true;
			isMacho = false;
		}
	}
}

void Tutorial::Draw()
{
	if (!isActive) return;

	fade->Draw();

	if (isCanBack)
	{
		backUI->Draw();
	}

	// ２枚以上あるときは
	if (tutorialTex.size() >= 2)
	{
		for (int i = 0; i < 2; i++)
		{
			LR_UI[i]->Draw();
		}
	}
	

	tutorialUI->Draw();
}

void Tutorial::SetPosition(const Vector3& _p)
{
	base->mTransform.pos = _p;
}

void Tutorial::SetTexture(D3DTEXTURE _tex)
{
	bool isFirst = false;
	if (tutorialTex.size() == 0)
	{
		isFirst = true;
	}
	else
	{
		isCanBack = false;
		backUI->SetActive(false);
	}

	tutorialTex.push_back(_tex);

	if (isFirst)
	{
		tutorialUI->SetTexture(tutorialTex[0]);
	}
}

void Tutorial::ChangeLR(int num)
{
	for (int i = 0; i < 2; i++)
	{
		LR_UI[i]->SetActive(false);
	}

	if (isMacho || tutorialTex.size() < 2) return;

	int buttonNum = 1;
	
	if(num == 2)
	{
		buttonNum = 0;
		isCanBack = true;
		backUI->SetActive(true);
	}

	
	LR_UI[buttonNum]->SetActive(true);
	
}

int Tutorial::GetState()
{
	return state;
}

bool Tutorial::GetIs1_1()
{
	return isStage1_1;
}

void Tutorial::MachoDisplay()
{
	isMacho = true;

	tutorialUI->SetTexture(tex1_1);

	Display();
}

bool Tutorial::GetIsMachoOnce()
{
	return isMachoOnce;
}
