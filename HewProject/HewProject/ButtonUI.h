#pragma once
#include "UI.h"
#include <functional>

#define LIGHT_SCALEUPTIMES (1.2f)	// �n�C���C�g����UI�̑傫��
#define SCALEUP_TIME (1.0f)	// �傫���Ȃ�܂ł̑傫��

class ButtonUI
{
protected:
	UI* text = nullptr;
	UI* button = nullptr;

	// �{�^���������ꂽ�Ƃ��̊֐���
	std::function<void()> func = nullptr;

	// �D�F��Ԃ̂Ƃ��̑傫��
	Vector3 grayState_scale = Vector3::one;

	float textScaleTimes = 0.85f;	// �{�^����1.0�Ƃ������̃e�L�X�g�̔{��
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_buttonBuffer">�{�^���̃o�b�t�@</param>
	/// <param name="_buttonTex">�{�^���̃e�N�X�`��</param>
	/// <param name="_textBuffer">�e�L�X�g�̃o�b�t�@</param>
	/// <param name="_textTex">�e�L�X�g�̃e�N�X�`��</param>
	ButtonUI(D3DBUFFER _buttonBuffer, D3DTEXTURE _buttonTex,D3DBUFFER _textBuffer, D3DTEXTURE _textTex);
	virtual ~ButtonUI();

	virtual void Update();

	virtual void Draw();
	
	/// <summary>
	/// �{�^�����n�C���C�g�ɂ���i�I�΂ꂽ�{�^���j
	/// </summary>
	/// <param name="_isLight">�Ԃ����邩�ǂ���</param>
	virtual void SetHighlight(bool _isLight);

	virtual void SetScale(const Vector3& _scale);

	virtual void SetPosition(const Vector3& _scale);

	// �{�^���������ꂽ�Ƃ��ɍs��������ݒ�
	void SetFunc(std::function<void()> _setFunction);

	// �ݒ肵���֐������s
	void BeginFunc();
};

