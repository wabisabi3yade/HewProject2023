#include "StgButton.h"

#define LIGHT_SCALEUPTIMES (1.55f)	// ハイライト中のUIの大きさ
#define LIGHT_SCALEDOWNTIMES (1.4f)	// ハイライト中のUIの大きさ
#define SCALEUP_TIME (1.2f)	// 大きくなるまでの大きさ
#define SCALEWAIT_TIME (0.4f)	// 待機する時間

#define UP_FLASHTIME (0.5f)


void StgButton::ScaleLoop(Vector3 _downScale, Vector3 _upScale)
{
	button->mTransform.scale = _downScale;
	button->dotween->DoEaseOutCubicScale(_upScale, SCALEUP_TIME);
	button->dotween->Append(_downScale, SCALEUP_TIME, DoTweenUI::FUNC::EASE_OUTCUBIC_SCALE);
	button->dotween->Append(Vector3::zero, SCALEWAIT_TIME, DoTweenUI::FUNC::DELAY);
	button->dotween->SetLoop(-1);

	text->mTransform.scale = _downScale * textScaleTimes;
	text->dotween->DoEaseOutCubicScale(_upScale * textScaleTimes, SCALEUP_TIME);
	text->dotween->Append(_downScale * textScaleTimes, SCALEUP_TIME, DoTweenUI::FUNC::EASE_OUTCUBIC_SCALE);
	text->dotween->Append(Vector3::zero, SCALEWAIT_TIME, DoTweenUI::FUNC::DELAY);
	text->dotween->SetLoop(-1);
}

StgButton::StgButton(D3DBUFFER _buttonBuffer, D3DTEXTURE _buttonTex, D3DBUFFER _textBuffer, D3DTEXTURE _textTex)
	: ButtonUI(_buttonBuffer, _buttonTex, _textBuffer, _textTex)
{

	SetPosition(Vector3::zero);
	SetScale(Vector3::one);

	textScaleTimes = 0.6f;
}

StgButton::~StgButton()
{
}

void StgButton::Update()
{

	if (isFlash)
	{
		static short flashTimes = 0;
		elapsedTime += 1.0f / 60;

		if (elapsedTime > FLASH_TIME)
		{
			flashTimes++;
			nowUV += 0.5f;
			if (nowUV >= 1.0f) nowUV = 0.0f;

			button->SetUV(0.0f, nowUV);

			elapsedTime = 0.0f;
		}

		if (flashTimes > FLASH_END)
		{
			isFlash = false;
			flashTimes = 0;
			button->SetUV(0.0f, 0.5f);
		}
	}

	button->Update();

	text->mTransform.pos = button->mTransform.pos;
	text->mTransform.pos.z -= UI_OFFSETZ;
	text->Update();



}

void StgButton::Draw()
{
	button->Draw();
	text->Draw();
}

void StgButton::SetHighlight(bool _isLight)
{
	float v = 0.0f;
	//  2等分の下なので
	if (_isLight)
	{
		v = 0.5f;

		// 拡大のスケール
		Vector3 upScale = grayState_scale * LIGHT_SCALEUPTIMES;
		upScale.z = 1.0f;

		// 拡大のスケール
		Vector3 downScale = grayState_scale * LIGHT_SCALEDOWNTIMES;
		downScale.z = 1.0f;

		ScaleLoop(downScale, upScale);
	}
	else
	{
		button->dotween->Stop();
		button->mTransform.scale = grayState_scale;

		text->dotween->Stop();
		text->mTransform.scale = grayState_scale * textScaleTimes;
		text->mTransform.scale.z = 1.0f;
	}

	button->SetUV(0.0f, v);
}

void StgButton::SetScale(const Vector3& _scale)
{
	grayState_scale = _scale;

	// 横4 縦1
	button->mTransform.scale = { _scale.x , _scale.y, 1.0f };

	const float textScaleTimes = 0.7f;	// ボタンを1.0とした時のテキストの倍率
	text->mTransform.scale = { _scale.x * textScaleTimes, _scale.y * textScaleTimes , 1.0f };
}

void StgButton::SetPosition(const Vector3& _pos)
{
	button->mTransform.pos = _pos;
	text->mTransform.pos = _pos;
	text->mTransform.pos.z -= UI_OFFSETZ;
}

void StgButton::SetFunc(std::function<void()> _setFunction)
{
	func = _setFunction;
}

void StgButton::BeginFunc()
{
	if (func == nullptr) return;
	func();
}

void StgButton::SetNum(short num)
{
	text->SetUV(num % 3 * (1.0f / 3), num / 3 * (1.0f / 4));
}

void StgButton::SetFlash()
{
	isFlash = true;

	
}
