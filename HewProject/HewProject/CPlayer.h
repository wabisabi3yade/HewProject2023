#pragma once
#include "CScene.h"
#include "Ccontroller.h"
#include "CObject.h"

class CPlayer : public CObject
{
public:
    //D3DBUFFER charBuffer;
    //D3DTEXTURE charTexture;
    //CObject* charObj;

    float x, y; // �v���C���[�̍��W
    float speed; // �ړ����x

public:
 
    CPlayer(D3DBUFFER vb, D3DTEXTURE tex);
    ~CPlayer();

    void Init(float startX, float startY, float speed);

    void Update() override;
    //void Render() override;
    void Draw() override;

    float GetX() const;
    float GetY() const;

    void HandleInput();
};




