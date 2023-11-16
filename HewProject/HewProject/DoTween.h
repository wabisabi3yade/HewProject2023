#pragma once
#include "CObject.h"
enum MOVEDIR
{
	NONE,
	RIGHT,
	LEFT,
	UP,
	DOWN,
	TO_TOP_LEFT,
	TO_TOP_RIGHT,
	TO_BOTTOM_LEFT,
	TO_BOTTOM_RIGHT,
};

class DoTween
{
private:
	enum  MOVESTATE
	{
		NONE,
		MOVE,
		MOVEX,
		MOVEY,
		SCALEUP,
		SCALEDOWN,
		MOVECURVE,
	};
	CObject* objptr;
	float nowTime;
	float moveTime;
	float moveSpeed;
	float curvePos;
	bool IsDoMove;
	MOVESTATE moveState;
	MOVEDIR movedir;
	Vector3 oldPos;
	Vector3 targetPos;
public:
	void Update();

	DoTween();
	~DoTween();

	void DoMove(CObject* _Objptr, float _moveSpeed, float _moveTime, MOVEDIR _movedir);
	void DoMoveX(CObject* _Objptr, float _moveSpeed, float _moveTime, MOVEDIR _movedir);
	void DoMoveY(CObject* _Objptr, float _moveSpeed, float _moveTime,MOVEDIR _movedir);
	void DoScaleUp(CObject* _Objptr, float _moveSpeed, float _moveTime);
	void DoScaleDown(CObject* _Objptr, float _moveSpeed, float _moveTime);
	void DoMoveCurve(CObject* _Objptr, Vector3 _movePos, float _curvePos, float _moveTime);
};

