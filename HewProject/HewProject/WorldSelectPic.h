#pragma once
#include "CObject.h"

class DoTween;

class WorldSelectPic :
    public CObject
{
public:
    DoTween* dotween;

    WorldSelectPic(D3DBUFFER vb, D3DTEXTURE tex);

    void Update() override;

    void Draw() override;
    ~WorldSelectPic();
};

