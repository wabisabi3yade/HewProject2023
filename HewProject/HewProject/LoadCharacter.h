#pragma once
#include "UI.h"

// ���[�h���̃L�����N�^�[
class LoadCharacter :
    public UI
{
public:
    LoadCharacter(D3DBUFFER vb, D3DTEXTURE tex);

    ~LoadCharacter();

    void Update() override;
    void Draw() override;
};

