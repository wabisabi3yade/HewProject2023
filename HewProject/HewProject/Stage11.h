#pragma once
#include "Stage.h"
class Stage11 :
    public Stage
{

    CScene::SCENE_NAME nextStage = CScene::SCENE_NAME::STAGE1_2;
public:
    Stage11();
    ~Stage11();
};

