#pragma once
#include "CScene.h"

class Fade;
class CalorieGage_hori;
class FloorUI;
class UI;
class ButtonUI;
class ProteinUI;
class CoinUI;

class Tutorial;

class Fade_TestScene
	:public CScene
{


	Fade* fade;
	CalorieGage_hori* gage;
	FloorUI* floorUI;

	D3DBUFFER buffer;
	D3DBUFFER b;
	ButtonUI* buttonUI;

	ProteinUI* proteinUI;
	CoinUI* coinUI;

	Tutorial* tutorial;

	D3DTEXTURE tutorial1Tex;
	D3DTEXTURE tutorial2Tex;

public:
	Fade_TestScene();
	~Fade_TestScene();

	void Update() override;
	void LateUpdate() override;
	void Draw() override;
};

