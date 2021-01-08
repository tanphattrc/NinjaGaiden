#include "BlueMana.h"

BlueMana::BlueMana(D3DXVECTOR3 position, float posStop)  
{
	this->_itemName = "BlueMana";
	Init(position, posStop, _itemName);
	
	this->TagItem = Entity::ItemType::BlueMana;
}





BlueMana::~BlueMana()
{
}
