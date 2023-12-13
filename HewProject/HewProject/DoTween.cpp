#include "DoTween.h"
#include"Time.h"

Vector3 DoTween::GetVector(Vector3 _start, Vector3 _end)
{
	// ベクトルを求める
	Vector3 vec = { _end.x - _start.x,
					_end.y - _start.y,
					_end.z - _start.z };

	// ベクトルの長さを求める
	double dis = pow((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z), 0.5);

	// 単位ベクトルを求める
	vec = { vec.x / (float)dis,vec.y / (float)dis, vec.z / (float)dis };


	/*DirectX::XMVECTOR v = XMLoadFloat3(dirChange(vec));
	v = DirectX::XMVector3Normalize(v);
	XMStoreFloat3(dirChange(vec), v);*/

	return vec;
}

float DoTween::GetVector(float _start, float _end)
{
	float vec = 0;

	// 目標座標が現在の座標より正の方向にあるなら
	if (_end - _start > 0)
	{
		vec = 1;
	}
	// 負なら
	else if (_end - _start < 0)
	{
		vec = -1;
	}
	// 距離0(移動しないなら)
	else
	{
		vec = 0;
	}

	return vec;
}

float DoTween::GetSpeed(Vector3 _start, Vector3 _end, float _time)
{
	// ベクトルを求める
	Vector3 vec = { _end.x - _start.x,
					_end.y - _start.y,
					_end.z - _start.z };
	// ベクトルの長さを求める
	double dis = pow((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z), 0.5);

	float spd = dis / (_time * 60);

	/*spd *= Time::slowTime;*/

	return spd;
}

void DoTween::Update()
{
	// Dotween起動していないなら抜ける	
	if (!IsDoMove)	return;

	// 現在時間が移動にかかる時間を超えていないなら
	if (nowTime < moveTime)
	{

		/*nowTime += Time::deltaTime;*/
		nowTime += 1.0f / 60;
		switch (state)
		{
		case TYPE::MOVE:
			objptr->mTransform.pos.x += moveDir.x * moveSpeed;
			objptr->mTransform.pos.y += moveDir.y * moveSpeed;
			objptr->mTransform.pos.z += moveDir.z * moveSpeed;
			break;

		case TYPE::SCALE:
			objptr->mTransform.scale.x += moveDir.x * moveSpeed;
			objptr->mTransform.scale.y += moveDir.y * moveSpeed;
			objptr->mTransform.scale.z += moveDir.z * moveSpeed;
			break;
		}

	}

	// 移動時間が終わると
	else
	{
		state = TYPE::NONE;
		IsDoMove = false;
		objptr->mTransform.pos = targetPos;
		nowTime = 0.0f;
		objptr = nullptr;
	}
}

