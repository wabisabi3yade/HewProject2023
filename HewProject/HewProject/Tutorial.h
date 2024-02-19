#pragma once
#include "UI.h"
#include <vector>

class Tutorial
{

public:
	enum STATE
	{
		STAY,
		FADE_IN,
		DISPLAY,
		FADE_OUT,
		END,
		NUM
	};

private:
	STATE state = STATE::STAY;
	bool isStage1_1 = false;

	bool isActive = false;

	bool isEnd = false;

	bool isMacho = false;

	bool isCanBack = true;

	bool isMachoOnce = false;

	std::vector<D3DTEXTURE> tutorialTex;
	int nowPage = 1;

	UI* tutorialUI;
	UI* fade;

	D3DBUFFER tutorialBuf;
	D3DBUFFER LR_Buf;

	D3DTEXTURE tex1_1 = NULL;

	UI* base;

	UI* backUI;

	UI* LR_UI[2];

public:
	Tutorial(bool _is1_1 = false);
	~Tutorial();

	void Display();

	void FeadOut();

	void Update();
	void FadeInUpdate();
	void DisplayUpdate();
	void FadeOutUpdate();

	void Draw();

	void SetActive(bool _set) { isActive = _set; }

	void SetPosition(const Vector3& _p);

	void SetTexture(D3DTEXTURE _tex);

	void ChangeLR(int num);

	int GetState();

	bool GetIs1_1();

	void MachoDisplay();

	bool GetIsMachoOnce();
};

