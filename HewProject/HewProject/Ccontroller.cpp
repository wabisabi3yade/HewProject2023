#include "Ccontroller.h"
#include <Windows.h>
#include <Xinput.h>

XINPUT_STATE controllerState;
DWORD result = XInputGetState(0, &controllerState);

if (result != ERROR_SUCCESS) {}