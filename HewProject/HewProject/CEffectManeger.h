#pragma once
#include "CObject.h"
#include <list>

class Vector3;

class CEffect;

class EffectManeger: public CObject
{
public:

	typedef enum
	{
		EFFECT_UP=0,
		EFFECT_DOWN,
	}FX_TYPE;

private:
	std::list<CEffect*>EffectList;

public:


	void Play(Vector3 _pos , Vector3 _scale , FX_TYPE _type ,bool _isLoop);

	void Draw();

	void Update();

};

