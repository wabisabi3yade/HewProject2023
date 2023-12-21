#include "CEffectManeger.h"
#include "Vector3.h"
//#include "CObject.h"
EffectManeger* EffectManeger::instance = nullptr;

//======???????????????======//
typedef struct
{
	bool aLoop;			// true�Ń��[�v�B�ʏ�BGM��ture�ASE��false�B
} Effect;

EffectManeger::EffectManeger()
{
	std::vector<const wchar_t*> effectTexPath{
		L"asset/kawada/Red_Slash.png",
		L"asset/kawada/bullets.png",
		L"asset/kawada/Red_Slash.png",
	};

	// �摜�����[�h���ăe�N�X�`���̔z��ɓ����
	for (int i = 0; i < effectTexPath.size(); i++)
	{
		effectTexBox.push_back(0);
		D3D_LoadTexture(effectTexPath[i], &effectTexBox[i]);
	}

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
		SAFE_RELEASE(effectTexBox[i]);
	}

	// �G�t�F�N�g�����
	for (auto itr = EffectList.begin(); itr != EffectList.end(); itr++)
	{
		CLASS_DELETE((*itr));
	}
	EffectList.clear();
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
	// �e�N�X�`���̃p�X�̎�ސ����������@�܂��́@���̒l�@�Ȃ�
	if ((int)_type > effectTexBox.size() - 1 || (int)_type < 0)
	{
		MessageBoxA(NULL, "�G�t�F�N�g�}�l�[�W���[Play�֐��Ŏw��ł��Ȃ��e�N�X�`���ԍ��ł�", "�G���[", MB_ICONERROR | MB_OK);

		return;
	}

	charObj = new CEffect(charBuffer, effectTexBox[_type]);

	//���[�v�����邩���߂�(false�Ȃ烋�[�v)
	charObj->GetmAnim()->SetEffectLoop(_isLoop);
	//�G�t�F�N�g�傫��
	charObj->mTransform.scale = _scale;
	//�G�t�F�N�g�ʒu
	charObj->mTransform.pos = _pos;

	charObj->GetmAnim()->animSpeed = 0.3f;

	//Effectlist��charObj��ǉ�
	EffectList.push_back(charObj);
}

void EffectManeger::Draw()
{
	//list�̍ŏ��̒l���擾;	list�Ō�̒l����Ȃ��ꍇ���s;	�l��1�ǉ�
	for (auto itr = EffectList.begin(); itr != EffectList.end(); itr++)
	{
		//CEffect��Draw�����s
		(*itr)->Draw();
	}
}

//list�̒��g��update����
void EffectManeger::Update()
{
	//list�̍ŏ��̒l���擾;	list�Ō�̒l����Ȃ��ꍇ���s;
	for (auto itr = EffectList.begin(); itr != EffectList.end();)
	{
		//CEffect��Update�����s
		(*itr)->Update();

		// �Đ����I������Ȃ�폜����
		if (!(*itr)->GetIsPlaying())
		{
			delete *itr;

			// ���X�g����폜����
			itr = EffectList.erase(itr);

			continue;
		}

		// ���ɐi�߂�
		itr++;
	}
}

void EffectManeger::Delete()
{
	CLASS_DELETE(instance);
}
