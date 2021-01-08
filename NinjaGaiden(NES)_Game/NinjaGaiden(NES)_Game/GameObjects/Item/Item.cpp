#include "Item.h"

Item::Item()
{
}

void Item::Init(D3DXVECTOR3 position, float posStop, string itemName)
{
	_itemName = itemName;
	init(position);
	this->_Active = false;
	this->_posStop = posStop;
	this->TagItem = Entity::ItemType::Container;
}

void Item::OnCollision()
{
	_Active = true;
	_allowPlayerpick = true;
}
void Item::Update(float dt)
{
	if (_Active)
	{
		vy += 1000 * dt;
	}
	if (posY >= _posStop)
	{
		vy = 0;
	}
	Entity::Update(dt);

}

Item::~Item()
{
}

const char * Item::FileName()
{
	
	_itemName = "Resources/Item_Effect/" + _itemName + ".png";
	return _itemName.c_str();
}

int Item::TotalFrame()
{
	return 1;
}

int Item::Row()
{
	return 1;
}

int Item::Column()
{
	return 1;
}

float Item::SecondPerFrame()
{
	return 1;
}

