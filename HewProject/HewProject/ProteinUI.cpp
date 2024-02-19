#include "ProteinUI.h"
#include "TextureFactory.h"

#define CIRCLE_OFFSETX (1.0f)	// �Z���m��X���W����
#define CIRCLE_OFFSETY (0.7f)	// �_����Z��Y���W����
#define PRO_SCALETIME (1.3f)	// �傫���Ȃ�܂ł̎���
ProteinUI::ProteinUI(const int& _proteinNum, bool _isMarkActive)
{
	isMarkActive = _isMarkActive;

	baseUI = new UI(NULL, NULL);
	baseUI->MakeDotween();
	baseUI->mTransform.pos = {};

	// �S�̂̍��W�������Őݒ�
	mTransform.pos = baseUI->mTransform.pos;

	TextureFactory* texFactory = TextureFactory::GetInstance();
	// ���̃X�e�[�W�ɂ���v���e�C���擾
	stageProMax = _proteinNum;

	D3D_CreateSquare({ 1,1 }, &buffer);
	D3DTEXTURE texWork;
	// �Z��UI
	texWork = texFactory->Fetch(L"asset/UI/Protein_Mark.png");
	for (int i = 0; i < stageProMax; i++)
	{
		proMark[i] = new UI(buffer, texWork);
		proMark[i]->mTransform.scale = proScale;
	}

	// �v���e�C��
	texWork = texFactory->Fetch(L"asset/Item/Protein.png");
	for (int i = 0; i < stageProMax; i++)
	{
		protein[i] = new UI(buffer, texWork);
		protein[i]->mTransform.scale = proScale;
		protein[i]->MakeDotween();
		/*protein[i]->SetActive(false);*/
	}

	// ���̖_
	texWork = texFactory->Fetch(L"asset/UI/Protein_Bar.png");
	bar = new UI(buffer, texWork);
	bar->mTransform.scale = barScale;

	SetPosition(mTransform.pos);

	SetProtein(0);
}

ProteinUI::~ProteinUI()
{
	SAFE_RELEASE(buffer);

	for (int i = 0; i < stageProMax; i++)
	{
		CLASS_DELETE(proMark[i]);
	}
	for (int i = 0; i < stageProMax; i++)
	{
		CLASS_DELETE(protein[i]);
	}
	CLASS_DELETE(bar);

	CLASS_DELETE(baseUI);
}

void ProteinUI::Update()
{
	for (int i = 0; i < stageProMax; i++)
	{
		protein[i]->Update();
	}

	baseUI->Update();
	mTransform.pos = baseUI->mTransform.pos;

	if (mTransform.pos != o_pos)
	{
		SetPosition(mTransform.pos);
	}
}

void ProteinUI::SetProtein(int _getProtein, bool _isDecade)
{
	if (_isDecade)
	{
		_getProtein = stageProMax - _getProtein;
	}

	if (_getProtein > stageProMax || _getProtein < 0)
	{
		MessageBoxA(NULL, "SetPritein�֐��̈������͈͊O�ł�", "�G���[", MB_ICONERROR | MB_OK);
		return;
	}

	// �擾���X�V
	getProtein = _getProtein;

	short roop = 0;
	// �擾�����v���e�C����UI���f
	for (; roop < _getProtein; roop++)
	{
		// �Z�͔�\��
		proMark[roop]->SetActive(false);
		// �v���e�C���͕\��
		protein[roop]->SetActive(true);
		protein[roop]->mTransform.scale.x = allScale.x * proScale.x;
		protein[roop]->mTransform.scale.y = allScale.y * proScale.y;
	}
	// �擾���Ă��Ȃ�UI���f
	for (; roop < stageProMax; roop++)
	{
		proMark[roop]->SetActive(true);

		protein[roop]->mTransform.scale = { 0.0f, 0.0f, 1.0f };
		protein[roop]->SetActive(false);
	}
}

