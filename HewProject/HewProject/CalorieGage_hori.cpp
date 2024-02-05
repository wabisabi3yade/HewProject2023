#include "CalorieGage_hori.h"
#include "TextureFactory.h"
#include "CalorieMark.h"

#define GAGEUI_OFFSET_Z	 (0.0001f) // �Q�[�W��UI��Z���W�̍���

#define ROGO_OFFSET_X (-3.23f)	// �Q�[�W�S�̂���̃��S��X���W
#define ROGO_OFFSET_Y (0.2f)	// �Q�[�W�S�̂���̃��S��Y���W

#define NUMBER_OFFSETX (0.3f)	// ���S�̒��S����̋���
#define NUMBER_OFFSETY (-0.1f)	// ���S�̒��S����̋���

#define MARK_BEGIN_OFFSET_X (-2.0f)	// 1�ڐ���ڂ�X���W
#define MARKTO_OFFSET_X (0.32f)	// �ڐ��蓯�m��X���W����
#define YELLOW_RATIO (1.0f / 3)	// �Q�[�W�S�̂��猩�����F�̊���
#define GREEN_RATIO (2.0f / 3)	// �Q�[�W�S�̂��猩���ΐF�̊���
#define MARK_SCALETIME (0.75f)	// �ڐ���傫���Ȃ鎞��
CalorieGage_hori::CalorieGage_hori()
{
	// ������
	mTransform.pos = {};
	mTransform.scale = { 1,1,1 };
	mTransform.rotation = {};

	TextureFactory* texFactory = TextureFactory::GetInstance();

	// �e�N�X�`�����擾�����Ɨp�ϐ�
	D3DTEXTURE texWork;

	D3D_CreateSquare({ 1,1 }, &oneBuffer);

	const Vector3& basePos = mTransform.pos;

	// �Q�[�W�w�i
	texWork = texFactory->Fetch(L"asset/UI/Gage_Back.png");
	back = new UI(oneBuffer, texWork);
	back->SetAlpha(0.6f);

	// ���S
	texWork = texFactory->Fetch(L"asset/UI/Gage_Rogo.png");
	rogo = new UI(oneBuffer, texWork);

	D3D_CreateSquare({ 3,4 }, &numBuffer);
	texWork = texFactory->Fetch(L"asset/UI/Calorie_Number.png");
	for (int i = 0; i < calorieDigits; i++)
	{
		number[i] = new UI(numBuffer, texWork);
	}

	// �ڐ���̏�����
	texWork = texFactory->Fetch(L"asset/UI/Carorie_Mark.png");
	D3D_CreateSquare({ 3,1 }, &markBuffer);
	// �ő吔���쐬����
	for (int i = 0; i < MARKNUM_MAX; i++)
	{
		mark[i] = new CalorieMark(markBuffer, texWork);
		mark[i]->MakeDotween();

		//�@�ΐF
		if (i >= MARKNUM_MAX * GREEN_RATIO)
		{
			mark[i]->SetColor(CalorieMark::GREEN);
		}
		// ���F
		else if(i >= MARKNUM_MAX * YELLOW_RATIO)
		{
			mark[i]->SetColor(CalorieMark::YELLOW);
		}
	}

	// UI����ׂ�
	SetPosition(mTransform.pos);
	SetScale(mTransform.scale);

	// �ڐ���������J�����[�ɔ��f������
	SetCalorie(calorieNum, false);

}

CalorieGage_hori::~CalorieGage_hori()
{
	SAFE_RELEASE(markBuffer);
	SAFE_RELEASE(oneBuffer);
	SAFE_RELEASE(numBuffer);

	for (int i = 0; i < MARKNUM_MAX; i++)
	{
		CLASS_DELETE(mark[i]);
	}
	for (int i = 0; i < calorieDigits; i++)
	{
		CLASS_DELETE(number[i]);
	}
	CLASS_DELETE(rogo);
	CLASS_DELETE(back);
}

