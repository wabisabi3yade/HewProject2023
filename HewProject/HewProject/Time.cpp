#include "Time.h"
float Time::deltaTime = 0;
float Time::slowTime = 0;

bool Time::isSlow = false;



void Time::Update()
{
	if (isSlow)
	{
		slowTime = 1.0f / 10;
	}
	else
	{
		slowTime = 1.0f;
	}
}
