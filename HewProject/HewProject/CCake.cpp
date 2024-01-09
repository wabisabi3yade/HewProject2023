#include "CCake.h"

CCake::CCake(D3DBUFFER vb, D3DTEXTURE tex)
	:CGridObject(vb,tex)
{
}

CCake::~CCake()
{

}

void CCake::Update()
{
	CGridObject::Update();
}

void CCake::Draw()
{
	CGridObject::Draw();
}
