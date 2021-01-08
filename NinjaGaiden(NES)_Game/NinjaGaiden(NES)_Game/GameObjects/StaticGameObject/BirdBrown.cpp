#include "BirdBrown.h"

BirdBrown::BirdBrown(D3DXVECTOR3 position)
{
	init(position);
	this->TagItem = Entity::ItemType::Container;

}

void BirdBrown::OnCollision(Entity * impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	SetPosition(-100, 0);

}


BirdBrown::~BirdBrown()
{
}

const char *BirdBrown::FileName()
{
	return "Resources/StaticObject/BirdBrown.png";
}

int BirdBrown::TotalFrame()
{
	return 2;
}

int BirdBrown::Row()
{
	return 1;
}

int BirdBrown::Column()
{
	return 2;
}

float BirdBrown::SecondPerFrame()
{
	return 0.3f;
}

