#pragma once
#include "CObject.h"

class CGrid;

// プレイヤー（リス）のオブジェクトクラス
class Player: 
	public CObject
{
	CGrid* grid;


public:
	Player(D3DBUFFER vb, D3DTEXTURE tex);

	~Player();
};

