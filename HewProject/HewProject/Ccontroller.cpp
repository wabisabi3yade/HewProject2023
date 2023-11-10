#include "Ccontroller.h"

//�ÓI�ϐ�
XINPUT_STATE Input::ControllerState;//�R���g���[���[�̏��

//������
void Input::Init() {}

//setter
//���ɂȂ��I

//getter
bool Input::GetControllerDown(int _button) { return(ControllerState.Gamepad.wButtons & _button); }	//�{�^���������ꂽ���Ԃ�
bool Input::GetController(int _button) { return(ControllerState.Gamepad.wButtons & _button); }		//�{�^����������Ă��邩�Ԃ�
bool Input::GetControllerUp(int _button) { return !(ControllerState.Gamepad.wButtons & _button); }	//�{�^���������ꂽ���Ԃ�

//�X�e�B�b�N�̓���
//����0or1��L,R�𔻒�
bool Input::GetControllerStick(int _stick)
{
	int Value=0;
	float x = 0, y = 0;


	switch (_stick)
	{
		//������0�Ȃ獶�X�e�B�b�N
	case 0:
		x = ControllerState.Gamepad.sThumbLX;	//���X�e�B�b�N��X��
		y = ControllerState.Gamepad.sThumbLY;	//���X�e�B�b�N��Y��
		break;
		//������1�Ȃ�E�X�e�B�b�N
	case 1:
		x = ControllerState.Gamepad.sThumbRX;	//�E�X�e�B�b�N��X��
		y = ControllerState.Gamepad.sThumbRY;	//�E�X�e�B�b�N��Y��
		break;
	};
	return Value; (x, y) / 32768;	//XInput��65535�i�K(-32768�`327768)int�^
}


//trigger�̓���
//����0or1��L,R�𔻒�
//�R���g���[���̃g���K�[�̒l��Ԃ��֐�
float Input::GetControllerTrigger(int _trigger)
{
	float val = 0;
	switch (_trigger)
	{
	//������0�Ȃ獶�g���K�[
	case 0:
		val = (float)(ControllerState.Gamepad.bLeftTrigger) / 255;
		break;
	//������1�Ȃ�E�g���K�[
	case 1:
		val = (float)(ControllerState.Gamepad.bRightTrigger) / 255;
		break;
	}
	return val;		//XInput�̃g���K�[���͂�int�^��255�i�K(0�`255)
}

//�c����
float Input::GetVertical()
{
	float ControllerVal = GetControllerStick(0), y;	//�X�e�B�b�N��Y���̒l

	if (ControllerVal != 0)
	{
		return ControllerVal;
	}
}

//������
float Input::GetHorizontal()
{
	float ControllerVal = GetControllerStick(0), x;	//�X�e�B�b�N��X���̒l
	if (ControllerVal != 0)
	{
		return ControllerVal;
	}
}

//����
bool Input::GetDecisionDown()
{
	if (GetController(Pad_X)) { return true; }	//A�������ꂽ��true��Ԃ�
	return false;
}

//�L�����Z��
bool Input::GetCancelDown()
{
	if (GetController(Pad_B)) { return true; }	//B�������ꂽ��true��Ԃ�
	return false;
}

//�W�����v
bool Input::GetJumpDown()
{
	if (GetController(Pad_A)) { return true; }
	return false;
}

//�U��
bool Input::GetAttackDown()
{
	if (GetController(Pad_Y)) { return true; }
	return false;
}

//XInput�̏�Ԃ��擾���A�l���i�[
void Input::Update() 
{
	XInputGetState(0, &ControllerState);
}