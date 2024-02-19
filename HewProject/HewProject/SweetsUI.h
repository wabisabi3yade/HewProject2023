#pragma once

#include "UI.h"

class SweetsUI
{
	UI* Sweets;
public:
	
	bool isResporn;   //リスポーンフラグ
	bool isON;        //DoTween用フラグ

	float pos;     //落下地点
	float speed;   //何秒で落下するか

	Vector3 vCopy;   //リスポーン場所

	SweetsUI(D3DBUFFER _sweetsBuffer, D3DTEXTURE _sweetsTex);

	~SweetsUI();

	void Update();

	void Draw();

	//スケール設定
	void SetScale(const Vector3& _scale);

	//ポジション設定
	void SetPosition(const Vector3& _position);

	//回転設定
	void SetRotation(const Vector3& _rotation);

	//落下場所と秒設定
	void SetPosSpeed(const float _pos, const float _speed);

	//Z回転用
	void SetRotateZ(const float rotatez);

	//テクスチャをセット
	void SetTexture(const D3DTEXTURE _tex);
};