void ProteinUI::AddProtein()
{
	// �v���e�C����1�擾
	getProtein++;

	// �X�e�[�W�ɂ���v���e�C���̐��𒴂�����
	if (getProtein > stageProMax)
	{
		MessageBoxA(NULL, "�v���e�C���̎擾�����X�e�[�W�ɂ���\n�v���e�C���擾���𒴂��܂���", "AddProtein�֐�", MB_ICONERROR | MB_OK);
		// �������킹��
		getProtein = stageProMax;
	}

	// �z��̗v�f��
	short n = getProtein - 1;
	// �v���e�C����\��������
	protein[n]->SetActive(true);
	proMark[n]->SetActive(false);
	//�傫������
	protein[n]->mTransform.scale = { 0.0f, 0.0f, 1.0f };

	Vector3 t = proScale;
	t.x *= allScale.x;
	t.y *= allScale.y;
	protein[n]->dotween->DoEaseElasticScale(t, PRO_SCALETIME);
}

void ProteinUI::Draw()
{
	if (isMarkActive)
	{
		bar->Draw();

		for (int i = 0; i < stageProMax; i++)
		{
			proMark[i]->Draw();
		}
	}
	

	for (int i = 0; i < stageProMax; i++)
	{
		protein[i]->Draw();
	}
}

void ProteinUI::SetPosition(const Vector3& _pos)
{
	baseUI->mTransform.pos = _pos;
	mTransform.pos = baseUI->mTransform.pos;

	bar->mTransform.pos = _pos;

	switch (stageProMax)
	{
	case 1:
		proMark[0]->mTransform.pos.x = _pos.x;
		break;

	case 2:
		proOffset = CIRCLE_OFFSETX / 2;
		proMark[0]->mTransform.pos.x = _pos.x - allScale.x * proOffset;
		proMark[1]->mTransform.pos.x = _pos.x + allScale.x * proOffset;
		break;

	case 3:
		proOffset = CIRCLE_OFFSETX;
		proMark[0]->mTransform.pos.x = _pos.x - allScale.x * proOffset;
		proMark[1]->mTransform.pos.x = _pos.x;
		proMark[2]->mTransform.pos.x = _pos.x + allScale.x * proOffset;
		break;
	}

	for (int i = 0; i < stageProMax; i++)
	{
		proMark[i]->mTransform.pos.z = _pos.z - i * UI_OFFSETZ;
		proMark[i]->mTransform.pos.y = _pos.y + allScale.y * CIRCLE_OFFSETY;
		protein[i]->mTransform.pos = proMark[i]->mTransform.pos;
		protein[i]->mTransform.pos.z -=  2 * UI_OFFSETZ;
	}
}

void ProteinUI::SetScale(const Vector2& _scale)
{
	allScale = _scale;

	// �g��
	for (int i = 0; i < stageProMax; i++)
	{
		proMark[i]->mTransform.scale.x = proScale.x * allScale.x;
		proMark[i]->mTransform.scale.y = proScale.y * allScale.y;
	}

	bar->mTransform.scale.x = barScale.x * allScale.x;
	bar->mTransform.scale.y = barScale.y * allScale.y;

	// ���W�X�V
	const Vector3& p = mTransform.pos;
	switch (stageProMax)
	{
	case 1:
		proMark[0]->mTransform.pos.x = p.x;
		break;

	case 2:
		proOffset = CIRCLE_OFFSETX / 2;
		proMark[0]->mTransform.pos.x = p.x - allScale.x * proOffset;
		proMark[1]->mTransform.pos.x = p.x + allScale.x * proOffset;
		break;

	case 3:
		proOffset = CIRCLE_OFFSETX / 2;
		proMark[0]->mTransform.pos.x = p.x - allScale.x * proOffset;
		proMark[1]->mTransform.pos.x = p.x;
		proMark[2]->mTransform.pos.x = p.x + allScale.x * proOffset;
		break;
	}

	for (int i = 0; i < stageProMax; i++)
	{
		proMark[i]->mTransform.pos.z = p.z - i * UI_OFFSETZ;
		proMark[i]->mTransform.pos.y = p.y + allScale.y *  CIRCLE_OFFSETY;
		protein[i]->mTransform.pos = proMark[i]->mTransform.pos;
		protein[i]->mTransform.pos.z -= 2 * UI_OFFSETZ;
	}
}

void ProteinUI::SetActive(bool _isActive)
{
	for (int i = 0; i < stageProMax; i++)
	{
		proMark[i]->SetActive(_isActive);
		protein[i]->SetActive(_isActive);;
	}

	bar->SetActive(_isActive);
}
