#include "Butterfly.h"

Butterfly::Butterfly(D3DXVECTOR3 position)
{
	init(position);
	this->TagItem = Entity::ItemType::Container;
	
}

void Butterfly::OnCollision(Entity * impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	SetPosition(-100, 0);

}


Butterfly::~Butterfly()
{
}

const char *Butterfly::FileName()
{
	return "Resources/StaticObject/Butterfly.png";
}

int Butterfly ::TotalFrame()
{
	return 2;
}

int Butterfly::Row()
{
	return 1;
}

int Butterfly::Column()
{
	return 2;
}

float Butterfly::SecondPerFrame()
{
	return 0.3f;
}

