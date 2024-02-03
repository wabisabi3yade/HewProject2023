#include "ProteinUI.h"
#include "TextureFactory.h"

#define UI_OFFSETZ (0.0001f)	// UI��Z�l����

#define CIRCLE_OFFSETX (1.0f)	// �Z���m��X���W����
#define CIRCLE_OFFSETY (0.5f)	// �_����Z��Y���W����

#define PRO_ADJUST_Y (0.2f)	// �v���e�C��Y���W����
#define PRO_SCALETIME (1.3f)	// �傫���Ȃ�܂ł̎���
ProteinUI::ProteinUI(const int& _proteinNum)
{
	// �S�̂̍��W�������Őݒ�
	mTransform.pos = {};

	TextureFactory* texFactory = TextureFactory::GetInstance();
	// ���̃X�e�[�W�ɂ���v���e�C���擾
	stageProMax = _proteinNum;

	D3D_CreateSquare({ 1,1 }, &buffer);
	D3DTEXTURE texWork;
	// �Z��UI
	texWork = texFactory->Fetch(L"asset/UI/Protein_Mark.png");
	for (int i = 0; i < stageProMax; i++)
	{
		circle[i] = new UI(buffer, texWork);
		circle[i]->mTransform.scale = { 0.4f, 0.4f, 1.0f };
	}

	// �v���e�C��
	texWork = texFactory->Fetch(L"asset/Item/Protein.png");
	for (int i = 0; i < stageProMax; i++)
	{
		protein[i] = new UI(buffer, texWork);
		protein[i]->mTransform.scale = proScale;
		protein[i]->MakeDotween();
	}

	// ���̖_
	texWork = texFactory->Fetch(L"asset/UI/Protein_Bar.png");
	bar = new UI(buffer, texWork);
	bar->mTransform.scale = { 3.0f, 0.2f, 1.0f };

	SetPosition(mTransform.pos);
}

ProteinUI::~ProteinUI()
{
	SAFE_RELEASE(buffer);

	for (int i = 0; i < stageProMax; i++)
	{
		CLASS_DELETE(circle[i]);
	}
	for (int i = 0; i < stageProMax; i++)
	{
		CLASS_DELETE(protein[i]);
	}
	CLASS_DELETE(bar);
}

void ProteinUI::Update()
{
	for (int i = 0; i < stageProMax; i++)
	{
		protein[i]->Update();
	}
}

void ProteinUI::SetProtein(const int& _getProtein)
{
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
		circle[roop]->SetActive(false);
		// �v���e�C���͕\��
		protein[roop]->SetActive(true);
		protein[roop]->mTransform.scale = proScale;
	}
	// �擾���Ă��Ȃ�UI���f
	for (; roop < stageProMax; roop++)
	{
		circle[roop]->SetActive(true);

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
	//�傫������
	protein[n]->mTransform.scale = { 0.0f, 0.0f, 1.0f };
	protein[n]->dotween->DoEaseElasticScale(proScale, PRO_SCALETIME);
	protein[n]->dotween->OnComplete([&]()
		{
			// �΍�
			if (n + 1 <= getProtein)
				circle[n]->SetActive(false);
		});
}

void ProteinUI::Draw()
{
	bar->Draw();

	for (int i = 0; i < stageProMax; i++)
	{
		circle[i]->Draw();
	}

	for (int i = 0; i < stageProMax; i++)
	{
		protein[i]->Draw();
	}
}

void ProteinUI::SetPosition(const Vector3& _pos)
{
	mTransform.pos = _pos;

	bar->mTransform.pos = _pos;

	switch (stageProMax)
	{
	case 1:
		circle[0]->mTransform.pos.x = _pos.x;
		break;

	case 2:
		circle[0]->mTransform.pos.x = _pos.x - CIRCLE_OFFSETX / 2;
		circle[1]->mTransform.pos.x = _pos.x + CIRCLE_OFFSETX / 2;
		break;

	case 3:
		circle[0]->mTransform.pos.x = _pos.x - CIRCLE_OFFSETX;
		circle[1]->mTransform.pos.x = _pos.x;
		circle[2]->mTransform.pos.x = _pos.x + CIRCLE_OFFSETX;
		break;
	}

	for (int i = 0; i < stageProMax; i++)
	{
		circle[i]->mTransform.pos.y = _pos.y + CIRCLE_OFFSETY;
		circle[i]->mTransform.pos.z = _pos.z - i * UI_OFFSETZ;

		protein[i]->mTransform.pos = circle[i]->mTransform.pos;
		protein[i]->mTransform.pos.y += PRO_ADJUST_Y;
		protein[i]->mTransform.pos.z -= UI_OFFSETZ;
	}
}