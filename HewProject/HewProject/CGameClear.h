#pragma once
#include "CScene.h"

class UI;
class ButtonUI;
class ButtonSelect;
class CGameClearPlayer;
class CoinUI;

class CGameClear :
    public CScene
{

    CScene::SCENE_NAME nextScene;


public:
    D3DBUFFER bgBuffer;
    D3DTEXTURE bgTexture;

    D3DBUFFER textBuffer;
    D3DTEXTURE textTexture;

    D3DBUFFER frameBuffer;
    D3DTEXTURE frameTexture;

    D3DBUFFER namiBuffer;
    D3DTEXTURE namiTexture;

    D3DBUFFER textBoxBuffer;
    D3DTEXTURE textBoxTexture;

    D3DTEXTURE text_nextStageTexture;
    D3DTEXTURE text_stageSelectTexture;

    D3DBUFFER playerBuffer;
    D3DTEXTURE player_EatTexture;
    D3DTEXTURE player_WalkTexture;

    UI* Bg;
    ButtonSelect* selectControl;
    UI* Text[6];
    ButtonUI* Message[2];
    UI* Frame[2];
    UI* Nami[2];
    CGameClearPlayer* player;
    CoinUI* Coin;
    int nNumCoin;
    int nGetCoin;

    bool isNoMoving;
    bool isOnce;
    bool isFrame;
    bool isStopAnim;
    bool isCoin;

public:
    CGameClear(CScene::SCENE_NAME _nextScene, CoinUI* _coin = nullptr);

    ~CGameClear();
    
    void Update() override;

    void LateUpdate() override;

    void Draw() override;

    void SetFunc(int _num, std::function<void()> _onComplete);
};

