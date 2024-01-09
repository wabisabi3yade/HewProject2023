#pragma once
#include "CScene.h"

class EffectManeger;

class CKawadaScene :
    public CScene
{
    EffectManeger* FXinstance;
    
    int test;

public:
    CKawadaScene();

    ~CKawadaScene();

    void Update() override;

    void LateUpdate() override;

    void Draw() override;
};

