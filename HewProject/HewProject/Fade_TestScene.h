#pragma once
#include "CScene.h"
#include "CalorieGage.h"

class Fade;

class Fade_TestScene
	:public CScene
{
	Fade* fade;

	CalorieGage* calorieGage;

public:
	Fade_TestScene();
	~Fade_TestScene();

	void Update() override;
	void LateUpdate() override;
	void Draw() override;
};

