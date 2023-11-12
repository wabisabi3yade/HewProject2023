#pragma once
#include "CScene.h"
#include "Ccontroller.h"
#include "CPlayer.h"

class CTatemizoScene :
    public CScene
{
public:
    CTatemizoScene();

    ~CTatemizoScene();

    void Update() override;

    void LateUpdate() override;

    void Draw() override;

private:
    CPlayer* player;  // CPlayer クラスのポインタをメンバーとして持つ
};

