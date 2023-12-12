#include "CTatemizoScene.h"
#include "CSceneManager.h"


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

    // キー操作で移動
    // キーが現在押されてるかを判定する　＝　キープレス
    if (gInput->GetKeyPress(VK_DOWN))
    {
        charObj->SetDir(Vector3::down);
        d.y = -1;// 下方向ベクトル
        moveSpeed = 0.01f;
    }
    if (gInput->GetKeyPress(VK_LEFT))
    {
        charObj->SetDir(Vector3::left);
        d.x = -1;// 左方向ベクトル
        moveSpeed = 0.01f;
    }
    if (gInput->GetKeyPress(VK_RIGHT))
    {
        charObj->SetDir(Vector3::right);
        d.x = 1;//右方向ベクトル
        moveSpeed = 0.01f;
    }
    if (gInput->GetKeyPress(VK_UP))
    {
        charObj->SetDir(Vector3::up);
        d.y = 1;// 上方向ベクトル
        moveSpeed = 0.01f;
    }

    // キー操作でベクトルが設定されていたらdirに代入する
    if (d.x != 0.0f || d.y != 0.0f)
    {
        dir = d;
    }

    //DirectX::XMVECTOR v = XMLoadFloat3(dirChange(this->dir));
    //v = DirectX::XMVector3Normalize(v);
    //XMStoreFloat3(dirChange(this->dir), v);

    // ベクトルを使って移動
    charObj->SetMoveSpeed(moveSpeed);
    pos.x = pos.x + dir.x * moveSpeed;
    pos.y = pos.y + dir.y * moveSpeed;
    pos.z = pos.z + dir.z * moveSpeed;

    charObj->Update();
}

void CTatemizoScene::LateUpdate()
{
}

void CTatemizoScene::Draw()
{
	charObj->Draw();
}
