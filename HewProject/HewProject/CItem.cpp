#include "CItem.h"

//�R���X�g���N�^
CItem::CItem(D3DBUFFER vb, D3DTEXTURE tex, float valcalorie)
	: CObject(vb, tex), calorie(valcalorie)
{
}

//�f�X�g���N�^
CItem::~CItem()
{
}

//�`��
void CItem::Draw()
{
	CObject::Draw();
}

//�X�V
void CItem::Update()
{
	CObject::Update();
}

//Get�֐�
float CItem::GetCalorie() const
{
	return calorie;
}

//�G�ꂽ���̏���(��X)
/*void CItem::touch()
{
	//���炩�̏���
}*/
