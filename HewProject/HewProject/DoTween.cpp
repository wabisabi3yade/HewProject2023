#include "DoTween.h"

void DoTween::Updeta()
{
	if (moveTime > 0)
	{
		moveTime -= 1 / 60.0f;
		switch (moveState)
		{
		case DoTween::NONE:
			return;
			break;
		case DoTween::MOVEX:
			objptr->SetMoveSpeed(moveSpeed);
			objptr->SetDir(Vector3::right);
			break;
		case DoTween::MOVEY:
			objptr->SetMoveSpeed(moveSpeed);
			objptr->SetDir(Vector3::up);
			break;
		default:
			break;
		}
	}
	else if(moveTime < 0)
	{
		moveTime = 0;
		objptr->SetMoveSpeed(0);
		objptr->SetDir(Vector3::zero);
		IsDoMove = false;
		moveState = MOVESTATE::NONE;

	}
}

DoTween::DoTween()
{
	objptr = nullptr;
	moveSpeed = 0.0f;
	moveTime = 0.0f;
	IsDoMove = false;
	moveState = MOVESTATE::NONE;
}

DoTween::~DoTween()
{
}

void DoTween::DoMoveX(CObject* _Objptr, float _moveSpeed, float _moveTime)
{
	if (!IsDoMove)
	{
		objptr = _Objptr;
		moveSpeed = _moveSpeed / (_moveTime * 60);
		moveTime = _moveTime- (1.0/60);
		IsDoMove = true;
		moveState = MOVESTATE::MOVEX;
	}
}

void DoTween::DoMoveY(CObject* _Objptr, float _moveSpeed, float _moveTime)
{
	if (!IsDoMove)
	{
		objptr = _Objptr;
		moveSpeed = _moveSpeed / (_moveTime *60);
		moveTime = _moveTime - (1.0 / 60);
		IsDoMove = true;
		moveState = MOVESTATE::MOVEY;
	}
}
