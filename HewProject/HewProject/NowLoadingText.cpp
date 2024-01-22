#include "NowLoadingText.h"
#include "TextureFactory.h"

NowLoadingText::NowLoadingText()
{
	// �o�b�t�@�쐬
	D3D_CreateSquare({ 3,4 }, &buffer);

	// �e�N�X�`���ǂ݂���
	TextureFactory* texFactory = TextureFactory::GetInstance();
	D3DTEXTURE texWork = texFactory->Fetch(L"asset/UI/NowLoading�c.png");
	// �e�L�X�g�쐬
	for (int i = 0; i < textNum; i++)
	{
		text[i] = new UI(buffer, texWork);
	};

	texWork = texFactory->Fetch(L"asset/UI/LoadCharacter.png");
	character = new UI(buffer, texWork);
}

NowLoadingText::~NowLoadingText()
{
	for (int i = 0; i < textNum; i++)
	{
		CLASS_DELETE(text[i]);
	}

	CLASS_DELETE(character);

	SAFE_RELEASE(buffer);
}

void NowLoadingText::SetTexText(D3DTEXTURE&& _tex)
{
	
}

void NowLoadingText::SetTexCharacter(D3DTEXTURE&& _tex)
{
	character->SetTexture(_tex);
}
