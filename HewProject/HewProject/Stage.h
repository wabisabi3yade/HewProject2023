#pragma once
#include "CScene.h"
#include "StageScene.h"
#include "DebugTable.h"
#include<iostream>
#include "Tutorial.h"
class Stage :
    public CScene
{
    DebugTable* dbgFloorTable; // �e�X�g�p
    DebugTable* dbgObjTable; // �e�X�g�p

protected:
    short stageNum;

    // �X�e�[�W��UI�Ƃ�
    StageScene* stage; // �X�e�[�W�S�̂̃I�u�W�F�N�g
    // csv�t�@�C���̖��O
    const wchar_t* csvPath;

    D3DTEXTURE backTex[4];

    D3DBUFFER backBuffer;

    CObject* back;

    CScene::SCENE_NAME nextStage;

    Tutorial* tutorial = nullptr;
    D3DTEXTURE tutolialTex = NULL;
public:

    Stage();

    /// <summary>
    /// �X�e�[�W�V�[���̃R���X�g���N�^
    /// </summary>
    /// <param name="_csvPath">CSV�t�@�C���̃p�X</param>
    Stage(const wchar_t* _csvPath, short int worldNum, CScene::SCENE_NAME _next);


    void Init();

    virtual void Update();
    virtual void LateUpdate();
    virtual void Draw();

    virtual ~Stage();
};

