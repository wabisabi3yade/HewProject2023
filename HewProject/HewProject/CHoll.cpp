#include "CHoll.h"

CHoll::CHoll(D3DBUFFER vb, D3DTEXTURE tex)
	:CGridObject(vb,tex)
{
}

CHoll::~CHoll()
{
}

void CHoll::Update()
{
	CGridObject::Update();
}

void CHoll::Draw()
{
	CGridObject::Draw();
}
