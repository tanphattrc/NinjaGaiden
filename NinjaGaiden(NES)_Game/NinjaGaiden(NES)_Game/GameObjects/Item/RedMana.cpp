#include "RedMana.h"





RedMana::RedMana(D3DXVECTOR3 position, float posStop)
{
	this->_itemName = "RedMana";
	Init(position, posStop, _itemName);

	this->TagItem = Entity::ItemType::RedMana;
}

RedMana::~RedMana()
{
}
