#include "CTitleScene.h"
#include "CSceneManager.h"
#include "CInput.h"
#include "UI.h"
#include "TextureFactory.h"

CTitleScene::CTitleScene()
{
	D3D_CreateSquare({ 1,1 }, &titleBuffer);
	titleTexture = TextureFactory::GetInstance()->Fetch(L"asset/UI/textBox_Blue.png");

	Title = new UI(titleBuffer,titleTexture);
	Title->MakeDotween();
	Title->mTransform.pos = { 0,1,0 };
	Title->mTransform.scale = { 1 };
	Title->materialDiffuse = { 1,1,1,1 };
}

CTitleScene::~CTitleScene()
{
	CLASS_DELETE(Title);
}

void CTitleScene::Update()
{
	Title->Update();
}

void CTitleScene::LateUpdate()
{
}

void CTitleScene::Draw()
{
	Title->Draw();
}
