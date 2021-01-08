#include "RedHP.h"





RedHP::RedHP(D3DXVECTOR3 position, float posStop)
{
	this->_itemName = "RedHP";
	Init(position, posStop, _itemName);

	this->TagItem = Entity::ItemType::RedHP;
}

RedHP::~RedHP()
{
}
