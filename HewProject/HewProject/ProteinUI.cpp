#include "ProteinUI.h"
#include "TextureFactory.h"

ProteinUI::ProteinUI(const int& _proteinNum)
{
	TextureFactory* texFactory = TextureFactory::GetInstance();
	// ���̃X�e�[�W�ɂ���v���e�C���擾
	stageProMax = _proteinNum;


}

ProteinUI::~ProteinUI()
{
}

void ProteinUI::Draw()
{
}
