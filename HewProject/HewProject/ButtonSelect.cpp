#include "ButtonSelect.h"
#include "ButtonUI.h"

ButtonSelect::ButtonSelect()
{
}

ButtonSelect::~ButtonSelect()
{
	buttonRegister.clear();
	buttonRegister.shrink_to_fit();
}

void ButtonSelect::FlagUpdate()
{
	o_isInput = c_isInput;
	c_isInput = false;
}

void ButtonSelect::ButtonMove(int _add)
{
	c_isInput = true;

	// ���͂��ꂽ�u��
	if ( !(c_isInput && !o_isInput) || !isActive) return;
	// �o�^���Ă���{�^���̐��ȏ���w�肷��ƏI������
	if (abs(_add) > buttonRegister.size()) return;

	// �ړ�����O�Ƀ{�^����ID����
	int o_buttonID = pointButtonID;
	// ����
	pointButtonID += _add;

	// �Ȃ�ł��m��񂯂�size()���Ƃ��������Ȃ�
	if (pointButtonID >= registCnt)
	{
		// �����
		pointButtonID -= buttonRegister.size();
	}
	// ����
	else if (pointButtonID < 0)
	{
		// ����
		pointButtonID = buttonRegister.size() + pointButtonID;
	}

	// �O�̃{�^���̃n�C���C�g�\�����~�߂�
	buttonRegister[o_buttonID]->SetHighlight(false);
	// �V�����w�肵���{�^�����n�C���C�g������
	buttonRegister[pointButtonID]->SetHighlight(true);
}

void ButtonSelect::PushButton()
{
	if (!isActive) return;
	buttonRegister[pointButtonID]->BeginFunc();
}

void ButtonSelect::Regist(ButtonUI* _registButton)
{
	buttonRegister.push_back(_registButton);
	registCnt++;
}
