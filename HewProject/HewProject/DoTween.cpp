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
			if (movedir == MOVEDIR::RIGHT)
			{
				objptr->SetDir(Vector3::right);
			}
			else
			{
				objptr->SetDir(Vector3::left);
			}
			break;
		case DoTween::MOVEY:
			objptr->SetMoveSpeed(moveSpeed);
			if (movedir == MOVEDIR::UP)
			{
				objptr->SetDir(Vector3::up);
			}
			else
			{
				objptr->SetDir(Vector3::down);
			}
			break;
		case DoTween::SCALEDOWN:
			if (objptr->mTransform.scale >= Vector3::zero)
			{
				objptr->mTransform.scale.x -= moveSpeed;
				objptr->mTransform.scale.y -= moveSpeed;
			}
			//objptr->mTransform.scale.z -= moveSpeed;
			break;
		case DoTween::SCALEUP:
			objptr->mTransform.scale.x += moveSpeed;
			objptr->mTransform.scale.y += moveSpeed;
			//objptr->mTransform.scale.z += moveSpeed;
			break;
		default:
			break;
		}
	}
	else if (moveTime < 0)
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
	movedir = MOVEDIR::NONE;
}

DoTween::~DoTween()
{
}

void DoTween::DoMoveX(CObject* _Objptr, float _moveSpeed, float _moveTime, MOVEDIR _movedir)
{
	if (!IsDoMove)
	{
		objptr = _Objptr;
		moveSpeed = _moveSpeed / (_moveTime * 60);
		moveTime = _moveTime - (1.0 / 60);
		IsDoMove = true;
		movedir = _movedir;
		moveState = MOVESTATE::MOVEX;
	}
}

void DoTween::DoMoveY(CObject* _Objptr, float _moveSpeed, float _moveTime, MOVEDIR _movedir)
{
	if (!IsDoMove)
	{
		objptr = _Objptr;
		moveSpeed = _moveSpeed / (_moveTime * 60);
		moveTime = _moveTime - (1.0 / 60);
		IsDoMove = true;
		movedir = _movedir;
		moveState = MOVESTATE::MOVEY;
	}
}

void DoTween::DoScaleUp(CObject* _Objptr, float _moveSpeed, float _moveTime)
{
	if (!IsDoMove)
	{
		objptr = _Objptr;
		moveSpeed = _moveSpeed / (_moveTime * 60);
		moveTime = _moveTime - (1.0 / 60);
		IsDoMove = true;
		moveState = MOVESTATE::SCALEUP;
	}
}

void DoTween::DoScaleDown(CObject* _Objptr, float _moveSpeed, float _moveTime)
{
	if (!IsDoMove)
	{
		objptr = _Objptr;
		moveSpeed = _moveSpeed / (_moveTime * 60);
		moveTime = _moveTime - (1.0 / 60);
		IsDoMove = true;
		moveState = MOVESTATE::SCALEDOWN;
	}
}
