#include "CPlayer.h"

// コンストラクタ
CPlayer::CPlayer(float startX, float startY, float speed) : x(startX), y(startY), speed(speed), charObj(nullptr) {}

// 入力と移動を処理するアップデート関数
void CPlayer::Update()
{

    // 入力に基づいてプレイヤーを移動
    x += Input::GetHorizontal() * speed;
    y += Input::GetVertical() * speed;

}

// プレイヤーを描画するレンダリング関数
void CPlayer::Render()
{
    D3D_CreateSquare({ 3,4 }, &charBuffer);
    D3D_LoadTexture(L"asset/hashimoto/char01.png", &charTexture);

    charObj = new CObject(charBuffer, charTexture);
    charObj->mTransform.scale = { 3.0f,3.0f,1.0f };
}

CPlayer::~CPlayer()
{
    CLASS_DELETE(charObj);

    SAFE_RELEASE(charBuffer);

    SAFE_RELEASE(charTexture);
}

// X座標を取得する関数
float CPlayer::GetX() const
{
    return x;
}

// Y座標を取得する関数
float CPlayer::GetY() const
{
    return y;
}

// プレイヤー入力を処理する関数
void CPlayer::HandleInput()
{
    // ボタンの処理は省略し、左右の移動だけを考慮する

    // 左スティックが水平方向に動いた場合、水平方向にプレイヤーを移動
    float horizontalInput = Input::GetHorizontal();
    x += horizontalInput * speed;

    // 右スティックが垂直方向に動いた場合、垂直方向にプレイヤーを移動
    float verticalInput = Input::GetVertical();
    y += verticalInput * speed;
}