#pragma once
#include "PlayerMove.h"

class NormalMove :
	public PlayerMove
{
public:
	NormalMove(Player* _p);

	// ˆÚ“®ŠÖ”
	void Move(DIRECTION _dir) override;

	void Step() override;

	// ‚Ç‚Ì•ûŒü‚ÉˆÚ“®‚ª‚Å‚«‚é‚©æ“¾‚·‚éŠÖ”
	void  CheckCanMove() override;

	~NormalMove();
};
