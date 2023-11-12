#pragma once
#include "CScene.h"
#include "Ccontroller.h"

class CPlayer : public CScene
{
public:
    D3DBUFFER charBuffer;
    D3DTEXTURE charTexture;
    CObject* charObj;

    float x, y; // �v���C���[�̍��W
    float speed; // �ړ����x

public:
    CPlayer(float startX, float startY, float speed);

    ~CPlayer();

    void Update() override;  // CScene �N���X�̏������z�֐����I�[�o�[���C�h
    void Render() /*override*/;  // CScene �N���X�̏������z�֐����I�[�o�[���C�h

    float GetX() const;
    float GetY() const;

    void HandleInput();
};




