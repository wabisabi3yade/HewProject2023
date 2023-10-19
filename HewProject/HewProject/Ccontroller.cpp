#include "Ccontroller.h"

Ccontroller::Ccontroller() 
{
    //�R���g���[���[�̏�Ԃ�������
    ZeroMemory(&m_controllerState, sizeof(XINPUT_STATE));
}

Ccontroller::~Ccontroller() 
{
    //��������͕s�v
}

void Ccontroller::Update() 
{
    //�R���g���[���[�̏�Ԃ��X�V����
    DWORD result = XInputGetState(0, &m_controllerState);

    if (result != ERROR_SUCCESS) 
    {
        //�R���g���[���[���ڑ�����Ă��Ȃ����A�G���[�����������ꍇ�A��Ԃ��N���A����
        ZeroMemory(&m_controllerState, sizeof(XINPUT_STATE));
    }
}

float Ccontroller::GetLeftStickX() const 
{
    //���X�e�B�b�N��X���W��-1.0����1.0�͈̔͂ɐ��K�����ĕԂ�
    return m_controllerState.Gamepad.sThumbLX / 32767.0f;
}

float Ccontroller::GetLeftStickY() const 
{
    //���X�e�B�b�N��Y���W��-1.0����1.0�͈̔͂ɐ��K�����ĕԂ�
    return m_controllerState.Gamepad.sThumbLY / 32767.0f;
}
