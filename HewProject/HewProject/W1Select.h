#pragma once
#include "StageSelect.h"
class W1Select :
    public StageSelect
{
    void Input() override;

public:
    W1Select();

    void Update() override;

    void Draw() override;

    ~W1Select();
};

