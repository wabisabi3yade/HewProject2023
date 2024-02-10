#pragma once
#include "CScene.h"
#include <vector>
#include "StgButton.h"
#include "ButtonSelect.h"
//class ButtonSelect;

class StageSelect :
    public CScene
{

protected:
    bool isChangeNumTriger = false; // �������ς�����u��

    short stageNum = 0; // �X�e�[�W�̐�
    
    short pointStage = 1;   // �I��ł���X�e�[�W�̐�

    D3DTEXTURE stageBtnTex; // �X�e�[�W�̃{�^���̃e�N�X�`��
    D3DBUFFER stageBtnBuf;  // �X�e�[�W�̃{�^���̃o�b�t�@
    D3DTEXTURE numberTex;
    D3DBUFFER numberBuf;
    std::vector<StgButton*> stgButton;  // �X�e�[�W�{�^��
    ButtonSelect* btnSelect; 

    D3DBUFFER oneBuf;   // {1,1}

    D3DTEXTURE stageSmpBackTex; // �T���v���̔w�i�̃e�N�X�`��
    UI* stageSmpBack;   
    std::vector<D3DTEXTURE> stageSmpTex;    // �X�e�[�W�̃T���v���e�N�X�`��


    D3DTEXTURE Back;    // �w�i
    D3DTEXTURE WorldBack;   // ���[���h�̔w�i
    D3DTEXTURE WorldNum;    // ���[���h�Z
    D3DTEXTURE WorkdName;   // ���[���h��

    void Input();

public:
    StageSelect();

    virtual void Update();

    void LateUpdate() override;

    virtual void Draw();

    virtual ~StageSelect();
};

