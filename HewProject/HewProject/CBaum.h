#pragma once
#include "CGridObject.h"

#define BAUM_THROWMIDTIME (0.66f)   // バウムクーヘンの途中でZ値調整するときに必要
#define BAUM_THROWENDTIME (1.33f)   // バウムクーヘン通り抜ける時間

class CBaum :
    public CGridObject
{

public:
    CBaum(D3DBUFFER vb ,D3DTEXTURE tex);
    ~CBaum();

    void Update();
    void Draw();
    /// <summary>
    /// 
    /// </summary>
    /// <param name="_dir"> 
    /// 移動方向 int
    /// </param>
    /// <param name="_vb">
    /// アニメーション用のバッファー D3DBUFFER
    /// </param>
    void PlayAnim(int _dir, D3DBUFFER _vb);
};

