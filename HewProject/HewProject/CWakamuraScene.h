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

    Player* player;

    Ckcal_gauge* test;

    CWakamuraScene();

    ~CWakamuraScene();

    void Update() override;

    void LateUpdate() override;

    void Draw() override;
};

