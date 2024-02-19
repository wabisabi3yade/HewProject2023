#pragma once
#include "CGridObject.h"
#include "DoTween.h"
class CEffect;

#define CASTELLAWALK_TIME (1.65f)	// �J�X�e���������Ƃ��̈ړ����x
#define CASTELLAFALL_TIME (1.1f)	// �J�X�e����������܂ł̑ҋ@����

class CCastella :
    public CGridObject
{
    std::unique_ptr<DoTween> dotween;
    CEffect* effect;
public:
    CCastella(D3DBUFFER vb, D3DTEXTURE tex);
    ~CCastella();
    void Update();
    /// <summary>
    /// �J�X�e���𓮂���
    /// </summary>
    /// <param name="_pos">������̃��[���h���W</param>
    /// <param name="isFall">������̂��ǂ���</param>
    /// <param name="_fallPos">��������W</param>
    void Move(Vector3 _pos, int _dir, Vector3 _fallPos = Vector3::zero);
    void Draw();
};

