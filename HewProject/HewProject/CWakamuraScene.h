#pragma once
#include "CScene.h"
class CWakamuraScene :
    public CScene
{
public:
    CWakamuraScene();

    ~CWakamuraScene();

    void Update() override;

    void LateUpdate() override;

    void Draw() override;
};

