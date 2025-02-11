#pragma once
#include "CGridObject.h"
#include "DoTween.h"

#define CASTELLAWALK_TIME (2.0f)	// カステラを押すときの移動速度
#define CASTELLAFALL_TIME (2.0f)	// カステラが落ちるまでの待機時間

class CCastella :
    public CGridObject
{
    std::unique_ptr<DoTween> dotween;

public:
    CCastella(D3DBUFFER vb, D3DTEXTURE tex);
    ~CCastella();
    void Update();
    /// <summary>
    /// カステラを動かす
    /// </summary>
    /// <param name="_pos">動く先のワールド座標</param>
    /// <param name="isFall">落ちるのかどうか</param>
    /// <param name="_fallPos">落ちる座標</param>
    void Move(Vector3 _pos, int _dir, Vector3 _fallPos = Vector3::zero);
    void Draw();
};

