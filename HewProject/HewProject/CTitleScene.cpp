#include "CTitleScene.h"
#include "CSceneManager.h"
#include "CInput.h"
#include "UI.h"
#include "TextureFactory.h"

CTitleScene::CTitleScene()
{
	D3D_CreateSquare({ 1,1 }, &sweetsBuffer);
	sweetsTexture = TextureFactory::GetInstance()->Fetch(L"asset/Item/Cake.png");

	for (int i = 0; i < MAXNUM; i++)
	{
		Sweets[i] = new UI(sweetsBuffer, sweetsTexture);
		Sweets[i]->mTransform.pos = {-1 + i * 0.5f,1.5f,0};
		Sweets[i]->mTransform.scale = {1,1,1};
		Sweets[i]->materialDiffuse = {1,1,1,1};
	}

	D3D_CreateSquare({ 1,1 }, &titleBuffer);
	titleTexture = TextureFactory::GetInstance()->Fetch(L"asset/UI/Title.png");

	Title = new UI(titleBuffer,titleTexture);
	Title->MakeDotween();
	Title->mTransform.pos = { 0,1.5f,0 };
	Title->mTransform.scale = { 1,1,1 };
	Title->materialDiffuse = { 1,1,1,1 };

	isNoMoving = false;
	isOnce = false;
	isRotationSwitch = false;
}

CTitleScene::~CTitleScene()
{
	CLASS_DELETE(Title);

	for (int i = 0; i < MAXNUM; i++)
	{
		CLASS_DELETE(Sweets[i]);
	}
}

void CTitleScene::Update()
{
	Title->Update();

	if (isNoMoving == false)
	{
		if (isOnce == false)
		{
			Title->dotween->DoMoveY(0.5f, 2.0f);
			//Title->dotween->Append(Vector3::zero, 2.0f, DoTweenUI::FUNC::SCALE);
			isOnce = true;
		}

		Title->dotween->OnComplete([&]()
			{
				isNoMoving = true;
			});

	}
	else {
		
		if (isRotationSwitch == false)
		{
			Title->mTransform.rotation.z += 1.0f;
			if (Title->mTransform.rotation.z > 45.0f)
			{
				isRotationSwitch = true;
			}
		}
		else
		{
			Title->mTransform.rotation.z -= 1.0f;
			if (Title->mTransform.rotation.z < -45.0f)
			{
				isRotationSwitch = false;
			}
		}

		//Title->mTransform.rotation.z += 1.0f;
		if (gInput->GetKeyTrigger(VK_RETURN))
		{
			CScene::SetScene(SCENE_NAME::WAKAMURA);
		}
	}
}

void CTitleScene::LateUpdate()
{
}

void CTitleScene::Draw()
{
	Title->Draw();
}
