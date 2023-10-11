#pragma once
#include "CScene.h"
class CTatemizoScene :
    public CScene
{

public:
    CTatemizoScene();

    ~CTatemizoScene();

    void Update() override;

    void LateUpdate() override;

    void Draw() override;
};

