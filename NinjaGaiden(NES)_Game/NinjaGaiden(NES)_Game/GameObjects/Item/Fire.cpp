#include "Fire.h"






Fire::Fire(D3DXVECTOR3 position, float posStop)
{
	this->_itemName = "Fire";
	Init(position, posStop, _itemName);

	this->TagItem = Entity::ItemType::Fire;
}

Fire::~Fire()
{
}
