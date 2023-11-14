#include "CEffectManeger.h"
#include "Vector3.h"
//#include "CObject.h"
EffectManeger* EffectManeger::instance = nullptr;

//======???????????????======//
typedef struct
{
	bool aLoop;			// true�Ń��[�v�B�ʏ�BGM��ture�ASE��false�B
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

//==============�f�X�X�g���N�^==============//
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
// �V�[���}�l�[�W���[���擾
// ���߂ČĂяo���ꂽ��C���X�^���X�𐶐�
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
	//���[�v�����邩���߂�(false�Ȃ烋�[�v)
	/*charObj->GetmAnim().SetEffectLoop(_isLoop);*/
	//�G�t�F�N�g�傫��
	charObj->mTransform.scale = _scale;
	//�G�t�F�N�g�ʒu
	charObj->mTransform.pos = _pos;

	//Effectlist��charObj��ǉ�
	EffectList.push_back(charObj);
}

void EffectManeger::Draw()
{
	//list�̍ŏ��̒l���擾;	list�Ō�̒l����Ȃ��ꍇ���s;	�l��1�ǉ�
	for (std::list<CEffect*>::iterator eit = EffectList.begin(); eit != EffectList.end(); eit++)
	{
		//CEffect��Draw�����s
		(*eit)->Draw();
	}
}

//list�̒��g��update����
void EffectManeger::Update()
{
	//list�̍ŏ��̒l���擾;	list�Ō�̒l����Ȃ��ꍇ���s;	�l��1�ǉ�
	for (std::list<CEffect*>::iterator eit = EffectList.begin(); eit != EffectList.end(); eit++)
	{
		//CEffect��Update�����s
		(*eit)->Update();
	}
}

void EffectManeger::Delete()
{
	CLASS_DELETE(instance);
}