void CalorieGage_hori::Update()
{
	for (int i = 0; i < MARKNUM_MAX; i++)
	{
		mark[i]->Update();
	}
}

void CalorieGage_hori::Draw()
{
	// �w�i�̕`��
	back->Draw();

	// ���S�̕`��
	rogo->Draw();

	// �����̕`��
	for (int i = 0; i < calorieDigits; i++)
	{
		number[i]->Draw();
	}

	

	// �ڐ���̕`��
	for (int i = 0; i < MARKNUM_MAX; i++)
	{
		mark[i]->Draw();
	}
}

void CalorieGage_hori::SetPosition(const Vector3& _pos)
{
	mTransform.pos = _pos;

	// UI�S�Ă��ς���
	const Vector3& basePos = mTransform.pos;
	const Vector3& baseScale = mTransform.scale;

	back->mTransform.pos = basePos;
	back->mTransform.pos.z = basePos.z;

	rogo->mTransform.pos.x = basePos.x + baseScale.x * ROGO_OFFSET_X;
	rogo->mTransform.pos.y = basePos.y + baseScale.y * ROGO_OFFSET_Y;
	rogo->mTransform.pos.z = basePos.z - GAGEUI_OFFSET_Z;

	// ����UI�̐ݒ�
	NumUISetting();

	// �߂���
	for (int i = 0; i < MARKNUM_MAX; i++)
	{
		mark[i]->mTransform.pos.x = basePos.x + baseScale.x * MARK_BEGIN_OFFSET_X;
		mark[i]->mTransform.pos.x += i * baseScale.x * MARKTO_OFFSET_X;
		mark[i]->mTransform.pos.y = basePos.y;
		mark[i]->mTransform.pos.z = basePos.z - (i + 1) * GAGEUI_OFFSET_Z;
	}
}

void CalorieGage_hori::SetScale(const Vector3& _scale)
{
	// �傫����ς���
	mTransform.scale = _scale;

	// UI�S�Ă��ς���
	const Vector3& basePos = mTransform.pos;


	// �X�P�[���𔽉f������
	back->mTransform.scale = _scale * backScale;

	rogo->mTransform.pos.x = basePos.x + _scale.x * ROGO_OFFSET_X;
	rogo->mTransform.pos.y = basePos.y + _scale.y * ROGO_OFFSET_Y;
	rogo->mTransform.scale = _scale * rogoScale;
	// �X�P�[����Z�͌Œ�
	rogo->mTransform.scale.z = 1.0f;

	// ����UI�̐ݒ�
	NumUISetting();

	// �߂���
	for (int i = 0; i < MARKNUM_MAX; i++)
	{
		mark[i]->mTransform.pos.x = basePos.x + _scale.x * MARK_BEGIN_OFFSET_X;
		mark[i]->mTransform.pos.x += i * _scale.x * MARKTO_OFFSET_X;
		mark[i]->mTransform.scale = _scale * markScale;
		mark[i]->mTransform.scale.z = 1.0f;
	}
}

void CalorieGage_hori::SetCalorie(const short& _set, bool action)
{
	// ������O�̃J�����[
	const short o_num = calorieNum;

	// �������
	calorieNum  = _set;
	if (calorieNum > MARKNUM_MAX)
	{
		calorieNum = MARKNUM_MAX;
	}
	else if (calorieNum < 0)
	{
		calorieNum = 0;
	}

	// ������UI
	NumUISetting();

	// ���o����Ȃ�
	if (action)
	{
		// �ڐ���ɔ��f������
		MarkAdd(o_num, _set - o_num);
	}
	else
	{
		// �J�����[�̃Q�[�W�܂ŕ\��������
		int roop = 0;
		for (; roop < calorieNum; roop++)
		{
			// �\�������đ傫����ς���
			mark[roop]->SetActive(true);
			mark[roop]->mTransform.scale.x = mTransform.scale.x * markScale.x;
			mark[roop]->mTransform.scale.y = mTransform.scale.y * markScale.y;
		}
		
		for (; roop < MARKNUM_MAX; roop++)
		{
			mark[roop]->SetActive(false);
			mark[roop]->mTransform.scale.x = 0.0f;
			mark[roop]->mTransform.scale.y = 0.0f;
		}

	}
	
}

