#pragma once
#include <vector>

class ButtonUI;

class ButtonSelect
{
	bool isActive = true;	// ���g���Ă��邩�ǂ���
	int pointButtonID = 0;	
	int registCnt = 0;	// �o�^����Ă���{�^���̐�

	std::vector<ButtonUI*> buttonRegister;	// ���䂷��{�^���̔z��

	bool c_isInput = false;
	bool o_isInput = false;
public:
	ButtonSelect();
	~ButtonSelect();

	// �g���K�[���͗p�̍X�V(ButtonMove�̑O�ɐ�Ώ���!!!)
	void FlagUpdate();

	/// <summary>
	/// �{�^�����ړ�������
	/// </summary>
	/// <param name="_add">�{�^���������ړ������邩�i�����Ƃ��̓}�C�i�X�̒l���w��j</param>
	void ButtonMove(int _add);


	// ���w�肵�Ă���{�^���̊֐������s
	void PushButton();

	/// <summary>
	/// �{�^����o�^����
	/// </summary>
	/// <param name="_registButton">�o�^�������{�^���̃A�h���X</param>
	void Regist(ButtonUI* _registButton);

	void SetActive(bool _set) { isActive = _set; }
	bool GetActive()const { return isActive; }
};

