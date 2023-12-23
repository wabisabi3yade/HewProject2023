#include "CGridObject.h"

CGridObject::CGridObject(D3DBUFFER vb, D3DTEXTURE tex)
	:CObject(vb,tex)
{
	Grid = new CGrid();
	isFloor = false;
}

CGridObject::~CGridObject()
{
}

void CGridObject::Draw()
{
	CObject::Draw();
}

void CGridObject::Update()
{
	CObject::Update();
}

void CGridObject::SetGridPos(const int _PosX,const int _PosY)
{
	Grid->gridPos.x = _PosX;
	Grid->gridPos.y = _PosY;
}

CGrid::GRID_XY CGridObject::GetGridPos()
{
	return Grid->gridPos;
}

void CGridObject::CheckFloor()
{
	isFloor = true;
}

bool CGridObject::GetIsFloor()
{
	return isFloor;
}
