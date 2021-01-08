#include "Eagle.h"

Eagle::~Eagle()
{
}

Eagle::Eagle(D3DXVECTOR3 position)
{
	_Active = false;
	init(position);
	moving = false;
	turnLeft = -1;
	time = 0;
	originalPos = position;
	if (mPlayer != NULL)
	{
		playerPos = mPlayer->GetPosition();

		if (playerPos.x > posX)
			direction = 1;
		else
			direction = -1;
	}
	directionVector.x = -1;
	directionVector.y = 1;
	oT = 0;
	TagEnemy = Entity::Eagle;
	timePauseUpdate = 200;
}

void Eagle::Update(float dt)
{
	if (GameGlobal::Pause)
	{
		if (isUpdate)
		{
			GameObject::Update(dt);
			//mAnimation->SetPosition(this->GetPosition());
			if (_Active == true)
			{
				if (oT >= 150 && oT < 250)
				{
					mAnimation->FlipVertical(true);
				}
				else
				{
					mAnimation->FlipVertical(false);
				}
				if (oT >= 250)
				{
					mAnimation->FlipVertical(false);
				}
				if (oT >= 350)
				{
					oT = 150;
				}


				//
				//if (oT >= 250)
				//{
				////	mAnimation->FlipVertical(false);
				//}
				//if (oT = 300)
				//{
				//	//oT = 0;
				//}
				if (mPlayer != NULL)
					playerPos = mPlayer->GetPosition();
				oT++;
				if (mPlayer != NULL)
					if (!direction)
					{
						this->vx = ((100 * cos(2 * 3.14*0.005*oT + 3.14 / 2)) + mPlayer->GetPosition().x) / dt;
						this->vy = (mPlayer->GetPosition().y - 10 - this->posY);



					}
					else
					{

						this->vx = ((100 * cos(2 * 3.14*0.005*oT + -3.14 / 2)) + mPlayer->GetPosition().x) / dt;
						this->vy = (mPlayer->GetPosition().y - 10 - this->posY);

					}

				posX = vx * dt;

				posY += vy * dt;
				mAnimation->SetPosition(D3DXVECTOR2(posX, posY));
			}
			else
			{
				vx = 0;
				vy = 0;
				SetPosition(originalPos);
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

const char * Eagle::FileName()
{
	return "Resources/Enemy/Eagle.png";
}

int Eagle::TotalFrame()
{
	return 2;
}

int Eagle::Row()
{
	return 1;
}

int Eagle::Column()
{
	return 2;
}

float Eagle::SecondPerFrame()
{
	return 0.3f;
}

void Eagle::OnCollision(Entity * impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
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
}
