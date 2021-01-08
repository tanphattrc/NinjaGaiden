#include "Swordman.h"

Swordman::~Swordman()
{
}

Swordman::Swordman(D3DXVECTOR3 position)
{
	

	init(position);
	turnLeft = -1;

	//vx = turnLeft*SPEED;
	originalPos = position;
	minX = -999;
	maxX = 999;
	TagEnemy = Entity::Swordman;
}
void Swordman::Update(float dt)
{
	if (GameGlobal::Pause)
	{
		GameObject::Update(dt);
		mAnimation->SetPosition(this->GetPosition());
		if (_Active == true)
		{
			if (turnLeft == -1)
				mAnimation->FlipVertical(true);
			else
				mAnimation->FlipVertical(false);
			vx = turnLeft * SPEED;
			//vy = 10;
			if (posX >= maxX)
				turnLeft = -1;
			if (posX <= minX)
				turnLeft = 1;
		}
		else
		{
			vx = 0;
			vy = 0;
			if (mPlayer != NULL)
			{
				if (mPlayer->GetPosition().x >= originalPos.x)
				{
					turnLeft = 1;
				}
				else
					turnLeft = -1;
			}

		}
	}
	else
	{

	}
	
}


const char * Swordman::FileName()
{
	return "Resources/Enemy/Swordman.png";
}

int Swordman::TotalFrame()
{
	return 3;
}

int Swordman::Row()
{
	return 1;
}

int Swordman::Column()
{
	return 3;
}

float Swordman::SecondPerFrame()
{
	return 0.3f;
}

void Swordman::turn()
{
	turnLeft = -turnLeft;
	vx = vx*turnLeft;
}

void Swordman::checkPlayerPosition()
{
}

void Swordman::SetActive(bool variable)
{
	GameObject::SetActive(variable);
}



void Swordman::OnCollision(Entity * impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	////this->SetPosition(-100, 0);
	//die = 1;
	if (impactor->Tag == EntityTypes::Ninja)
	{
		vx = 0;
		vy = 0;
		//Cho ra khỏi màn hình
		this->SetPosition(-100, -100);
	}
	if ((impactor->Tag == EntityTypes::Static))
	{
		vy = 0;
	}
}
 