#pragma once
#include "UI.h"

class ButtonUI
	: public UI
{

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="vb">�o�b�t�@{1,2}</param>
	/// <param name="tex">�e�N�X�`��</param>
	ButtonUI(D3DBUFFER vb, D3DTEXTURE tex);
	void Draw() override;
	~ButtonUI();

	/// <summary>
	/// �{�^�����n�C���C�g�ɂ���i�I�΂ꂽ�{�^���j
	/// </summary>
	/// <param name="_isLight"></param>
	void SetHighlight(bool _isLight);
};

