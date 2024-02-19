#pragma once
#include "CScene.h"

class WorldSelectPic;
class CStageSelectPlayer;
class UI;
class ShadowUI;

class CStage1SelectScene :
    public CScene
{
public:

    bool isSceneChanging;   // �V�[���ς��

    bool c_isHitStage[5]; // ���ꂼ�ꓖ�����Ă邩���肷��
    bool o_isHitStage[5];  // �O�t���[���œ������Ă邩

    //�v���C���[
    D3DBUFFER playerBuffer;
    D3DTEXTURE playerTexture;
    D3DTEXTURE player_waitTexture;

    //�X�e�[�W
    D3DBUFFER stageBuffer;
    D3DTEXTURE stage1Texture;
    D3DTEXTURE stage2Texture;
    D3DTEXTURE stage3Texture;
    D3DTEXTURE stage4Texture;
    D3DTEXTURE shadowTexture;
    D3DTEXTURE backTexture;

    //�e�L�X�g
    D3DBUFFER textBuffer;
    D3DTEXTURE text_world1Texture;
    D3DTEXTURE text_world2Texture;
    D3DTEXTURE text_world3Texture;
    D3DTEXTURE text_world4Texture;

    //����
    D3DBUFFER wordBuffer;
    D3DTEXTURE word_RightUpTexture;
    D3DTEXTURE word_RightDownTexture;
    D3DTEXTURE word_LeftUpTexture;
    D3DTEXTURE word_LeftDownTexture;
    D3DTEXTURE world1Texture;
    D3DTEXTURE world2Texture;
    D3DTEXTURE world3Texture;
    D3DTEXTURE worldEXTexture;

    //����
    D3DBUFFER decisionBuffer;
    D3DTEXTURE decisionTexture;
    D3DTEXTURE B_ButtonTexture;

    D3DBUFFER decision_textboxBuffer;
    D3DTEXTURE decision_textbox1Texture;
    D3DTEXTURE decision_textbox2Texture;
    D3DTEXTURE decision_textbox3Texture;
    D3DTEXTURE decision_textbox4Texture;

    D3DBUFFER bgBuffer;
    D3DTEXTURE bgTexture;

    CStageSelectPlayer* player;
    WorldSelectPic* stage[5];
    UI* Text[4];
    UI* Word[8];
    UI* Bg;
    UI* World[4];
    UI* Num[4];
    UI* Decision[5];
    UI* Decision_textbox[5];
    ShadowUI* Shadow[4];
    UI* B_Button;

    bool isPlayerMoving;
    bool isOnce;
    bool isUpDown;
    bool isBigSmall;
    bool isOncePos;

public:
    CStage1SelectScene();
    ~CStage1SelectScene();

    void Update() override;

    void LateUpdate() override;

    void Draw() override;

};



