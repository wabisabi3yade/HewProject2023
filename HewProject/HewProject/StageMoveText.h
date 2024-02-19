#pragma once
#include "LoadCharacter.h"
#include <vector>

class StageMoveText
{	
	UI* base;
	D3DBUFFER moveBuffer;
	D3DTEXTURE moveTex;

	UI* W = nullptr;
	UI* num[2];
	UI* haihun = nullptr;
	UI* MoveText[4];
	UI* period[3];

	std::vector<UI*> text;

public:

	StageMoveText(int worldNum, int stageNum);

	void Update();

	void Draw();

	~StageMoveText();
};

