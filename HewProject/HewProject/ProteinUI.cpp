#include "ProteinUI.h"
#include "TextureFactory.h"

ProteinUI::ProteinUI(const int& _proteinNum)
{
	TextureFactory* texFactory = TextureFactory::GetInstance();
	// このステージにあるプロテイン取得
	stageProMax = _proteinNum;


}

ProteinUI::~ProteinUI()
{
}

void ProteinUI::Draw()
{
}
