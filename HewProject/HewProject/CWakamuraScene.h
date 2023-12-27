#pragma once
#include "CScene.h"

class Ckcal_gauge;
class Player;

class CWakamuraScene :
    public CScene
{
public:
    D3DBUFFER playerBuffer;
    D3DTEXTURE playerTexture;

    D3DTEXTURE playerTexture1;

    Player* player;

    bool isChange = false;
    bool isGO = false;
    bool isFlashTime = false;

    ULONGLONG pushTime = 0;

    Ckcal_gauge* test;

    CWakamuraScene();

    ~CWakamuraScene();

    void Update() override;

    void LateUpdate() override;

    void Draw() override;
};

