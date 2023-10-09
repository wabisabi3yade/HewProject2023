#pragma once
#include "CScene.h"
class CMizunoScene :
    public CScene
{
public:
    CMizunoScene();

    ~CMizunoScene();

    void Update() override;

    void LateUpdate() override;

    void Draw() override;
};

