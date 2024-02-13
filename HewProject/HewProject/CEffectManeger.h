#pragma once
#include "CObject.h"
#include <list>
#include <vector>
#include"CEffect.h"
class Vector3;

//大きさの倍率

constexpr float CRACKSCALE = 1.5f;
constexpr float CANNON_IN_SCALE = 1.5f;
constexpr float CANNON_FIRE_SCALE = 1.5f;
constexpr float PANTI_SCALE = 1.5f;
constexpr float SMOKE_SCALE = 3.0f;
constexpr float HEART_SCALE = 1.8f;
constexpr float STAR_BOUND_SCALE = 1.5f;
constexpr float STAR_CASTELLA_SCALE = 1.5f;

//constexpr float
class EffectManeger //public CObject
{

public:

	typedef enum
	{
		EFFECT_UP = 0,
		EFFECT_DOWN,
		CHARE,
		CRACK,
		CANNON_IN,
		CANNON_FIRE,
		PANTI,
		SMOKE_R,
		SMOKE_G,
		SMOKE_Y,
		HEART,
		STAR_BOUND,
		STAR_CASTELLA,
		EFFECT_MAX,
	}FX_TYPE;

private:
	//std::list<CEffect*>EffectList;

	std::vector<D3DTEXTURE> effectTexBox;	// エフェクトのオブジェクトをまとめた配列

	/*std::vector<const wchar_t*> effectTexPath;*/	// エフェクト画像のパスが入ったリスト

	D3DBUFFER charBuffer;
	D3DTEXTURE charTexture;
	CEffect* charObj;

	static EffectManeger* instance;

	//コンストラクタ
	EffectManeger();

	//デスストラクタ
	~EffectManeger();
public:

	static EffectManeger* GetInstance();

	CEffect* Play(Vector3 _pos, Vector3 _scale, FX_TYPE _type, bool _isLoop);

	void Draw();

	void Update();

	static void Delete();

	int GetTexBoxSize()const { return static_cast<int>(effectTexBox.size()); };
};

