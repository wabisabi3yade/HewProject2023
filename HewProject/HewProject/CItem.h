#pragma once
#include "CObject.h"
#include "CGridObject.h"
#include "CShadow.h"



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

