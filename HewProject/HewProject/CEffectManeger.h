#pragma once
#include "CObject.h"
#include <list>
#include <vector>
#include"CEffect.h"
class Vector3;

constexpr float CRACKSCALE = 1.5f;
constexpr float CANNON_IN_SCALE = 1.5f;
constexpr float CANNON_FIRE_SCALE = 1.5f;

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
		EFFECT_MAX,
	}FX_TYPE;

private:
	//std::list<CEffect*>EffectList;

	std::vector<D3DTEXTURE> effectTexBox;	// �G�t�F�N�g�̃I�u�W�F�N�g���܂Ƃ߂��z��

	/*std::vector<const wchar_t*> effectTexPath;*/	// �G�t�F�N�g�摜�̃p�X�����������X�g

	D3DBUFFER charBuffer;
	D3DTEXTURE charTexture;
	CEffect* charObj;

	static EffectManeger* instance;

	//�R���X�g���N�^
	EffectManeger();

	//�f�X�X�g���N�^
	~EffectManeger();
public:

	static EffectManeger* GetInstance();

	CEffect* Play(Vector3 _pos, Vector3 _scale, FX_TYPE _type, bool _isLoop);

	void Draw();

	void Update();

	static void Delete();

	int GetTexBoxSize()const { return static_cast<int>(effectTexBox.size()); };
};

