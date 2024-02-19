#pragma once
#include "CScene.h"
#include <vector>
#include "StgButton.h"
#include "ButtonSelect.h"

#define UI_POSZ (0.8f)
#define BTN_OFFSETX (1.2f)	// �{�^�����Ƃ̍����iX���W�j
#define BEGIN_MOVETIME (1.0f)   // �n�߂̈ړ�����
#define BEGIN_MOVEMENT_X (7.5f) // ���߂̈ړ���

#define WORLDNAME_OFFSETY (1.5f)	// y���̍����l

#define SIN_POWER (0.12f)
#define SIN_SPEED (1.0f)

class StageSelect :
    public CScene
{

protected:
    float sinRot = 0.0f;

    bool isBeginFin = false;

    bool isChangeNumTriger = false; // �������ς�����u��

    bool isSceneMoving = false;   // �V�[���ς���Ă���Œ���

    bool isMove = false;

    short stageNum; // �X�e�[�W�̐�
  
    short c_pointStage = 1;   // �I��ł���X�e�[�W�̐�
    short o_pointStage;

    Vector3 btnScale = { 1.5f, 1.5f, 1.0f };
    Vector3 firstBtnPos = { -7.0f, -2.0f, UI_POSZ };

    D3DTEXTURE stageBtnTex; // �X�e�[�W�̃{�^���̃e�N�X�`��
    D3DBUFFER stageBtnBuf;  // �X�e�[�W�̃{�^���̃o�b�t�@
    D3DTEXTURE numberTex;
    D3DBUFFER numberBuf;
    std::vector<StgButton*> stgButton;  // �X�e�[�W�{�^��
    ButtonSelect* btnSelect; 

    D3DBUFFER oneBuf;   // {1,1}

    D3DTEXTURE stageSmpBackTex; // �T���v���̔w�i�̃e�N�X�`��
    UI* stageSmpBack;   
    Vector3 stageSmpPos;

    UI* smp;
    std::vector<D3DTEXTURE> stageSmpTex;    // �X�e�[�W�̃T���v���e�N�X�`��


    D3DTEXTURE backTex;    // �w�i
    UI* backGround[3];

    // A�{�^��
    D3DTEXTURE startTex;
    UI* startUI;

    // B�{�^��
    D3DTEXTURE backButtonTex;
    UI* backUI;

    D3DTEXTURE stageTex;
    UI* stageText;
    Vector3 stageTextPos;
    UI* stageTextBack;


    D3DTEXTURE worldTextTex;   // ���[���h�̔w�i
    UI* worldText;  // World
    Vector3 worldTextPos;

    UI* worldNum;   // ����

    D3DTEXTURE worldNameTex;   // ���[���h��
    D3DBUFFER worldNameBuffer;
    UI* worldName[2];   // ���[���h��
    Vector3 worldNamePos;
    float worldNameOffsetX;

    D3DTEXTURE btnNumTex;   // �{�^���p�e�N�X�`��


    virtual void Input();

    void SmpMove(); // �T���v���̈ړ��֐�

    virtual void BeginMove();   // �ŏ��̓���

public: 
    StageSelect();

    virtual void Update();

    void LateUpdate() override;

    virtual void Draw();

    virtual ~StageSelect();
};

