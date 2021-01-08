#include "ThrowingStar.h"






ThrowingStar::ThrowingStar(D3DXVECTOR3 position, float posStop)
{
	this->_itemName = "ThrowingStar";
	Init(position, posStop, _itemName);

	this->TagItem = Entity::ItemType::ThrowingStar;
}

ThrowingStar::~ThrowingStar()
{
}