//void DoTween::Update()
//{
//	if (!IsDoMove)
//	{
//		return;
//	}
//	if (moveTime > 0.0f)
//	{
//		debugCnt++;
//		switch (moveState)
//		{
//		case DoTween::NONE:
//			return;
//			break;
//		case DoTween::MOVE:
//			moveTime -= 1 / 60.0f * Time::slowTime;
//			switch (movedir)
//			{
//			case TO_TOP_LEFT:
//				objptr->SetDir(Vector3(-1.0f,-1.0f,0.0f));
//				if (moveTime < 0)
//				{
//					moveTime = 0;
//					objptr->SetMoveSpeed(0);
//					objptr->SetDir(Vector3::zero);
//					IsDoMove = false;
//					moveState = MOVESTATE::NONE;
//				}
//				break;
//
//			case MOVE_POS:
//				
//
//				break;
//			case TO_TOP_RIGHT:
//				objptr->SetDir(Vector3(1.0f,1.0f,0.0f));
//				if (moveTime < 0)
//				{
//					moveTime = 0;
//					objptr->SetMoveSpeed(0);
//					objptr->SetDir(Vector3::zero);
//					IsDoMove = false;
//					moveState = MOVESTATE::NONE;
//				}
//				break;
//			case TO_BOTTOM_LEFT:
//				objptr->SetDir(Vector3(-1.0f,-1.0f,0.0f));
//				if (moveTime < 0)
//				{
//					moveTime = 0;
//					objptr->SetMoveSpeed(0);
//					objptr->SetDir(Vector3::zero);
//					IsDoMove = false;
//					moveState = MOVESTATE::NONE;
//				}
//				break;
//			case TO_BOTTOM_RIGHT:
//				objptr->SetDir(Vector3(1.0f, -1.0f, 0.0f));
//				if (moveTime < 0)
//				{
//					moveTime = 0;
//					objptr->SetMoveSpeed(0);
//					objptr->SetDir(Vector3::zero);
//					IsDoMove = false;
//					moveState = MOVESTATE::NONE;
//				}
//				break;
//			default:
//				break;
//
//			}
//			break;
//		case DoTween::MOVEX:
//			moveTime -= 1 / 60.0f * Time::slowTime;
//			objptr->SetMoveSpeed(moveSpeed);
//			if (movedir == MOVEDIR::RIGHT)
//			{
//				objptr->SetDir(Vector3::right);
//			}
//			else
//			{
//				objptr->SetDir(Vector3::left);
//			}
//			if (moveTime < 0)
//			{
//				moveTime = 0;
//				objptr->SetMoveSpeed(0);
//				objptr->SetDir(Vector3::zero);
//				IsDoMove = false;
//				moveState = MOVESTATE::NONE;
//			}
//			break;
//		case DoTween::MOVEY:
//			moveTime -= 1 / 60.0f * Time::slowTime;
//			objptr->SetMoveSpeed(moveSpeed);
//			if (movedir == MOVEDIR::UP)
//			{
//				objptr->SetDir(Vector3::up);
//			}
//			else
//			{
//				objptr->SetDir(Vector3::down);
//			}
//			if (moveTime < 0)
//			{
//				moveTime = 0;
//				objptr->SetMoveSpeed(0);
//				objptr->SetDir(Vector3::zero);
//				IsDoMove = false;
//				moveState = MOVESTATE::NONE;
//			}
//			break;
//		case DoTween::SCALEDOWN:
//			moveTime -= 1 / 60.0f * Time::slowTime;
//			if (objptr->mTransform.scale >= Vector3::zero)
//			{
//				objptr->mTransform.scale.x -= moveSpeed * Time::slowTime;
//				objptr->mTransform.scale.y -= moveSpeed * Time::slowTime;
//			}
//			if (moveTime < 0)
//			{
//				moveTime = 0;
//				objptr->SetMoveSpeed(0);
//				objptr->SetDir(Vector3::zero);
//				IsDoMove = false;
//				moveState = MOVESTATE::NONE;
//			}
//			break;
//		case DoTween::SCALEUP:
//			moveTime -= 1 / 60.0f * Time::slowTime;
//			objptr->mTransform.scale.x += moveSpeed *Time::slowTime;
//			objptr->mTransform.scale.y += moveSpeed * Time::slowTime;
//			//objptr->mTransform.scale.z += moveSpeed;
//			if (moveTime  < 0)
//			{
//				moveTime = 0;
//				objptr->SetMoveSpeed(0);
//				objptr->SetDir(Vector3::zero);
//				IsDoMove = false;
//				moveState = MOVESTATE::NONE;
//			}
//			break;
//		case DoTween::MOVESTATE::MOVECURVE:
//			nowTime += 1.0f / 60;
//			float t = nowTime * (1.0f / moveTime);
//			objptr->mTransform.pos.x =
//				((pow((1 - t), 2) * oldPos.x)
//				+ (2 * t) * (1 - t) * ((oldPos.x + targetPos.x) / 2)
//				+ (pow(t, 2) * targetPos.x)*Time::slowTime);
//
//			objptr->mTransform.pos.y =
//				((pow((1 - t), 2) * oldPos.y)
//				+ (2 * t) * (1 - t) * ((oldPos.y + targetPos.y) / 2 + curvePos)
//				+ (pow(t, 2) * targetPos.y) * Time::slowTime);
//
//			if (moveTime <= nowTime)
//			{
//				moveState = MOVESTATE::NONE;
//				IsDoMove = false;
//				objptr->mTransform.pos.x = targetPos.x;
//				objptr->mTransform.pos.y = targetPos.y;
//				objptr = nullptr;
//
//			}
//			break;
//		}
//	}
//	//else if (moveTime < 0)
//	//{
//	//	moveTime = 0;
//	//	objptr->SetMoveSpeed(0);
//	//	objptr->SetDir(Vector3::zero);
//	//	IsDoMove = false;
//	//	moveState = MOVESTATE::NONE;
//
//	//}
//}

DoTween::DoTween()
{
	objptr = nullptr;
	moveSpeed = 0.0f;
	moveTime = 0.0f;
	nowTime = 0.0f;
	curvePos = 0.0f;
	IsDoMove = false;
	state = TYPE::NONE;
	moveDir = MOVEDIR::NONE;
}

DoTween::~DoTween()
{
	if (objptr != nullptr)
	{
		objptr = nullptr;
	}
}

void DoTween::DoMove(CObject* _Objptr, Vector3 _targetPos, float _moveTime)
{
	if (!IsDoMove)
	{
		IsDoMove = true;	// Dotween起動
		targetPos = _targetPos;
		objptr = _Objptr;
		moveTime = _moveTime - (1.0f / 60);
		state = TYPE::MOVE;

		// 単位ベクトルを求める
		moveDir = GetVector(objptr->mTransform.pos, _targetPos);

		moveSpeed = GetSpeed(objptr->mTransform.pos, targetPos, _moveTime);
	}
}





