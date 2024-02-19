#include "ButtonSelect.h"
#include "xa2.h"

#define PUSH_SCALETINE (0.5f)
#define CANT_SELECT_TIME (1.0f)

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

	if (!isSlecting)
	{
		static float elapsedTime = 0.0f;

		elapsedTime += 1.0f / 60;

		if (elapsedTime > CANT_SELECT_TIME)
		{
			isSlecting = true;
		}
	}
}

void ButtonSelect::ButtonMove(int _add)
{

	if (!isSlecting) return;
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

	XA_Play(SOUND_LABEL::S_MOVEBUTTON);

	// �O�̃{�^���̃n�C���C�g�\�����~�߂�
	buttonRegister[o_buttonID]->SetHighlight(false);

	// �V�����w�肵���{�^�����n�C���C�g������
	buttonRegister[pointButtonID]->SetHighlight(true);
}

void ButtonSelect::SetButtonID(int _id)
{
	int o_point = pointButtonID;

	if (_id >= buttonRegister.size())
	{
		_id = buttonRegister.size() - 1;
	}
	else if (_id < 0)
	{
		_id = 0;
	}

	pointButtonID = _id;

	// �O�̃{�^���̃n�C���C�g�\�����~�߂�
	buttonRegister[o_point]->SetHighlight(false);

	// �V�����w�肵���{�^�����n�C���C�g������
	buttonRegister[pointButtonID]->SetHighlight(true);

}

void ButtonSelect::PushButton(bool _isFlash)
{
	if (!isActive) return;
	isSlecting = false;
	buttonRegister[pointButtonID]->BeginFunc();
	if (_isFlash)
	{
		buttonRegister[pointButtonID]->SetFlash();
	}
}

void ButtonSelect::Regist(ButtonUI* _registButton)
{
	buttonRegister.push_back(_registButton);
	registCnt++;
}
