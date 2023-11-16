#include "DoTween.h"


int  debugCnt = 0;

void DoTween::Update()
{
	if (!IsDoMove)
	{
		return;
	}
	if (moveTime > 0.0f)
	{
		debugCnt++;
		//moveTime -= 1 / 60.0f;
		switch (moveState)
		{
		case DoTween::NONE:
			return;
			break;
		case DoTween::MOVE:
			moveTime -= 1 / 60.0f;
			switch (movedir)
			{
			case TO_TOP_LEFT:
				objptr->SetDir(Vector3(-1.0f,-1.0f,0.0f));
				if (moveTime < 0)
				{
					moveTime = 0;
					objptr->SetMoveSpeed(0);
					objptr->SetDir(Vector3::zero);
					IsDoMove = false;
					moveState = MOVESTATE::NONE;
				}
				break;
			case TO_TOP_RIGHT:
				objptr->SetDir(Vector3(1.0f,1.0f,0.0f));
				if (moveTime < 0)
				{
					moveTime = 0;
					objptr->SetMoveSpeed(0);
					objptr->SetDir(Vector3::zero);
					IsDoMove = false;
					moveState = MOVESTATE::NONE;
				}
				break;
			case TO_BOTTOM_LEFT:
				objptr->SetDir(Vector3(-1.0f,-1.0f,0.0f));
				if (moveTime < 0)
				{
					moveTime = 0;
					objptr->SetMoveSpeed(0);
					objptr->SetDir(Vector3::zero);
					IsDoMove = false;
					moveState = MOVESTATE::NONE;
				}
				break;
			case TO_BOTTOM_RIGHT:
				objptr->SetDir(Vector3(1.0f, -1.0f, 0.0f));
				if (moveTime < 0)
				{
					moveTime = 0;
					objptr->SetMoveSpeed(0);
					objptr->SetDir(Vector3::zero);
					IsDoMove = false;
					moveState = MOVESTATE::NONE;
				}
				break;
			default:
				break;

			}
			break;
		case DoTween::MOVEX:
			moveTime -= 1 / 60.0f;
			objptr->SetMoveSpeed(moveSpeed);
			if (movedir == MOVEDIR::RIGHT)
			{
				objptr->SetDir(Vector3::right);
			}
			else
			{
				objptr->SetDir(Vector3::left);
			}
			if (moveTime < 0)
			{
				moveTime = 0;
				objptr->SetMoveSpeed(0);
				objptr->SetDir(Vector3::zero);
				IsDoMove = false;
				moveState = MOVESTATE::NONE;
			}
			break;
		case DoTween::MOVEY:
			moveTime -= 1 / 60.0f;
			objptr->SetMoveSpeed(moveSpeed);
			if (movedir == MOVEDIR::UP)
			{
				objptr->SetDir(Vector3::up);
			}
			else
			{
				objptr->SetDir(Vector3::down);
			}
			if (moveTime < 0)
			{
				moveTime = 0;
				objptr->SetMoveSpeed(0);
				objptr->SetDir(Vector3::zero);
				IsDoMove = false;
				moveState = MOVESTATE::NONE;
			}
			break;
		case DoTween::SCALEDOWN:
			moveTime -= 1 / 60.0f;
			if (objptr->mTransform.scale >= Vector3::zero)
			{
				objptr->mTransform.scale.x -= moveSpeed;
				objptr->mTransform.scale.y -= moveSpeed;
			}
			if (moveTime < 0)
			{
				moveTime = 0;
				objptr->SetMoveSpeed(0);
				objptr->SetDir(Vector3::zero);
				IsDoMove = false;
				moveState = MOVESTATE::NONE;
			}
			break;
		case DoTween::SCALEUP:
			moveTime -= 1 / 60.0f;
			objptr->mTransform.scale.x += moveSpeed;
			objptr->mTransform.scale.y += moveSpeed;
			//objptr->mTransform.scale.z += moveSpeed;
			if (moveTime < 0)
			{
				moveTime = 0;
				objptr->SetMoveSpeed(0);
				objptr->SetDir(Vector3::zero);
				IsDoMove = false;
				moveState = MOVESTATE::NONE;
			}
			break;
		case DoTween::MOVESTATE::MOVECURVE:
			nowTime += 1.0f / 60;
			float t = nowTime * (1.0f / moveTime);
			objptr->mTransform.pos.x =
				(pow((1 - t), 2) * oldPos.x)
				+ (2 * t) * (1 - t) * ((oldPos.x + targetPos.x) / 2)
				+ (pow(t, 2) * targetPos.x);

			objptr->mTransform.pos.y =
				(pow((1 - t), 2) * oldPos.y)
				+ (2 * t) * (1 - t) * ((oldPos.y + targetPos.y) / 2 + curvePos)
				+ (pow(t, 2) * targetPos.y);

			if (moveTime <= nowTime)
			{
				moveState = MOVESTATE::NONE;
				IsDoMove = false;
				objptr->mTransform.pos.x = targetPos.x;
				objptr->mTransform.pos.y = targetPos.y;
				objptr = nullptr;

			}
			break;
		}
	}
	//else if (moveTime < 0)
	//{
	//	moveTime = 0;
	//	objptr->SetMoveSpeed(0);
	//	objptr->SetDir(Vector3::zero);
	//	IsDoMove = false;
	//	moveState = MOVESTATE::NONE;

	//}
}

DoTween::DoTween()
{
	objptr = nullptr;
	moveSpeed = 0.0f;
	moveTime = 0.0f;
	nowTime = 0.0f;
	curvePos = 0.0f;
	IsDoMove = false;
	moveState = MOVESTATE::NONE;
	movedir = MOVEDIR::NONE;
}

DoTween::~DoTween()
{
	if (objptr != nullptr)
	{
		objptr = nullptr;
	}
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

void DoTween::DoMoveCurve(CObject* _Objptr, Vector3 _movePos, float _curvePos, float _moveTime)
{
	if (!IsDoMove)
	{
		objptr = _Objptr;
		targetPos.x = _movePos.x + objptr->mTransform.pos.x;
		targetPos.y = _movePos.y + objptr->mTransform.pos.y;
		moveTime = _moveTime;
		nowTime = 0.0f;
		oldPos = objptr->mTransform.pos;
		curvePos = _curvePos;
		moveState = MOVESTATE::MOVECURVE;
		IsDoMove = true;
	}
}

void DoTween::DoMove(CObject* _Objptr, float _moveSpeed, float _moveTime, MOVEDIR _movedir)
{
	if (!IsDoMove)
	{
		objptr = _Objptr;
		moveSpeed = _moveSpeed / (_moveTime * 60);
		objptr->SetMoveSpeed(moveSpeed);
		moveTime = _moveTime - (1.0 / 60);
		IsDoMove = true;
		movedir = _movedir;
		objptr->SetDir(movedir);
		moveState = MOVESTATE::MOVE;
	}
}

