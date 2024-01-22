#pragma once
#include "UI.h"
class NowLoadingText :
    public UI
{
    const short textNum = 10;
    UI* text[10];
    UI* character;

    D3DBUFFER buffer;

public:
    NowLoadingText();
    ~NowLoadingText();

    void SetTexText(D3DTEXTURE&& _tex);
    void SetTexCharacter(D3DTEXTURE&& _tex);
};

