#pragma once

#include <Windows.h>
#include <Xinput.h>
//#include <DirectXMath.h>

#pragma comment(lib, "XInput.lib")

class Ccontroller 
{
public:
    Ccontroller();  //�R���g���N�^
    ~Ccontroller(); //�f�X�g���N�^

    void Update();  // �R���g���[���[�̏�Ԃ��X�V

    //���X�e�B�b�N��X���W���擾
    float GetLeftStickX() const;
    //���X�e�B�b�N��Y���W���擾
    float GetLeftStickY() const;

private:
    XINPUT_STATE m_controllerState; //�R���g���[���[�̏�Ԃ��i�[
};
