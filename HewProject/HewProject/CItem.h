#pragma once
#include "CObject.h"
#include "CGridObject.h"
#include "CShadow.h"

constexpr float MAX_POS_X = 8.0f;
constexpr float MAX_POS_Y = 4.5f;
constexpr float BLOWOFF_TIME = 2.0f;

class CItem :
	public CGridObject
{
    float movement; // ふわふわ動かすときのs
    Vector3 drawPos;       // 描画する座標
    
    CShadow* shadow;
public:
    CItem(D3DBUFFER vb, D3DTEXTURE tex);
    ~CItem();

    virtual void Update();
    virtual void FloatingFluffy();  // ふわふわ浮く
    virtual void Draw();

    // アイテムの初期化
    void InitItem(D3DTEXTURE _shadowTex);

    // 影の設定する※アイテムの座標、大きさが入った後に呼び出す)
    void SetShadow(D3DTEXTURE _shadowTex);
};

