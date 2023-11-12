#pragma once
#include "CScene.h"
#include "Ccontroller.h"

class CPlayer : public CScene
{
public:
    D3DBUFFER charBuffer;
    D3DTEXTURE charTexture;
    CObject* charObj;

    float x, y; // プレイヤーの座標
    float speed; // 移動速度

public:
    CPlayer(float startX, float startY, float speed);

    ~CPlayer();

    void Update() override;  // CScene クラスの純粋仮想関数をオーバーライド
    void Render() /*override*/;  // CScene クラスの純粋仮想関数をオーバーライド

    float GetX() const;
    float GetY() const;

    void HandleInput();
};




