#include "CWall.h"
#include "DoTween.h"
#include"Player.h"

CWall::CWall(D3DBUFFER vb, D3DTEXTURE tex)
	:CGridObject(vb, tex)
{
	dotween = new DoTween(this);
	isBreak = false;
	isDecrease = false;
	time = 0;
}
CWall::~CWall()
{
	CLASS_DELETE(dotween);
}

void CWall::Update()
{
	CGridObject::Update();
	dotween->Update();
	if (isBreak)
	{
		time += 1.0f / 60.0;
		static short c_time = 0;
		static short o_time = 0;
		c_time = static_cast<UINT>(time / 0.1f);
		if (c_time != o_time)
		{
			this->ChangeInvisible();
		}
		o_time = c_time;
	}
	if (isDecrease)
	{
		this->materialDiffuse.w -= 0.01f;
	}
}

void CWall::Draw()
{
	CGridObject::Draw();
}

void CWall::Break(float _breakTime)
{
	dotween->DelayedCall(_breakTime / 3.0, [&]()
		{
			isBreak = true;
			time = 0;
		});
	dotween->DelayedCall(_breakTime /2.0f, [&]()
		{
			isDecrease = true;
		});
	dotween->DelayedCall(_breakTime, [&]()
		{
			isBreak = false;
			this->SetActive(false);
		});
}
