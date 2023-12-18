#include "COperation.h"

void COperation::Update()
{
    // 操作で設定する用のベクトル変数
    Vector3 d;

    // 方向なしベクトルに設定
    d.x = 0;
    d.y = 0;
    d.z = 0;

    // 移動速度を初めに０にする
    moveSpeed = 0.0f;

    dir = { 0,0,0 };

    // キー操作で移動
    // キーが現在押されてるかを判定する　＝　キープレス
    if (gInput->GetKeyPress(VK_DOWN))
    {
        dir.y = -1;
        d.y = -1;// 下方向ベクトル
        moveSpeed = 0.01f;
    }
    if (gInput->GetKeyPress(VK_LEFT))
    {
        dir.x = -1;
        d.x = -1;// 左方向ベクトル
        moveSpeed = 0.01f;
    }
    if (gInput->GetKeyPress(VK_RIGHT))
    {
        dir.x = +1;
        d.x = 1;//右方向ベクトル
        moveSpeed = 0.01f;
    }
    if (gInput->GetKeyPress(VK_UP))
    {
        dir.y = +1;
        d.y = 1;// 上方向ベクトル
        moveSpeed = 0.01f;
    }

    charObj->SetDir(dir);

    charObj->Update();
}

void COperation::Draw()
{
}


