#pragma once
class Time
{

public:
	static float deltaTime; //デルタタイム
	static float slowTime;	//スロータイム
	static bool isSlow;		//スロー判定

	//Time更新
	static void Update();

};

