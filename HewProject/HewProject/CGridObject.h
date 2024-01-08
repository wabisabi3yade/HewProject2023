#pragma once
#include "CObject.h"
#include"CGrid.h"
class CGridObject :
    public CObject
{

protected:
    CGrid *Grid;
    int BlockType;
    int category;
public:
    CGridObject(D3DBUFFER vb, D3DTEXTURE tex);
    virtual ~CGridObject();
    void Draw();
    void Update();
    void SetGridPos(const int _PosX, const int _PosY);
    CGrid::GRID_XY GetGridPos() const { return Grid->gridPos; };

    void SetBlookType(int _BkType) { BlockType = _BkType; };
    int GetBlookType() const { return BlockType; };
    
    void SetCategory(int _category) { category = _category; };
    int GetCategory() const { return category; };
};

