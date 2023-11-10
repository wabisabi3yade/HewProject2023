#include "Collision.h"

bool CollsionCircle(CObject _obj1, CObject _obj2)
{
	Vector3 dis = _obj1.mTransform.pos - _obj2.mTransform.pos;
	float syahen = dis.x * dis.x + dis.y * dis.y;
	float decision = _obj1.mTransform.scale.x / 2.0f + _obj2.mTransform.scale.x / 2;

	return syahen <= decision * decision;
}
bool CollsionCircle(const Transform& _obj1, const Transform& _obj2)
{
	Vector3 dis = _obj1.pos - _obj2.pos;
	float syahen = dis.x * dis.x + dis.y * dis.y;
	float decision = _obj1.scale.x / 2.0f + _obj2.scale.x / 2;

	return syahen <= decision * decision;
}
bool CollsionRect(CObject _obj1, CObject _obj2)
{
	if (_obj1.mTransform.pos.x + _obj1.mTransform.scale.x / 2 >= _obj2.mTransform.pos.x - _obj2.mTransform.scale.x / 2 &&
		_obj2.mTransform.pos.x + _obj2.mTransform.scale.x / 2 >= _obj1.mTransform.pos.x - _obj2.mTransform.scale.x / 2 &&
		_obj1.mTransform.pos.y + _obj1.mTransform.scale.y / 2 >= _obj2.mTransform.pos.y - _obj2.mTransform.scale.y / 2 &&
		_obj2.mTransform.pos.y + _obj2.mTransform.scale.y / 2 >= _obj1.mTransform.pos.y - _obj2.mTransform.scale.y / 2)
	{
		return true;
	}
	return false;
}
