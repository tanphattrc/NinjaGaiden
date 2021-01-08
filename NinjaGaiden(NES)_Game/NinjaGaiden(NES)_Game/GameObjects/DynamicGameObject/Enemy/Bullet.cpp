#include "Bullet.h"

Bullet::~Bullet()
{
}

Bullet::Bullet(D3DXVECTOR3 position)
{
	//mAnimation = new Animation("Resources/Enemy/Bullet.png", 3, 1, 3, 0.25f);
	////this->vx = 0;
	////this->vy = 0;
	//Tag = Enemy;
	////mAnimation->SetPosition(position);
	//this->SetPosition(position);
	//Entity::SetWidth(mAnimation->GetWidth());
	//Entity::SetHeight(mAnimation->GetHeight());
	init(position);
	vx = 0;
	state = STAY;
	originalPos = position;
	turnLeft = -1;

}
void Bullet::Update(float dt)
{
	GameObject::Update(dt);
	//vx -= 5 * dt;
	//Entity::Update(dt);
	if (state == SHOT)
	{
		delete mAnimation;
		mAnimation = new Animation(FileName(), TotalFrame(), Row(), Column(), SecondPerFrame());
		time += dt;
		vx = turnLeft*SPEED;
		_Active = true;
	}
	else
	{
		SetPosition(originalPos);
		vx = 0;
	}
}

void Bullet::turn(int dir)
{
	turnLeft = dir;
	vx = vx*turnLeft;
}

void Bullet::SetShot(boolean shot)
{
	state = shot;
}

void Bullet::SetOriginalPosition(D3DXVECTOR3 position)
{
	originalPos = position;
}


const char * Bullet::FileName()
{
	if (state == SHOT)
		return "Resources/Enemy/bullet.png";
}

int Bullet::TotalFrame()
{
	return 1;
}

int Bullet::Row()
{
	return 1;
}

int Bullet::Column()
{
	return 1;
}

float Bullet::SecondPerFrame()
{
	return 0.2f;
}



void Bullet::OnCollision(Entity * impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
}
