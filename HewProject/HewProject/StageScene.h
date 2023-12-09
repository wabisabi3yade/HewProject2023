#pragma once
#include"CScene.h"
#include"CStageMake.h"
#include"CLoadStage.h"
#include"Ccontroller.h"
#include"CFade.h"
#include<vector>
#include<list>
class StageScene :
    public CScene
{
private:
    CLoadStage* stage;
    CStageMake* stageMake;
    const char* CsvPath[PathLength];
public:

};

