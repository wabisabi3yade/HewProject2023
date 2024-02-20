#pragma once

#include <Windows.h>
#include <Xinput.h>
class ControllerVibration
{
	XINPUT_VIBRATION vibration;

	ControllerVibration();
	~ControllerVibration();

	static ControllerVibration* instance;

	float leftPower = 0.0f;
	float rightPower = 0.0f;
public:

	static ControllerVibration* GetInstance();
	static void Delete();
	void Update();

	void Shake(float _leftVibePower, float _rightVibePower, float _shakeTime);
};

