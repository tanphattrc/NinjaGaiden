#include "WindmillStar.h"






WindmillStar::WindmillStar(D3DXVECTOR3 position, float posStop)
{
	this->_itemName = "WindmillStar";
	Init(position, posStop, _itemName);

	this->TagItem = Entity::ItemType::WindmillStar;
}

WindmillStar::~WindmillStar()
{
}
