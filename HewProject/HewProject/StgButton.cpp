#include "StgButton.h"
#define UI_OFFSETZ (0.0001f)

StgButton::StgButton(D3DBUFFER _buttonBuffer, D3DTEXTURE _buttonTex, D3DBUFFER _textBuffer, D3DTEXTURE _textTex)
	: ButtonUI(_buttonBuffer, _buttonTex, _textBuffer, _textTex)
{

	SetPosition(Vector3::zero);
	SetScale(Vector3::one);
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
		button->dotween->DoEaseOutBackScale(upScale, SCALEUP_TIME);
		button->dotween->Append(grayState_scale, SCALEUP_TIME, DoTweenUI::FUNC::EASE_OUTBACK_SCALE);
		button->dotween->SetLoop(-1);
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
