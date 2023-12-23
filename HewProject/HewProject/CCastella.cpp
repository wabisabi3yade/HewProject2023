#include "CCastella.h"

CCastella::CCastella(D3DBUFFER vb, D3DTEXTURE tex)
	:CGridObject(vb,tex)
{

}

CCastella::~CCastella()
{
}

void CCastella::Update()
{
	CGridObject::Update();
}

void CCastella::Draw()
{
	CGridObject::Draw();
}
