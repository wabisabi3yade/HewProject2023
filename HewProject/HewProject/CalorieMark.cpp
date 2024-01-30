#include "CalorieMark.h"
#include "TextureFactory.h"

#define ONEMARK_DEGREE_OFFSET (360.0f / MARKNUM_MAX)	// ��ڐ��育�Ƃ̊p�x�̍���
#define OFFSET_MARK_POSZ (0.0001f)	// 1�ڐ��育�Ƃ�Z���W�̍���

CalorieMark::CalorieMark()
{
	mTransform.scale = Vector3::one;

	// �e�N�X�`���A�o�b�t�@�쐬
	markTex = TextureFactory::GetInstance()->Fetch(L"asset/UI/gage.png");
	D3D_CreateSquare({ 1,1 }, &markBuffer);

	// �ڐ�����ő吔���A�쐬
	for (int i = 0; i < MARKNUM_MAX; i++)
	{
		mark[i] = new UI(markBuffer, markTex);

		mark[i]->mTransform.scale.x = mTransform.scale.x;
		mark[i]->mTransform.scale.y = mTransform.scale.y;

		// �ڐ��育�ƂɊp�x��ݒ肷��
		mark[i]->mTransform.rotation.z = i * ONEMARK_DEGREE_OFFSET;

	}
}

CalorieMark::~CalorieMark()
{
	SAFE_RELEASE(markBuffer);

	for (int i = 0; i < MARKNUM_MAX; i++)
	{
		CLASS_DELETE(mark[i]);
	}
}

void CalorieMark::Update()
{
}

void CalorieMark::Draw()
{
	for (int i = 0; i < MARKNUM_MAX; i++)
	{
		mark[i]->Draw();
	}
}

void CalorieMark::SetPosition(const Vector3& _setPos)
{
	const Vector3& scWork = this->mTransform.scale;

	// ���W��ݒ肷��
	mTransform.pos = _setPos;

	// �ڐ�����ő吔���A�쐬
	for (int i = 0; i < MARKNUM_MAX; i++)
	{
		const float startDegree = 90.0f;
		float radWork = DirectX::XMConvertToRadians(startDegree + i * ONEMARK_DEGREE_OFFSET);
		// ���W
		mark[i]->mTransform.pos.x = this->mTransform.pos.x + (scWork.x * baseRadius)
			* cos(radWork);

		mark[i]->mTransform.pos.y = this->mTransform.pos.y + (scWork.y * baseRadius)
			* sin(radWork);

		mark[i]->mTransform.pos.z = this->mTransform.pos.z - i * OFFSET_MARK_POSZ;
	}
}

void CalorieMark::SetScale(const Vector3& _setScale)
{
	// �S�̂̑傫����ݒ肷��
	this->mTransform.scale = _setScale;

	// ��Ɨp�ϐ�
	const Vector2 radiusWork = { this->mTransform.scale.x * baseRadius ,  this->mTransform.scale.y * baseRadius };	 // ���a�̑傫��

	// �ڐ�����ő吔���A�쐬
	for (int i = 0; i < MARKNUM_MAX; i++)
	{
		// �X�P�[���ݒ肷��
		mark[i]->mTransform.scale.x = this->mTransform.scale.y;
		mark[i]->mTransform.scale.y = this->mTransform.scale.y;

		const float startDegree = 90.0f;
		float radWork = DirectX::XMConvertToRadians(startDegree + i * ONEMARK_DEGREE_OFFSET);

		// ���W���ݒ肷��
		mark[i]->mTransform.pos.x = this->mTransform.pos.x +
			(this->mTransform.scale.x * radiusWork.x) * cos(radWork);
		mark[i]->mTransform.pos.y = this->mTransform.pos.y +
			(this->mTransform.scale.y * radiusWork.y) * sin(radWork);
	}
}
