#include "Ball.h"

Ball::~Ball()
{
}

Ball::Ball(D3DXVECTOR3 position)
{
	
	init(position);
	vx = 0;
	state = STAY;
	originalPos = position;
	turnLeft = -1;
	TagWeapon = Entity::BallWeapon;
	TagEnemy = Entity::Ball_E;
}
void Ball::Update(float dt)
{
	GameObject::Update(dt);
	
	//Entity::Update(dt);
	if (state == SHOT)
	{
		time += dt;
		vx = turnLeft*SPEED;
		_Active = true;
	}
	else
	{
		SetPosition(originalPos);
		vx = 0;
		_Active = false;
	}
}

void Ball::turn(int dir)
{
	turnLeft = dir;
	vx = turnLeft*SPEED;
}

void Ball::SetShot(boolean shot)
{
	state = shot;
	SetPosition(originalPos);
}

void Ball::SetOriginalPosition(D3DXVECTOR3 position)
{
	originalPos = position;
}


const char * Ball::FileName()
{
	return "Resources/Enemy/Ball.png";
}

int Ball::TotalFrame()
{
	return 1;
}

int Ball::Row()
{
	return 1;
}

int Ball::Column()
{
	return 1;
}

float Ball::SecondPerFrame()
{
	return 0.2f;
}



//void Ball::OnCollision(Entity * impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
//{
//	GameObject::On
//}
