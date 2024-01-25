#pragma once
#include "CScene.h"

class Fade;

class Fade_TestScene
	:public CScene
{
	
	Fade* fade;

public:
	Fade_TestScene();
	~Fade_TestScene();

	void Update() override;
	void LateUpdate() override;
	void Draw() override;
};

