#pragma once

#include"Vector2.h"

// �O���b�h�i�}�X�ځj�Ɋւ��ẴN���X
class CGrid
{
public:
	struct GRID_XY
	{
		int x, y;
	};

private:
	GRID_XY gridPos;

public:
	// �O���b�h���W�ɑ������
	void SetGridPos(Vector2 _p);
	GRID_XY GetGridPos()const { return gridPos; }
};

