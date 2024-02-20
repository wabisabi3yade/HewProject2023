#include "ControllerVibration.h"
ControllerVibration* ControllerVibration::instance = nullptr;

ControllerVibration::ControllerVibration()
{
}

ControllerVibration::~ControllerVibration()
{
}

ControllerVibration* ControllerVibration::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new ControllerVibration();
	}

	return instance;
}

void ControllerVibration::Delete()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

void ControllerVibration::Update()
{
	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
	vibration.wLeftMotorSpeed = leftPower; // use any value between 0-65535 here
	vibration.wRightMotorSpeed = rightPower; // use any value between 0-65535 here
	XInputSetState(NULL, &vibration);
}

void ControllerVibration::Shake(float _leftVibePower, float _rightVibePower, float _shakeTime)
{
	leftPower = _leftVibePower;
	rightPower = _rightVibePower;
}
