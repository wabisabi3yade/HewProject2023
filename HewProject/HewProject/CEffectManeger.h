#pragma once
#include "CObject.h"
#include <list>
#include"CEffect.h"
class Vector3;

//class CEffect;

class EffectManeger //public CObject
{
	
public:
	
	typedef enum
	{
		EFFECT_UP=0,
		EFFECT_DOWN,
		EFFECT_MAX,
	}FX_TYPE;

private:
	std::list<CEffect*>EffectList;

	D3DBUFFER charBuffer;
	D3DTEXTURE charTexture;
	CEffect* charObj;

	static EffectManeger* instance;

	//コンストラクタ
	EffectManeger();

	//デスストラクタ
	~EffectManeger();
public:

	D3DTEXTURE EffectBox[EFFECT_MAX];

	static EffectManeger* GetInstance();

	void Play(Vector3 _pos , Vector3 _scale , FX_TYPE _type ,bool _isLoop);

	void Draw();

	void Update();

	void Delete();
};

