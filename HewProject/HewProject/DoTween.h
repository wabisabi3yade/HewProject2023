#pragma once
#include "CObject.h"
class DoTween
{
private:
	enum MOVESTATE
	{
		NONE,
		MOVEX,
		MOVEY
	};
	CObject* objptr;
	float moveTime;
	float moveSpeed;
	bool IsDoMove;
	MOVESTATE moveState;

public:
	void Updeta();

	DoTween();
	~DoTween();

	void DoMoveX(CObject* _Objptr, float _moveSpeed, float _moveTime);
	void DoMoveY(CObject* _Objptr, float _moveSpeed, float _moveTime);
};

