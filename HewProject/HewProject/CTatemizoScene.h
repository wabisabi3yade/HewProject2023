#pragma once
#include "CScene.h"
#include "Ccontroller.h"
#include "CPlayer.h"

class CTatemizoScene :
	public CScene
{
public:
	D3DBUFFER charBuffer;
	D3DTEXTURE charTexture;
	CObject* charObj;

public:
	CTatemizoScene();

	~CTatemizoScene();

	void Update() override;

	void LateUpdate() override;

	void Draw() override;

private:
	CPlayer* player;  // CPlayer クラスのポインタをメンバーとして持つ
};

