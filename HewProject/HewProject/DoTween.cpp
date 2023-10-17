#include "DoTween.h"

void DoTween::Updeta()
{
	switch (moveState)
	{
	case DoTween::NONE:
		return;
		break;
	case DoTween::MOVEX:
		if (GetTickCount64() < time + moveTime * 1000)
		{
			objptr->mTransform.pos.x += movePos /(moveTime * 1000 / 60.0f) ;
		}
		else
		{
			IsDoMove = false;
		}
		break;
	case DoTween::MOVEY:
		if (GetTickCount64() > time + moveTime * 1000)
		{
			objptr->mTransform.pos.y += movePos;
		}
		break;
	default:
		break;
	}
}

DoTween::DoTween()
{
	objptr = nullptr;
	movePos = 0.0f;
	moveTime = 0.0f;
	IsDoMove = false;
	moveState = MOVESTATE::NONE;
}

DoTween::~DoTween()
{
}

void DoTween::DoMoveX(CObject* _Objptr, float _movepos, float _moveTime)
{
	if (!IsDoMove)
	{

	objptr = _Objptr;
	movePos = _movepos;
	moveTime = _moveTime;
	IsDoMove = true;
	time = GetTickCount64();
	moveState = MOVESTATE::MOVEX;
	}
}

void DoTween::DoMoveY(CObject* _Objptr, float _movespeed, float _moveTime)
{
	if (!IsDoMove)
	{

	objptr = _Objptr;
	movePos = _movespeed;
	moveTime = _moveTime;
	IsDoMove = true;
	time = GetTickCount64();
	moveState = MOVESTATE::MOVEY;
	}
}
