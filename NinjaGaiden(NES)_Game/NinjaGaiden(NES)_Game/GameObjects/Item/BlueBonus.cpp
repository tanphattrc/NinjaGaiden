#include "BlueBonus.h"





BlueBonus::BlueBonus(D3DXVECTOR3 position, float posStop)
{
	this->_itemName = "BlueBonus";
	Init(position, posStop, _itemName);

	this->TagItem = Entity::ItemType::BlueBonus;
}

BlueBonus::~BlueBonus()
{
}
