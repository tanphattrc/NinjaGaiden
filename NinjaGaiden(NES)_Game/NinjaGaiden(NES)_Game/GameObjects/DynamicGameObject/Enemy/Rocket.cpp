#include "Rocket.h"

Rocket::~Rocket()
{
}

Rocket::Rocket(D3DXVECTOR3 position)
{
	//mAnimation = new Animation("Resources/Enemy/Rocket.png", 3, 1, 3, 0.25f);
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
void Rocket::Update(float dt)
{
	//vx -= 5 * dt;
	//Entity::Update(dt);
	if (state == SHOT)
	{
		/*delete mAnimation;
		mAnimation = new Animation(FileName(), TotalFrame(), Row(), Column(), SecondPerFrame());*/
		time += dt;
		vx = turnLeft * SPEED;
		if (_Active == false)
		{
			_Active = true;
		}

	}
	else
	{
		SetPosition(originalPos);
		vx = 0;
	}
	GameObject::Update(dt);
}

void Rocket::turn(int dir)
{
	turnLeft = dir;
	vx = vx * turnLeft;
}

void Rocket::SetShot(boolean shot)
{
	state = shot;
}

void Rocket::SetOriginalPosition(D3DXVECTOR3 position)
{
	originalPos = position;
}


const char * Rocket::FileName()
{
	//if (state == SHOT)
	return "Resources/Enemy/Rocket.png";
}

int Rocket::TotalFrame()
{
	return 1;
}

int Rocket::Row()
{
	return 1;
}

int Rocket::Column()
{
	return 1;
}

float Rocket::SecondPerFrame()
{
	return 0.2f;
}



void Rocket::OnCollision(Entity * impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
}
