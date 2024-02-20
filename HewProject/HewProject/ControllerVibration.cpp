#include "ControllerVibration.h"
ControllerVibration* ControllerVibration::instance = nullptr;

ControllerVibration::ControllerVibration()
{
	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
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
	if (isShaking)
	{
		elapsedTime += 1.0f / 60;
		vibration.wLeftMotorSpeed = leftPower; // use any value between 0-65535 here
		vibration.wRightMotorSpeed = rightPower; // use any value between 0-65535 here
		XInputSetState(NULL, &vibration);

		if (elapsedTime > shakeTime)
		{
			isShaking = false;
			vibration.wLeftMotorSpeed = 0; // use any value between 0-65535 here
			vibration.wRightMotorSpeed = 0; // use any value between 0-65535 here
			XInputSetState(NULL, &vibration);
		}
	}
}

void ControllerVibration::Shake(float _leftVibePower, float _rightVibePower, float _shakeTime)
{
	leftPower = _leftVibePower;
	rightPower = _rightVibePower;

	elapsedTime = 0.0f;
	shakeTime = _shakeTime;

	isShaking = true;
}
