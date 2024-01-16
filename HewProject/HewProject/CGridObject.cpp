#include "CGridObject.h"

CGridObject::CGridObject(D3DBUFFER vb, D3DTEXTURE tex)
	:CObject(vb,tex)
{
	Grid = new CGrid();
}

CGridObject::~CGridObject()
{
	CLASS_DELETE(Grid)
}

void CGridObject::Draw()
{
	CObject::Draw();
}

void CGridObject::Update()
{
}

void CGridObject::SetGridPos(const int _PosX,const int _PosY)
{
	Grid->gridPos.x = _PosX;
	Grid->gridPos.y = _PosY;
}

void CGridObject::SetGridPos(CGrid::GRID_XY _gridXY)
{
	this->Grid->gridPos = _gridXY;
}

