#pragma once
#include "CGridObject.h"
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
    /// �ړ����� int
    /// </param>
    /// <param name="_vb">
    /// �A�j���[�V�����p�̃o�b�t�@�[ D3DBUFFER
    /// </param>
    void PlayAnim(int _dir, D3DBUFFER _vb);
};

