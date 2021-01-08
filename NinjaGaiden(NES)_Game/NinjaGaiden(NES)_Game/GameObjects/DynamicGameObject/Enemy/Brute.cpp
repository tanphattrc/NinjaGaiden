#include "Brute.h"

Brute::~Brute()
{
}

Brute::Brute(D3DXVECTOR3 position)
{
	
	init(position);
	time = 0;
	timeBullet = 0;
	state = WALKING_STATE;
	originalPos = position;
	for (int i = 0; i < 3; i++)
	{
		Bullet* temp = new Bullet(this->GetPosition());
		temp->SetShot(false);
		bullet.push_back(temp);
	}
	mAnimation = new Animation(FileName(), TotalFrame(), Row(), Column(), SecondPerFrame());
	setBullet();
	turnLeft = -1;
	vx = turnLeft*SPEED;
	minX = 9999;
	maxX = 9999;

	TagEnemy = Entity::Brute;
}
void Brute::Update(float dt)
{
	if (GameGlobal::Pause)
	{
		GameObject::Update(dt);
		Entity::Update(dt);
		if (_Active == true)
		{
			time += dt;
			timeBullet += dt;
			mAnimation->SetPosition(this->GetPosition());
			if (bulletTurn == 1)
				mAnimation->FlipVertical(true);
			else
				mAnimation->FlipVertical(false);
			if (posX >= maxX)
			{
				turnLeft = -1;
			}
			if (posX <= minX)
			{
				turnLeft = 1;
			}
			if (time >= 2)
			{
				time = 0;
				state = -state;
				delete mAnimation;
				mAnimation = new Animation(FileName(), TotalFrame(), Row(), Column(), SecondPerFrame());
				for (int i = 0; i < 3; i++)
				{
					bullet[i]->SetShot(-state);
				}
				Sound::getInstance()->play("MachineGunner", true, 0);


			}
			//Changeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
			if (state == WALKING_STATE)
			{
				vx = turnLeft * SPEED;
				setBullet();
				for (int i = 0; i < 3; i++)
				{
					bullet[i]->Hidden();
				}
				if (mPlayer != NULL)
					if (mPlayer->GetPosition().x > posX)
					{
						for (int i = 0; i < bullet.size(); i++)
						{
							bullet[i]->turn(1);
							bulletTurn = -1;
						}
					}
					else
					{
						for (int i = 0; i < bullet.size(); i++)
						{
							bullet[i]->turn(-1);
							bulletTurn = 1;
						}
					}
			}
			else
			{
				vx = 0;
				if (mPlayer != NULL)
				{
					if (mPlayer->GetPosition().x > posX && turnLeft == -1)
					{
						turnLeft = 1;
					}
					if (mPlayer->GetPosition().x < posX && turnLeft == 1)
					{
						turnLeft = -1;
					}
				}
			}
		}
	}
	else
	{

	}

}

void Brute::turn()
{
	/*turnLeft = -turnLeft;
	vx = vx*turnLeft;*/
}


const char * Brute::FileName()
{
	if (state == WALKING_STATE)
		return "Resources/Enemy/Brutefixed.png";
	else
		return "Resources/Enemy/Brute_shootingfixed.png";
}

vector<GameObject*> Brute::GetBullet()
{
	vector<GameObject*> listresult;
	for (int i = 0; i < 3; i++)
	{
		listresult.push_back(bullet[i]);
	}
	return listresult;
}

void Brute::setBullet()
{
	
	for (int i = 0; i < 3; i++)
	{
		D3DXVECTOR3 temp;
		if (i < 3)
			temp.x = posX - turnLeft * i * 15;

		temp.y = posY;
		temp.z = 0;
		bullet[i]->SetOriginalPosition(temp);
	}
}

int Brute::TotalFrame()
{
	return 2;
}

int Brute::Row()
{
	return 1;
}

int Brute::Column()
{
	return 2;
}

float Brute::SecondPerFrame()
{
	return 0.2f;
}



void Brute::OnCollision(Entity * impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
}
