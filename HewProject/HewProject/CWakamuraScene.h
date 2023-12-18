#pragma once
#include "CScene.h"

class Ckcal_gauge;

class CWakamuraScene :
    public CScene
{
public:

    Ckcal_gauge* test;

    CWakamuraScene();

    ~CWakamuraScene();

    void Update() override;

    void LateUpdate() override;

    void Draw() override;
};

