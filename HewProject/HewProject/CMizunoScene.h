#pragma once
#include "CScene.h"
#include"CStageMake.h"
#include"Ccontroller.h"
#include "DoTween.h"
#include"CFade.h"
#include<vector>
#include<list>
class CMizunoScene :
    public CScene
{
    D3DBUFFER charBuffer;
    D3DTEXTURE charTexture;
    CObject* charObj;

    D3DBUFFER charBuffer2;
    D3DTEXTURE charTexture2;
    CObject* charObj2;
    //DoTween* doToween;

    CFade* fade;
    D3DBUFFER fadeBuffer;
    D3DTEXTURE fadeTexture;

    CObject* a[5];
    D3DTEXTURE centerTexture;

    CLoadStage* stage;
    CStageMake* stageMake;

    CObject* stageobj[39];

    std::vector<CObject*> stageObj;
    std::list<CObject*> stageObjList;
    int ss = 0;
    Input input;
public:
    CMizunoScene();

    ~CMizunoScene();

    void Update() override;

    void LateUpdate() override;

    void Draw() override;
};

void Z_Sort(std::vector<CObject*>& _sortList);
void Z_SortList(std::list<CObject*> _sortList);