#include "CEffectManeger.h"
#include "Vector3.h"

//======???????????????======//
typedef struct
{
	bool aLoop;			// trueでループ。通常BGMはture、SEはfalse。
} TEST;

TEST test[3] //??
{
	{"BGM/kawada/doen.png"},
	{"BGM/kawada/up.png"},
};


void EffectManeger::Play(Vector3 _pos, Vector3 _scale, FX_TYPE _type, bool _isLoop)
{

}
