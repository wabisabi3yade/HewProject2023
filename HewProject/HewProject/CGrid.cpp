#include "CGrid.h"

Vector2 CGrid::GridToWorldPos()
{
	return Vector2();
}

void CGrid::SetGridPos(Vector2 _p)
{
	// float�^��int�ɕϊ�����
	int x = (int)_p.x;
	int y = (int)_p.y;

	// �O���b�h���W�ɑ������
	gridPos = { x, y };
}
