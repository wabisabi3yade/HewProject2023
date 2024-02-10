#pragma once
#include "ButtonUI.h"
class StgButton
	: public ButtonUI
{
	void ScaleLoop(Vector3 _downScale, Vector3 _upScale) override;

public:
	StgButton(D3DBUFFER _buttonBuffer, D3DTEXTURE _buttonTex, D3DBUFFER _textBuffer, D3DTEXTURE _textTex);

	~StgButton();

	void Update() override;

	void Draw() override;

	/// <summary>
	/// �{�^�����n�C���C�g�ɂ���i�I�΂ꂽ�{�^���j
	/// </summary>
	/// <param name="_isLight">�Ԃ����邩�ǂ���</param>
	void SetHighlight(bool _isLight) override;

	void SetScale(const Vector3& _scale) override;

	void SetPosition(const Vector3& _pos) override;

	// �{�^���������ꂽ�Ƃ��ɍs��������ݒ�
	void SetFunc(std::function<void()> _setFunction);

	// �ݒ肵���֐������s
	void BeginFunc();

	// ������ݒ�
	void SetNum(short num);
};

