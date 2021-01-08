#include "RedBonus.h"






RedBonus::RedBonus(D3DXVECTOR3 position, float posStop)
{
	this->_itemName = "RedBonus";
	Init(position, posStop, _itemName);

	this->TagItem = Entity::ItemType::RedBonus;
}

RedBonus::~RedBonus()
{
}
