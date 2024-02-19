#pragma once
#include"Transform.h"
#include"CObject.h"
#include "CStageSelectPlayer.h"
#include "CGridObject.h"
bool CollsionCircle(CObject, CObject);
bool CollsionCircle(const Transform&, const Transform&);
bool CollsionRect(CObject* _obj1, CObject* _obj2);

