#include "Time.h"
float Time::deltaTime = 0;
float Time::slowTime = 0;

bool Time::isSlow = false;



void Time::Update()
{
	if (isSlow)
	{
		slowTime = deltaTime / 10;
	}
	else
	{
		slowTime = deltaTime;
	}
}
