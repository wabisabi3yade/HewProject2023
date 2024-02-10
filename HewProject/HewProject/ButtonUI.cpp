#include "ButtonUI.h"
#define TXT_OFFSETY (0.2f)	// �{�^����肿�傢��

#define BTN_HORI_RATIO (4)	// �{�^���̉摜�c1�ɑ΂��ĉ��̔䗦
#define TXT_HORI_RATIO (8)	// �e�L�X�g�摜�c1�ɑ΂��ĉ��̔䗦

#define LIGHT_SCALEUPTIMES (1.5f)	// �n�C���C�g����UI�̑傫��
#define LIGHT_SCALEDOWNTIMES (1.3f)	// �n�C���C�g����UI�̑傫��

#define SCALEUP_TIME (1.0f)	// �傫���Ȃ�܂ł̑傫��

void ButtonUI::ScaleLoop(Vector3 _downScale, Vector3 _upScale)
{
	button->mTransform.scale = _downScale;
	button->dotween->DoEaseOutCubicScale(_upScale, SCALEUP_TIME);
	button->dotween->Append(_downScale, SCALEUP_TIME, DoTweenUI::FUNC::EASE_OUTCUBIC_SCALE);
	button->dotween->SetLoop(-1);

	text->mTransform.scale = _downScale * textScaleTimes;
	text->dotween->DoEaseOutCubicScale(_upScale * textScaleTimes, SCALEUP_TIME);
	text->dotween->Append(_downScale * textScaleTimes, SCALEUP_TIME, DoTweenUI::FUNC::EASE_OUTCUBIC_SCALE);
	text->dotween->SetLoop(-1);
}

ButtonUI::ButtonUI(D3DBUFFER _buttonBuffer, D3DTEXTURE _buttonTex, D3DBUFFER _textBuffer, D3DTEXTURE _textTex)
{
	button = new UI(_buttonBuffer, _buttonTex);
	button->MakeDotween();
	text = new UI(_textBuffer, _textTex);
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
}

void ButtonUI::SetHighlight(bool _isLight)
{
	float v = 0.0f;
	//  2�����̉��Ȃ̂�
	if (_isLight)
	{
		v = 0.5f;
		// �g��̃X�P�[��
		Vector3 upScale = grayState_scale * LIGHT_SCALEUPTIMES;
		upScale.z = 1.0f;
		// �g��̃X�P�[��
		Vector3 downScale = grayState_scale * LIGHT_SCALEDOWNTIMES;
		upScale.z = 1.0f;

		ScaleLoop(downScale, upScale);
	}
	if (_isLight)
	{
		button->dotween->Stop();
		button->mTransform.scale = grayState_scale;
	}

	button->SetUV(0.0f, v);	
}

void ButtonUI::SetScale(const Vector3& _scale)
{
	// �D�F��Ԃ̑傫���Ƃ��đ������
	grayState_scale = _scale;
	grayState_scale.z = 1.0f;

	// ��4 �c1
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

void ButtonUI::BeginFunc()
{
	if (func == nullptr) return;
	func();
}