void CalorieGage_hori::AddCalorie(const short& _add)
{
	// ������O�̃J�����[
	const short o_num = calorieNum;

	// ����
	calorieNum += _add;
	if (calorieNum > MARKNUM_MAX)
	{
		calorieNum = MARKNUM_MAX;
	}
	else if (calorieNum < 0)
	{
		calorieNum = 0;
	}
	// ������UI
	NumUISetting();
	MarkAdd(o_num, _add);
}

void CalorieGage_hori::MarkAdd(const short& _oldNum, const short& _add)
{
	short targetValue = _oldNum + _add;

	// ������Ȃ�
	if (_add > 0)
	{
		for (short i = _oldNum; i < targetValue; i++)
		{
			if (i >= MARKNUM_MAX) break;

			mark[i]->SetActive(true);
			mark[i]->mTransform.scale.x = 0.0f;
			mark[i]->mTransform.scale.y = 0.0f;
			// �ڕW�̑傫��
			Vector3 target = mTransform.scale * markScale;
			target.z = 1.0f;
			mark[i]->dotween->DoEaseOutBackScale(target, MARK_SCALETIME);
		}
	}
	// ����Ȃ�
	else
	{
		for(short i = _oldNum; i > targetValue; i--)
		{
			if (i <= 0) break;

			// �ڕW�̑傫��
			mark[i - 1]->dotween->DoEaseInBackScale(Vector3::zero , MARK_SCALETIME);
			mark[i - 1]->dotween->OnComplete([&, i]()
				{
					mark[i - 1]->SetActive(false);
					
					// ���炵����ɑ��₷�Ǝ��ԍ��Ŕ�\���ɂȂ��Ă��܂��̂ő΍�
					if (i <= calorieNum)
					mark[i - 1]->SetActive(true);
					
				});
		}
	}
}

void CalorieGage_hori::NumUISetting()
{
	const Vector3& baseScale = mTransform.scale;

	// ����
	// 2�������Ȃ烍�S�̒��S�ɃZ�b�g����
	if (calorieNum < 10)
	{
		number[0]->mTransform.pos.x = rogo->mTransform.pos.x;
		number[1]->SetActive(false);

	}
	// 2���Ȃ璆�S���炸�炷�悤�ɂ���
	else
	{
		number[0]->mTransform.pos.x = rogo->mTransform.pos.x + baseScale.x * NUMBER_OFFSETX;
		number[1]->mTransform.pos.x = rogo->mTransform.pos.x - baseScale.x * NUMBER_OFFSETX;
		number[1]->SetActive(true);
	}

	DirectX::XMFLOAT3 rgb;
	// �F����
	if (calorieNum > MARKNUM_MAX * GREEN_RATIO)
	{
		rgb = { 89, 215, 98 };
	}
	else if (calorieNum > MARKNUM_MAX * YELLOW_RATIO)
	{
		rgb = { 255, 215, 0 };
	}
	else
	{
		rgb = { 252, 100, 100 };
	}

	for (int i = 0; i < calorieDigits; i++)
	{
		number[i]->mTransform.pos.y = rogo->mTransform.pos.y + NUMBER_OFFSETY;
		number[i]->mTransform.pos.z = rogo->mTransform.pos.z - (i + 1) * GAGEUI_OFFSET_Z;
		number[i]->mTransform.scale = baseScale * numScale;
		number[i]->mTransform.scale.z = 1.0f;
		number[i]->SetColor(rgb);
	}

	// UV���W�ݒ�
	number[1]->SetUV(1.0f / 3, 0.0f);
	// 1���̐��������߂�
	short oneDigitsNum = calorieNum % 10;
	number[0]->SetUV(oneDigitsNum % 3 * (1.0f / 3), oneDigitsNum / 3 * (1.0f / 4));
}
