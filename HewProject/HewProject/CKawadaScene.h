#pragma once
#include "CScene.h"
class CKawadaScene :
    public CScene
{

public:
    CKawadaScene();

    ~CKawadaScene();

    void Update() override;

    void LateUpdate() override;

    void Draw() override;
};

