#include "ButtonUI.h"
#define UI_OFFSETZ (0.0001f)

#define TXT_OFFSETY (0.2f)	// �{�^����肿�傢��

#define BTN_HORI_RATIO (4)	// �{�^���̉摜�c1�ɑ΂��ĉ��̔䗦
#define TXT_HORI_RATIO (8)	// �e�L�X�g�摜�c1�ɑ΂��ĉ��̔䗦

ButtonUI::ButtonUI(D3DBUFFER _buttonBuffer, D3DTEXTURE _buttonTex, D3DBUFFER _textBuffer, D3DTEXTURE _textTex)
{
	button = new UI(_buttonBuffer, _buttonTex);
	text = new UI(_textBuffer, _textTex);
	
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
	}

	button->SetUV(0.0f, v);
}

void ButtonUI::SetScale(const Vector3& _scale)
{
	// ��4 �c1
	button->mTransform.scale = { _scale.x , _scale.y / BTN_HORI_RATIO, 1.0f };

	const float textScaleTimes = 0.85f;	// �{�^����1.0�Ƃ������̃e�L�X�g�̔{��
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
