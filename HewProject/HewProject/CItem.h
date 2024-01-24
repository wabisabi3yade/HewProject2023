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
    float movement; // �ӂ�ӂ퓮�����Ƃ���s
    Vector3 drawPos;       // �`�悷����W
    
    CShadow* shadow;
public:
    CItem(D3DBUFFER vb, D3DTEXTURE tex);
    ~CItem();

    virtual void Update();
    virtual void FloatingFluffy();  // �ӂ�ӂ핂��
    virtual void Draw();

    // �A�C�e���̏�����
    void InitItem(D3DTEXTURE _shadowTex);

    // �e�̐ݒ肷�遦�A�C�e���̍��W�A�傫������������ɌĂяo��)
    void SetShadow(D3DTEXTURE _shadowTex);
};

