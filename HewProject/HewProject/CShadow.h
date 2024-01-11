#pragma once
#include "CObject.h"

class CShadow
	: public CObject
{
public:
	CShadow(D3DBUFFER vb, D3DTEXTURE tex);

	~CShadow();

	void Update() override;
	void Draw() override;
};

