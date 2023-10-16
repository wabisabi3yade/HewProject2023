#pragma once
#include "CObject.h"
class DoTween
{
private:
	CObject* objptr;
	float moveSpeed;
	float moveTime;
	bool IsDoMove;


public:
	void Updeta();

	DoTween();
	~DoTween();

	void DoMoveX(CObject* _Objptr, float _movespeed, float _moveTime);
	void DoMoveY(CObject* _Objptr, float _movespeed, float _moveTime);
};

