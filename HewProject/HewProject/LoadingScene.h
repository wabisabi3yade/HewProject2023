#pragma once
#include "CScene.h"
class LoadingScene :
    public CScene
{

public:
    void Update() override;
    void LateUpdate() override;
    void Draw() override;
};

