#include "CEffectManeger.h"
#include "Vector3.h"
//#include "CObject.h"
EffectManeger* EffectManeger::instance = nullptr;

//======???????????????======//
typedef struct
{
	bool aLoop;			// trueでループ。通常BGMはture、SEはfalse。
} Effect;

Effect effect[10] //??
{
	{"BGM/kawada/down.png"},
	{"BGM/kawada/up.png"},
};


EffectManeger::EffectManeger()
{
	D3D_LoadTexture(L"BGM/kawada/down.png", &EffectBox[0]);
	D3D_LoadTexture(L"BGM/kawada/up.png", &EffectBox[1]);
	D3D_CreateSquare({ 3,4 }, &charBuffer);
}

//==============デスストラクタ==============//
EffectManeger::~EffectManeger()
{
	CLASS_DELETE(charObj);

	SAFE_RELEASE(charBuffer);

	SAFE_RELEASE(charTexture);

	for (int i = 0; i < EFFECT_MAX; i++)
	{
		SAFE_RELEASE(EffectBox[i]);
	}
}
// シーンマネージャーを取得
// 初めて呼び出されたらインスタンスを生成
EffectManeger* EffectManeger::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new EffectManeger();
	}

	return instance;
}
//------------------------------------------//
void EffectManeger::Play(Vector3 _pos, Vector3 _scale, FX_TYPE _type, bool _isLoop)
{
	charObj = new CEffect(charBuffer, EffectBox[_type]);

	charObj->SetTexture(EffectBox[_type]);
	//ループをするか決める(falseならループ)
	/*charObj->GetmAnim().SetEffectLoop(_isLoop);*/
	//エフェクト大きさ
	charObj->mTransform.scale = _scale;
	//エフェクト位置
	charObj->mTransform.pos = _pos;

	//EffectlistにcharObjを追加
	EffectList.push_back(charObj);
}

void EffectManeger::Draw()
{
	//listの最初の値を取得;	list最後の値じゃない場合続行;	値を1追加
	for (std::list<CEffect*>::iterator eit = EffectList.begin(); eit != EffectList.end(); eit++)
	{
		//CEffectのDrawを実行
		(*eit)->Draw();
	}
}

//listの中身をupdateする
void EffectManeger::Update()
{
	//listの最初の値を取得;	list最後の値じゃない場合続行;	値を1追加
	for (std::list<CEffect*>::iterator eit = EffectList.begin(); eit != EffectList.end(); eit++)
	{
		//CEffectのUpdateを実行
		(*eit)->Update();
	}
}

void EffectManeger::Delete()
{
	CLASS_DELETE(instance);
}
