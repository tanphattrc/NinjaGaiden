#include "Panther.h"

Panther::~Panther()
{
}

Panther::Panther(D3DXVECTOR3 position)
{
	init(position);
	vx = turnLeft*SPEED;
	//vy = 50;
	originalPos = position;
	turnLeft = 1;
	minX = -9999;
	maxX = 9999;
	TagEnemy = Entity::Paner;
	timePauseUpdate = 200;
}

void Panther::Update(float dt)
{
	if (GameGlobal::Pause)
	{
		if (isUpdate)
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
				vy = vy + 10;
				if (posX >= maxX)
					turnLeft = -1;
				if (posX <= minX)
					turnLeft = 1;
				DBOUT("PosY: " << posY << "OriginalY: " << originalPos.y);
			}
			else
			{
				vx = 0;
				vy = 0;
				if (mPlayer != NULL)
					if (mPlayer->GetPosition().x >= originalPos.x)
					{
						turnLeft = 1;
					}
					else
						turnLeft = -1;

			}
		}
		else
		{
			timePauseUpdate--;
			if (timePauseUpdate <= 0)
			{
				timePauseUpdate = 200;
				isUpdate = true;
			}
		}
	}
	else
	{

	}
}

const char * Panther::FileName()
{
	return "Resources/Enemy/Panther.png";
}

int Panther::TotalFrame()
{
	return 2;
}

int Panther::Row()
{
	return 1;
}

int Panther::Column()
{
	return 2;
}

float Panther::SecondPerFrame()
{
	return 0.3f;
}

void Panther::OnCollision(Entity * impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	////this->SetPosition(-100, 0);
	//die = 1;
	if (impactor->Tag == EntityTypes::Static)
	{
		if ((side == Bottom || side == BottomLeft || side == BottomRight))
		{
			vy = -120;
		}
	}
	if (impactor->Tag == EntityTypes::Ninja)
	{
		vx = 0;
		vy = 0;
		//Cho ra khỏi màn hình
		this->SetPosition(-100, -100);
	}



}
