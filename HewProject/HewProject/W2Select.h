#pragma once
#include "StageSelect.h"
class W2Select :
    public StageSelect
{
public:
    W2Select();

    void Update() override;

    void Draw() override;

    ~W2Select();
};

