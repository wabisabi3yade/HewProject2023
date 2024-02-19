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

	enum TYPE
	{
		STAGE1_1,
		STAGE1_2,
		STAGE1_3,
		STAGE1_4
	};


private:
	STATE state = STATE::STAY;

	bool isActive = false;

	bool isEnd = false;

	std::vector<D3DTEXTURE> tutorialTex;
	int nowPage = 1;

	UI* tutorialUI;
	UI* fade;

	D3DBUFFER tutorialBuf;
	D3DBUFFER LR_Buf;

	UI* base;

	UI* backUI;

	UI* LR_UI[2];

public:
	Tutorial(int _type);
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
};

