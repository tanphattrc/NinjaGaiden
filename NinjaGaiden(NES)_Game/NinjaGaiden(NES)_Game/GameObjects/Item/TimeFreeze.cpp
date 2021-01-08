#include "TimeFreeze.h"





TimeFreeze::TimeFreeze(D3DXVECTOR3 position, float posStop)
{
	this->_itemName = "TimeFreeze";
	Init(position, posStop, _itemName);

	this->TagItem = Entity::ItemType::TimeFreeze;
}

TimeFreeze::~TimeFreeze()
{
}
