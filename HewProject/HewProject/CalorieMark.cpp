#include "CalorieMark.h"
#include "TextureFactory.h"

#define ONEMARK_DEGREE_OFFSET (360.0f / MARKNUM_MAX)	// ��ڐ��育�Ƃ̊p�x�̍���

CalorieMark::CalorieMark()
{
	// �e�N�X�`���A�o�b�t�@�쐬
	markTex = TextureFactory::GetInstance()->Fetch(L"asset/UI/gage.png");
	D3D_CreateSquare({ 1,1 }, &markBuffer);

	// �ڐ�����ő吔���A�쐬
	for (int i = 0; i < MARKNUM_MAX; i++)
	{
		mark[i] = new UI(markBuffer, markTex);

		// �ڐ��育�ƂɊp�x��ݒ肷��
		mark[i]->mTransform.rotation.z = i * ONEMARK_DEGREE_OFFSET;

		// �ڐ��育�Ƃ̍��W���ݒ肷��
		// X���W
		mark[i]->mTransform.pos.x = this->mTransform.pos.x + cos(DirectX::XMConvertToRadians(i * ONEMARK_DEGREE_OFFSET));

		// Y���W
		mark[i]->mTransform.pos.y = this->mTransform.pos.y + sin(DirectX::XMConvertToRadians(i * ONEMARK_DEGREE_OFFSET));

	
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
