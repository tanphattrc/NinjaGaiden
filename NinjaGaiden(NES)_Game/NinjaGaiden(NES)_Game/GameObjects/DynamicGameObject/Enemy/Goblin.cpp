#include "Goblin.h"
Goblin::~Goblin()
{
}

Goblin::Goblin(D3DXVECTOR3 position)
{

	init(position);
	vx = -SPEED;
	time = 0;
	timeBullet = 0;
	state = WALKING_STATE;
	originalPos = position;
	for (int i = 0; i < 1; i++)
	{
		Axe* temp = new Axe(this->GetPosition());
		temp->SetShot(false);
		bullet.push_back(temp);
	}
	mAnimation = new Animation(FileName(), TotalFrame(), Row(), Column(), SecondPerFrame());
	setBullet();
	bulletTracking = 0;
	turnLeft = -1;
	minX = -999;
	maxX = 999;
	TagEnemy = Entity::Goblin;
	timePauseUpdate = 200;

}
void Goblin::Update(float dt)
{
	if (GameGlobal::Pause)
	{
		if (isUpdate)
		{
			if (_Active == true)
			{
				if (mPlayer != NULL)
					if (mPlayer->GetPosition().x > posX)
					{
						mAnimation->FlipVertical(false);
						mPlayer->GetPosition().x;
						//turnLeft = 1;
						for (int i = 0; i < bullet.size(); i++)
						{
							bullet[i]->SetVx(50);
							if (abs(mPlayer->GetPosition().x - posX) < 50)
							{
								bullet[i]->SetVx(30);
							}
						}
					}
					else
					{
						//turnLeft = -1;
						mAnimation->FlipVertical(true);
						for (int i = 0; i < bullet.size(); i++)
						{
							bullet[i]->SetVx(-50);
							if (abs(posX - mPlayer->GetPosition().x) < 50)
								bullet[i]->SetVx(-30);
						}
					}
				if (posX >= maxX)
					turnLeft = -1;
				if (posX <= minX)
					turnLeft = 1;
				mAnimation->SetPosition(this->GetPosition());
			}

			GameObject::Update(dt);
			//vx -= 5 * dt;
			Entity::Update(dt);
			if (_Active == true)
			{
				time += dt;
				timeBullet += dt;
				if (time >= 1)
				{
					time = 0;
					state = -state;
					delete mAnimation;
					mAnimation = new Animation(FileName(), TotalFrame(), Row(), Column(), SecondPerFrame());
					if (bulletTracking < 1)
					{
						bullet[bulletTracking]->SetShot(true);
						bulletTracking++;
					}
					else
						bulletTracking = 0;
				}
			}
			else
			{
				for (int i = 0; i < bullet.size(); i++)
				{
					bullet[i]->Hidden();
				}
			}

			if (state == WALKING_STATE)
			{
				setBullet();
				vx = turnLeft * SPEED;
			}
			else
			{
				vx = 0;
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


const char * Goblin::FileName()
{
	if (state == WALKING_STATE)
		return "Resources/Enemy/Goblinfixed.png";
	else
		return "Resources/Enemy/Goblin_shooting.png";
}

int Goblin::TotalFrame()
{
	return 2;
}

int Goblin::Row()
{
	return 1;
}

int Goblin::Column()
{
	return 2;
}

float Goblin::SecondPerFrame()
{
	if (state == WALKING_STATE)
		return 0.2f;
	else
		return 0.5f;
}

vector<GameObject*> Goblin::GetBullet()
{
	vector<GameObject*> listresult;
	for (int i = 0; i < 1; i++)
	{
		listresult.push_back(bullet[i]);
	}
	return listresult;
}

void Goblin::setBullet()
{
	for (int i = 0; i < 1; i++)
	{
		bullet[i]->SetOriginalPosition(GetPosition());
	}
}

void Goblin::turn()
{
	turnLeft = -turnLeft;
	vx = vx*turnLeft;
}



void Goblin::OnCollision(Entity * impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	if (impactor->Tag == EntityTypes::Ninja)
	{
		////this->SetPosition(-100, 0);
		//die = 1;
		vx = 0;
		vy = 0;
		//Cho ra khỏi màn hình
		this->SetPosition(-100, -100);
	}
}
