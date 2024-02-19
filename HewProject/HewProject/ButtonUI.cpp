#include "ButtonUI.h"
#include "ShadowUI.h"
#define TXT_OFFSETY (0.2f)	// ボタンよりちょい上

#define BTN_HORI_RATIO (4)	// ボタンの画像縦1に対して横の比率
#define TXT_HORI_RATIO (8)	// テキスト画像縦1に対して横の比率

#define LIGHT_SCALEUPTIMES (1.5f)	// ハイライト中のUIの大きさ
#define LIGHT_SCALEDOWNTIMES (1.3f)	// ハイライト中のUIの大きさ

#define SCALEUP_TIME (0.8f)	// 大きくなるまでの大きさ
#define WAIT_TIME (0.0f)	// ハイライト中のUIの大きさ

#define FLASH_TIME (0.1f)
#define FLASH_ENDTIME (3.0f)

Vector3 ButtonUI::ButtonScaleConversion(const Vector3& _scale)
{
	return { _scale.x, _scale.y / BTN_HORI_RATIO, 1.0f };
}

Vector3 ButtonUI::TextScaleConversion(const Vector3& _scale)
{
	return { _scale.x * textScaleTimes, _scale.y / TXT_HORI_RATIO * textScaleTimes , 1.0f };
}

void ButtonUI::ScaleLoop(Vector3 _downScale, Vector3 _upScale)
{
	button->mTransform.scale = ButtonScaleConversion(_downScale);
	button->dotween->DoScale(ButtonScaleConversion(_upScale), SCALEUP_TIME);
	button->dotween->Append(ButtonScaleConversion(_downScale), SCALEUP_TIME, DoTweenUI::FUNC::SCALE);
	button->dotween->Append(Vector3::zero, WAIT_TIME, DoTweenUI::FUNC::DELAY);
	button->dotween->SetLoop(-1);

	text->mTransform.scale = TextScaleConversion(_downScale);
	text->dotween->DoScale(TextScaleConversion(_upScale), SCALEUP_TIME);
	text->dotween->Append(TextScaleConversion(_downScale), SCALEUP_TIME, DoTweenUI::FUNC::SCALE);
	text->dotween->Append(Vector3::zero, WAIT_TIME, DoTweenUI::FUNC::DELAY);
	text->dotween->SetLoop(-1);
}

ButtonUI::ButtonUI(D3DBUFFER _buttonBuffer, D3DTEXTURE _buttonTex, D3DBUFFER _textBuffer, D3DTEXTURE _textTex)
{
	button = new UI(_buttonBuffer, _buttonTex);
	button->MakeDotween();
	text = new ShadowUI(_textBuffer, _textTex);
	text->MakeDotween();

	SetPosition(Vector3::zero);
	SetScale(Vector3::one);
}

void ButtonUI::Draw()
{
	button->Draw();
	text->Draw();
}

ButtonUI::~ButtonUI()
{
	CLASS_DELETE(button);
	CLASS_DELETE(text);
}

void ButtonUI::Update()
{
	button->Update();

	text->Update();

	if (isFlash)
	{
		elapsedTime += 1.0f / 60;

		if (elapsedTime > FLASH_TIME)
		{
			nowUV += 0.5f;
			if (nowUV >= 1.0f) nowUV = 0.0f;

			button->SetUV(0.0f, nowUV);
		}

		if (elapsedTime > FLASH_ENDTIME)
		{
			isFlash = false;
		}
	}

}

void ButtonUI::SetHighlight(bool _isLight)
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
		upScale.z = 1.0f;

		ScaleLoop(downScale, upScale);
	}
	if (!_isLight)
	{
		button->dotween->Stop();
		button->mTransform.scale = ButtonScaleConversion(grayState_scale);

		text->dotween->Stop();
		text->mTransform.scale = TextScaleConversion(grayState_scale);
	}

	button->SetUV(0.0f, v);
}

void ButtonUI::SetFlash()
{
	isFlash = true;
	nowUV = 0.5f;
}

void ButtonUI::SetScale(const Vector3& _scale)
{
	// 灰色状態の大きさとして代入する
	grayState_scale = _scale;
	grayState_scale.z = 1.0f;

	// 横4 縦1
	button->mTransform.scale = { _scale.x , _scale.y / BTN_HORI_RATIO, 1.0f };

	text->mTransform.scale = { _scale.x * textScaleTimes, _scale.y / TXT_HORI_RATIO * textScaleTimes , 1.0f };

	text->mTransform.pos.y = button->mTransform.pos.y + TXT_OFFSETY * text->mTransform.scale.y;
}

void ButtonUI::SetPosition(const Vector3& _pos)
{
	button->mTransform.pos = _pos;
	text->mTransform.pos = _pos;
	text->mTransform.pos.y += TXT_OFFSETY * text->mTransform.scale.y;
	text->mTransform.pos.z -= UI_OFFSETZ;
}

void ButtonUI::SetFunc(std::function<void()> _setFunction)
{
	func = _setFunction;
}

void ButtonUI::SetSceneName(int _setName)
{
	nextSceneName = _setName;
}

int ButtonUI::GetSceneName() const
{
	return nextSceneName;
}

void ButtonUI::BeginFunc()
{
	if (func == nullptr) return;
	func();
}

void ButtonUI::MakeDotween()
{
	button->MakeDotween();
}

DoTweenUI* ButtonUI::GetDotween()
{
	return button->dotween;
}