void DoTween::DoMoveX(CObject* _Objptr, float _targetPosX, float _moveTime)
{
	if (!IsDoMove)
	{
		IsDoMove = true;	// Dotween起動
		objptr = _Objptr;
		moveTime = _moveTime;
		targetPos.x = _targetPosX;
		state = TYPE::MOVE;

		// 方向ベクトルを求める
		moveDir = Vector3::zero;
		moveDir.x = GetVector(_Objptr->mTransform.pos.x, _targetPosX);

		// 速度を求める
		moveSpeed = GetSpeed({ objptr->mTransform.pos.x,0,0 },
			{ _targetPosX, 0,0 }, _moveTime);
	}
}

void DoTween::DoMoveY(CObject* _Objptr, float _targetPosY, float _moveTime)
{
	if (!IsDoMove)
	{
		IsDoMove = true;	// Dotween起動
		objptr = _Objptr;
		moveTime = _moveTime;
		targetPos.y = _targetPosY;
		state = TYPE::MOVE;

		// 方向ベクトルを求める
		moveDir = Vector3::zero;
		moveDir.y = GetVector(_Objptr->mTransform.pos.y, _targetPosY);

		// 速度を求める
		moveSpeed = GetSpeed({ 0,objptr->mTransform.pos.y, 0 },
			{ 0, _targetPosY, 0 }, _moveTime);
	}
}

void DoTween::DoScale(CObject* _Objptr, Vector3 _targetScale, float _moveTime)
{
	if (!IsDoMove)
	{
		IsDoMove = true;	// Dotween起動
		targetPos = _targetScale;
		objptr = _Objptr;
		moveTime = _moveTime - (1.0f / 60);
		state = TYPE::SCALE;

		// 単位ベクトルを求める
		moveDir = GetVector(objptr->mTransform.scale, _targetScale);

		moveSpeed = GetSpeed(objptr->mTransform.scale, _targetScale, _moveTime);
	}
}

//void DoTween::DoMoveX(CObject* _Objptr, float _moveSpeed, float _moveTime, Vector3 _movedir)
//{
//	if (!IsDoMove)
//	{
//		objptr = _Objptr;
//		moveSpeed = _moveSpeed / (_moveTime * 60) * Time::slowTime;
//		moveTime =
//			IsDoMove = true;
//		moveDir = _movedir;
//		moveState = MOVESTATE::MOVEX;
//	}
//}
//
//void DoTween::DoMoveY(CObject* _Objptr, float _moveSpeed, float _moveTime, Vector3 _movedir)
//{
//	if (!IsDoMove)
//	{
//		objptr = _Objptr;
//		moveSpeed = _moveSpeed / (_moveTime * 60) * Time::slowTime;
//		moveTime = _moveTime - (1.0 / 60);
//		IsDoMove = true;
//		moveDir = _movedir;
//		moveState = MOVESTATE::MOVEY;
//	}
//}
//
//void DoTween::DoScaleUp(CObject* _Objptr, float _moveSpeed, float _moveTime)
//{
//	if (!IsDoMove)
//	{
//		objptr = _Objptr;
//		moveSpeed = _moveSpeed / (_moveTime * 60);
//		moveTime = _moveTime - (1.0 / 60);
//		IsDoMove = true;
//		moveState = MOVESTATE::SCALEUP;
//	}
//}
//
//void DoTween::DoScaleDown(CObject* _Objptr, float _moveSpeed, float _moveTime)
//{
//	if (!IsDoMove)
//	{
//		objptr = _Objptr;
//		moveSpeed = _moveSpeed / (_moveTime * 60);
//		moveTime = _moveTime - (1.0 / 60);
//		IsDoMove = true;
//		moveState = MOVESTATE::SCALEDOWN;
//	}
//}
//
//void DoTween::DoMoveCurve(CObject* _Objptr, Vector3 _movePos, float _curvePos, float _moveTime)
//{
//	if (!IsDoMove)
//	{
//		objptr = _Objptr;
//		targetPos.x = _movePos.x + objptr->mTransform.pos.x;
//		targetPos.y = _movePos.y + objptr->mTransform.pos.y;
//		moveTime = _moveTime;
//		nowTime = 0.0f;
//		oldPos = objptr->mTransform.pos;
//		curvePos = _curvePos;
//		moveState = MOVESTATE::MOVECURVE;
//		IsDoMove = true;
//	}
//}
//
//void DoTween::DoMove(CObject* _Objptr, float _moveSpeed, float _moveTime, Vector3 _movedir)
//{
//	if (!IsDoMove)
//	{
//		objptr = _Objptr;
//		moveSpeed = _moveSpeed / (_moveTime * 60);
//		objptr->SetMoveSpeed(moveSpeed);
//		moveTime = _moveTime - (1.0 / 60);
//		IsDoMove = true;
//		moveDir = _movedir;
//		objptr->SetDir(moveDir);
//		moveState = MOVESTATE::MOVE;
//	}
//}
//
