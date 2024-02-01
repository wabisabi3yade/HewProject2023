#pragma once
#include "CScene.h"

class Fade;
class CalorieGage_hori;
class UI;
class Fade_TestScene
	:public CScene
{
	Fade* fade;
	CalorieGage_hori* gage;

public:
	Fade_TestScene();
	~Fade_TestScene();

	void Update() override;
	void LateUpdate() override;
	void Draw() override;
};

