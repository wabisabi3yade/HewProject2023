#include "CItem.h"

//コンストラクタ
CItem::CItem(D3DBUFFER vb, D3DTEXTURE tex, float valcalorie)
	: CObject(vb, tex), calorie(valcalorie)
{
}

//デストラクタ
CItem::~CItem()
{
}

//描画
void CItem::Draw()
{
	CObject::Draw();
}

//更新
void CItem::Update()
{
	CObject::Update();
}

//Get関数
float CItem::GetCalorie() const
{
	return calorie;
}

//触れた時の処理(後々)
/*void CItem::touch()
{
	//何らかの処理
}*/
