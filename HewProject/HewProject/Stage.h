#pragma once
#include "CScene.h"
#include "StageScene.h"
#include "DebugTable.h"

class Ckcal_gauge;

class Stage :
    public CScene
{
    // �X�e�[�W��UI�Ƃ�
    StageScene* stage; // �X�e�[�W�S�̂̃I�u�W�F�N�g

    Ckcal_gauge* gauge; // �J�����[�Q�[�W

    DebugTable* dbgFloorTable; // �e�X�g�p
    DebugTable* dbgObjTable; // �e�X�g�p


public:
    /// <summary>
    /// �X�e�[�W�V�[���̃R���X�g���N�^
    /// </summary>
    /// <param name="_csvPath">CSV�t�@�C���̃p�X</param>
    Stage(const wchar_t* _csvPath);
    void Update()override;
    void LateUpdate()override;
    void Draw()override;

    ~Stage();
};

