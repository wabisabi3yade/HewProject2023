#include "CFloor.h"

CFloor::CFloor(D3DBUFFER vb, D3DTEXTURE tex)
	:CGridObject(vb,tex)
{
}

CFloor::~CFloor()
{
}

void CFloor::Update()
{
	CGridObject::Update();
}

void CFloor::Draw()
{
	CGridObject::Draw();
}
