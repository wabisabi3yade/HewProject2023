#pragma once
#include "CObject.h"
#include"CGrid.h"
class CGridObject :
    public CObject
{

private:
    CGrid *Grid;
    bool isFloor;
public:
    CGridObject(D3DBUFFER vb, D3DTEXTURE tex);
    ~CGridObject();
    void Draw();
    void Update();
    void SetGridPos(const int _PosX, const int _PosY);
    CGrid::GRID_XY GetGridPos();
    void CheckFloor();
    bool GetIsFloor();
};

