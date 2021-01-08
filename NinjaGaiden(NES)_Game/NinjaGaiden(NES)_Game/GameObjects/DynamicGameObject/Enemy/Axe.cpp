#include "Axe.h"

Axe::~Axe()
{
}

Axe::Axe(D3DXVECTOR3 position)
{
	
	init(position);
	vx = 0;
	vy = -300;
	state = STAY;
	originalPos = position;
	TagEnemy = Entity::Axe_E;
}
void Axe::Update(float dt)
{
	GameObject::Update(dt);
	//vx -= 5 * dt;
	Entity::Update(dt);
	if (state == SHOT)
	{
		_Active = true;
		time += dt;
		vx = turnLeft*SPEED;
		vy = vy+10;
	}
	else
	{
		SetPosition(originalPos);
		vx = 0;
		vy = -200;
	}
	if (posY > 150 || posY == 0)
	{
		state = STAY;
	}
	if (_Active == false)
	{
		state = STAY;
		SetPosition(originalPos);
	}
}

void Axe::turn(int dir)
{
	turnLeft = dir;
	vx = vx*turnLeft;
}

void Axe::SetShot(boolean shot)
{
	state = shot;
}

void Axe::SetOriginalPosition(D3DXVECTOR3 position)
{
	originalPos = position;
}


const char * Axe::FileName()
{
	return "Resources/Enemy/Axe.png";
}

int Axe::TotalFrame()
{
	return 3;
}

int Axe::Row()
{
	return 1;
}

int Axe::Column()
{
	return 3;
}

float Axe::SecondPerFrame()
{
	return 0.2f;
}



void Axe::OnCollision(Entity * impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
}
