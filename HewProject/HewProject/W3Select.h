#pragma once
#include "StageSelect.h"
class W3Select :
    public StageSelect
{
public:
    W3Select();

    void Update() override;

    void Draw() override;

    ~W3Select();
};

