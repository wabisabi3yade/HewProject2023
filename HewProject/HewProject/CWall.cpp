#include "CWall.h"
CWall::CWall(D3DBUFFER vb, D3DTEXTURE tex)
	:CGridObject(vb, tex)
{

}
CWall::~CWall()
{
}

void CWall::Updata()
{
	CGridObject::Update();
}

void CWall::Draw()
{
	CGridObject::Draw();
}
