#include "CCastella.h"

CCastella::CCastella(D3DBUFFER vb, D3DTEXTURE tex)
	:CGridObject(vb,tex)
{
	dotween = std::make_unique<DoTween>(this);
}

CCastella::~CCastella()
{
}

void CCastella::Update()
{
	CGridObject::Update();
	dotween->Update();
}

void CCastella::Move(Vector3 _pos, bool isFall, Vector3 _fallPos)
{
	dotween->DoMove(_pos, CASTELLAWALK_TIME);

	if (isFall)
	{
		dotween->Append(_fallPos, CASTELLAFALL_TIME, DoTween::FUNC::MOVE);
	}
	

}

void CCastella::Draw()
{
	CGridObject::Draw();
}
