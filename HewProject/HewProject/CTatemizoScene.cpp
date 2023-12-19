#include "CTatemizoScene.h"
#include "Ccontroller.h"

Input* gValue = new Input;

CTatemizoScene::CTatemizoScene()
{
	D3D_CreateSquare({ 3,4 }, &charBuffer);
	D3D_LoadTexture(L"asset/hashimoto/Char01.png", &charTexture);

	charObj = new CObject(charBuffer, charTexture);
	charObj->mTransform.scale = { 3.0f,3.0f,1.0f };
}

CTatemizoScene::~CTatemizoScene()
{
	CLASS_DELETE(charObj);

	SAFE_RELEASE(charBuffer);

	SAFE_RELEASE(charTexture);
}

void CTatemizoScene::Update()
{
    // 操作で設定する用のベクトル変数
    Vector3 d;

    // 方向なしベクトルに設定
    d.x = 0;
    d.y = 0;
    d.z = 0;

    // 移動速度を初めに０にする
    moveSpeed = 0.0f;

    dir = { 0,0,0 };

    //スティックの値で角度を判定して動かす
    CTatemizoScene::

	charObj->Update();
    // ベクトルを使って移動
    //charObj->SetMoveSpeed(moveSpeed);
    //pos.x = pos.x + dir.x * moveSpeed;
    //pos.y = pos.y + dir.y * moveSpeed;
    //pos.z = pos.z + dir.z * moveSpeed;
}

void CTatemizoScene::LateUpdate()
{
}

void CTatemizoScene::Draw()
{
	charObj->Draw();
}
