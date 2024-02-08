#pragma once
#include "UI.h"
#include <functional>

class ButtonUI
{
	UI* text = nullptr;
	UI* button = nullptr;

	// �{�^���������ꂽ�Ƃ��̊֐���
	std::function<void()> func = nullptr;
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_buttonBuffer">�{�^���̃o�b�t�@</param>
	/// <param name="_buttonTex">�{�^���̃e�N�X�`��</param>
	/// <param name="_textBuffer">�e�L�X�g�̃o�b�t�@</param>
	/// <param name="_textTex">�e�L�X�g�̃e�N�X�`��</param>
	ButtonUI(D3DBUFFER _buttonBuffer, D3DTEXTURE _buttonTex,D3DBUFFER _textBuffer, D3DTEXTURE _textTex);
	~ButtonUI();

	void Update();

	void Draw();
	
	/// <summary>
	/// �{�^�����n�C���C�g�ɂ���i�I�΂ꂽ�{�^���j
	/// </summary>
	/// <param name="_isLight">�Ԃ����邩�ǂ���</param>
	void SetHighlight(bool _isLight);

	void SetScale(const Vector3& _scale);

	void SetPosition(const Vector3& _scale);

	// �{�^���������ꂽ�Ƃ��ɍs��������ݒ�
	void SetFunc(std::function<void()> _setFunction);

	// �ݒ肵���֐������s
	void BeginFunc();
};

