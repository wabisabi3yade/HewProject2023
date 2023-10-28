#pragma once
#include "CObject.h"
enum MOVEDIR
{
	NONE,
	RIGHT,
	LEFT,
	UP,
	DOWN,
};

class DoTween
{
private:
	enum MOVESTATE
	{
		NONE,
		MOVEX,
		MOVEY,
		SCALEUP,
		SCALEDOWN,
	};
	CObject* objptr;
	float moveTime;
	float moveSpeed;
	bool IsDoMove;
	MOVESTATE moveState;
	MOVEDIR movedir;

public:
	void Updeta();

	DoTween();
	~DoTween();

	void DoMoveX(CObject* _Objptr, float _moveSpeed, float _moveTime, MOVEDIR _movedir);
	void DoMoveY(CObject* _Objptr, float _moveSpeed, float _moveTime,MOVEDIR _movedir);
	void DoScaleUp(CObject* _Objptr, float _moveSpeed, float _moveTime);
	void DoScaleDown(CObject* _Objptr, float _moveSpeed, float _moveTime);
};

