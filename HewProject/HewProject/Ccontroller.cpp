#include "Ccontroller.h"

Ccontroller::Ccontroller() 
{
    //コントローラーの状態を初期化
    ZeroMemory(&m_controllerState, sizeof(XINPUT_STATE));
}

Ccontroller::~Ccontroller() 
{
    //解放処理は不要
}

void Ccontroller::Update() 
{
    //コントローラーの状態を更新する
    DWORD result = XInputGetState(0, &m_controllerState);

    if (result != ERROR_SUCCESS) 
    {
        //コントローラーが接続されていないか、エラーが発生した場合、状態をクリアする
        ZeroMemory(&m_controllerState, sizeof(XINPUT_STATE));
    }
}

float Ccontroller::GetLeftStickX() const 
{
    //左スティックのX座標を-1.0から1.0の範囲に正規化して返す
    return m_controllerState.Gamepad.sThumbLX / 32767.0f;
}

float Ccontroller::GetLeftStickY() const 
{
    //左スティックのY座標を-1.0から1.0の範囲に正規化して返す
    return m_controllerState.Gamepad.sThumbLY / 32767.0f;
}
