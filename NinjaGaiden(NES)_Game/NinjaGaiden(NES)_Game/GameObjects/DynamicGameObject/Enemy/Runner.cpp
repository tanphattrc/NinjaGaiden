#include "Runner.h"

Runner::Runner(D3DXVECTOR3 position)
{
	init(position);
	vx = turnLeft*SPEED;
	originalPos = position;
	turnLeft = -1;
	state = true;
	minX = position.x - 30;
	maxX = position.x + 30;
	TagEnemy = Entity::Runner;
}

Runner::~Runner()
{

}

void Runner::Update(float dt)
{
	if (GameGlobal::Pause)
	{
		GameObject::Update(dt);
		Entity::Update(dt);
		if (_Active == true)
		{
			mAnimation->SetPosition(this->GetPosition());
			if (turnLeft == -1)
				mAnimation->FlipVertical(true);
			else
				mAnimation->FlipVertical(false);
			vx = turnLeft * SPEED;
			if (state)
			{
				vy = 0;
				if (posX >= maxX)
				{
					vy = -170;
					state = false;
				}
				if (posX <= minX)
				{
					vy = -170;
					state = false;
				}
			}
			else
			{
				vy = vy + 10;
			}
		}
		else
		{
			if (mPlayer != NULL)
				if (mPlayer->GetPosition().x >= originalPos.x)
				{
					turnLeft = 1;
				}
				else
					turnLeft = -1;
			vx = 0;
			vy = 0;
		}
	}
	else
	{

	}
}

const char * Runner::FileName()
{
	return "Resources/Enemy/Runner.png";
}

int Runner::TotalFrame()
{
	return 2;
}

int Runner::Row()
{
	return 1;
}

void Runner::turn()
{
	turnLeft = -turnLeft;
	vx = vx*turnLeft;
}

int Runner::Column()
{
	return 2;
}

float Runner::SecondPerFrame()
{
	return 0.2f;
}



void Runner::OnCollision(Entity * impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	if ((impactor->Tag == EntityTypes::Static))
	{
		vy = 0;
		state = true;
	}
}
