#include "StgButton.h"

#define LIGHT_SCALEUPTIMES (1.5f)	// ハイライト中のUIの大きさ
#define LIGHT_SCALEDOWNTIMES (1.3f)	// ハイライト中のUIの大きさ
#define SCALEUP_TIME (0.2f)	// 大きくなるまでの大きさ
#define SCALEWAIT_TIME (0.6f)	// 待機する時間


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
	button->Update();
	text->Update();
}

void StgButton::Draw()
{
	button->Draw();
	text->Draw();
}

void StgButton::SetHighlight(bool _isLight)
{
	float u = 0.0f;
	//  2等分の下なので
	if (_isLight)
	{
		u = 0.5f;

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

	button->SetUV(u, 0.0f);
}

void StgButton::SetScale(const Vector3& _scale)
{
	grayState_scale = _scale;

	// 横4 縦1
	button->mTransform.scale = { _scale.x , _scale.y, 1.0f };

	const float textScaleTimes = 0.7f;	// ボタンを1.0とした時のテキストの倍率
	text->mTransform.scale = { _scale.x * textScaleTimes, _scale.y  * textScaleTimes , 1.0f };

	/*text->mTransform.pos.y = button->mTransform.pos.y + TXT_OFFSETY * text->mTrasnsform.scale.y;*/
}

void StgButton::SetPosition(const Vector3& _pos)
{
	button->mTransform.pos = _pos;
	text->mTransform.pos = _pos;
	/*text->mTransform.pos.y += TXT_OFFSETY * text->mTransform.scale.y;*/
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
