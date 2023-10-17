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
	float movePos;
	float moveTime;
	bool IsDoMove;
	MOVESTATE moveState;
	ULONGLONG time;

public:
	void Updeta();

	DoTween();
	~DoTween();

	void DoMoveX(CObject* _Objptr, float _movepos, float _moveTime);
	void DoMoveY(CObject* _Objptr, float _movepos, float _moveTime);
};

