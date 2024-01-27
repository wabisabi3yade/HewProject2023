#include "InputStateUpdate.h"
#include "CInput.h"

InputStateUpdate* InputStateUpdate::instance = nullptr;

InputStateUpdate::InputStateUpdate()
{
	controller = GameController::GetInstance();

	for (int i = 0; i < static_cast<int>(TYPE::NUM); i++)
	{
		// ��Ɨp�ϐ�
		int keyWork = 0;	
		WORD controllerWork = 0;

		// �e�{�^���^�C�v�ɑΉ������L�[�ƃR���g���[���[�����肷��
		switch (static_cast<TYPE>(i))
		{
		case TYPE::DECIDE:
			keyWork = VK_SPACE;
			controllerWork = XINPUT_GAMEPAD_A;
			break;

		case TYPE::CANCEL:
			keyWork = VK_BACK;
			controllerWork = XINPUT_GAMEPAD_B;
			break;

		case TYPE::OPTION:
			keyWork = VK_ESCAPE;
			controllerWork = XINPUT_GAMEPAD_START;
			break;

		case TYPE::CAMERA:
			keyWork = VK_CONTROL;
			controllerWork = XINPUT_GAMEPAD_Y;
			break;

		case TYPE::L_BUTTON:
			keyWork = VK_F11;
			controllerWork = XINPUT_GAMEPAD_LEFT_SHOULDER;
			break;

		case TYPE::R_BUTTON:
			keyWork = VK_F12;
			controllerWork = XINPUT_GAMEPAD_RIGHT_SHOULDER;
			break;

		default:
			MessageBoxA(NULL, "�Ή��ł��Ă��Ȃ��{�^���^�C�v������܂�", "�G���[", MB_ICONERROR | MB_OK);
			break;
		}

		// �Ή������L�[��������
		cInput_Support[i] = keyWork;
		contoroller_Support[i] = controllerWork;
	}
}

InputStateUpdate::~InputStateUpdate()
{
}

InputStateUpdate* InputStateUpdate::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new InputStateUpdate();
	}

	return instance;
}

void InputStateUpdate::Delete()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

void InputStateUpdate::UpdateKeyState()
{	
	// �O�t���[���̏�Ԃ��X�V����
	// �w��o�C�g�������������R�s�[����֐�
	memcpy_s(o_InputState, sizeof(o_InputState), c_InputState, sizeof(c_InputState));
	for (int i = 0; i < typeNum; i++)
		o_InputState[i] = c_InputState[i];

	// ���t���[���̏�Ԃ��X�V����
	// �{�^���^�C�v�̐�����
	for (int i = 0; i < typeNum; i++)
	{
		// �ŏ��Ƀt���O���~�낷
		c_InputState[i] = false;
		// �L�[�{�[�h�A�R���g���[���[�ǂ��炩���Ή������{�^����������Ă�����
		if (gInput->GetKeyPress(cInput_Support[i]) == true ||
			controller->Button(contoroller_Support[i]) == true)
		{
			// �t���O�𗧂Ă�
			c_InputState[i] = true;
		}
	}
}

bool InputStateUpdate::GetInputPress(TYPE _buttonType)
{
	return c_InputState[static_cast<int>(_buttonType)];
}

bool InputStateUpdate::GetInputTrigger(TYPE _buttonType)
{
	// �O�t���[����������Ă��Ȃ��@���@���t���[���ŉ�����Ă���
	return !o_InputState[static_cast<int>(_buttonType)] && 
		c_InputState[static_cast<int>(_buttonType)];
}

