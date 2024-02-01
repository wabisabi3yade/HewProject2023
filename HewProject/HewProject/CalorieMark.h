#pragma once
#include "UI.h"
class CalorieMark :
    public UI
{
public:
    enum COLOR 
    {
        RED,
        YELLOW,
        GREEN,
        NUM
    };
public:
    CalorieMark(D3DBUFFER vb, D3DTEXTURE tex);
    ~CalorieMark();

    void Update() override;

    void Draw() override;

    void SetColor(const COLOR& _setColor);
};

