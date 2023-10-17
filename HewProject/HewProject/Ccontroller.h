#pragma once

#include <Windows.h>
#include <Xinput.h>
//#include <DirectXMath.h>

#pragma comment(lib, "XInput.lib")

class Ccontroller 
{
public:
    Ccontroller();  //コントラクタ
    ~Ccontroller(); //デストラクタ

    void Update();  // コントローラーの状態を更新

    //左スティックのX座標を取得
    float GetLeftStickX() const;
    //左スティックのY座標を取得
    float GetLeftStickY() const;

private:
    XINPUT_STATE m_controllerState; //コントローラーの状態を格納
};
