#pragma once
#include "GridTable.h"
#include "Transform.h"

class DebugTable
{
	bool isFloorTable;
	GridTable* displayTable;

public: 
	Transform mTransform;

	DebugTable(GridTable* _table, bool _isFloorTable);

	void Update();

	void Draw();

	~DebugTable();

	void SetTable(GridTable* _table) { displayTable = _table; }
};

