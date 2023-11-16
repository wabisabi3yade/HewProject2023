#pragma once
#include "CObject.h"

class CItem:public CObject
{
public:
	float calorie;

public:
	
	//コンストラクタ
	CItem(D3DBUFFER vb, D3DTEXTURE tex, float valcalorie);

	//デストラクタ
	~CItem();

	//描画
	void Draw();

	//更新
	void Update();

	//Get関数
	float GetCalorie()const;

	//一応、触れた時の処理出来るとこ
	//void touch();


};

