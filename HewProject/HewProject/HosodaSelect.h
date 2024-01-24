#pragma once
#include "CScene.h"
class HosodaSelect
	: public CScene
{

	wchar_t* WriteText;

public:
	HosodaSelect();
	~HosodaSelect();

	void Update() override;

	void LateUpdate() override;

	void Draw() override;
};