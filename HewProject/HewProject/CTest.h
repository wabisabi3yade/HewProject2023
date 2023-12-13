#pragma once
#include "CScene.h"
#include <iostream>

class Player;

// �e�X�g�V�[��
class CTest :
    public CScene
{
    D3DBUFFER playerBuffer;
    D3DTEXTURE playerTexture;
    
   /* Player* player;*/

    std::shared_ptr<Player> player;
public:
    CTest();

    ~CTest();

    void Update() override;

    void LateUpdate() override;

    void Draw() override;

};

