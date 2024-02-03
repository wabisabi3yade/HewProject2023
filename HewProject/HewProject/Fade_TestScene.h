#pragma once
#include "CScene.h"

class Fade;
class CalorieGage_hori;
class FloorUI;
class UI;
class ButtonUI;
class ProteinUI;

class Fade_TestScene
	:public CScene
{
	Fade* fade;
	CalorieGage_hori* gage;
	FloorUI* floorUI;

	D3DBUFFER buffer;
	ButtonUI* buttonUI;

	ProteinUI* proteinUI;


public:
	Fade_TestScene();
	~Fade_TestScene();

	void Update() override;
	void LateUpdate() override;
	void Draw() override;
};

