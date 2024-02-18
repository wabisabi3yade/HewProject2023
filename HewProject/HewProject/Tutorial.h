#pragma once
#include "UI.h"

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

	bool isActive = false;

	bool isEnd = false;

	UI* tutorialUI;
	UI* fade;

	D3DTEXTURE tutorialTex;
	D3DBUFFER tutorialBuf;

	UI* base;

	UI* backUI;

public:
	Tutorial(D3DTEXTURE _tex);
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
};

