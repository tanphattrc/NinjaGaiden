#include "Canoneer.h"

Canoneer::~Canoneer()
{
}

Canoneer::Canoneer(D3DXVECTOR3 position)
{
	init(position);
	time = 0;
	timeBullet = 0;
	state = WALKING_STATE;
	originalPos = position;
	for (int i = 0; i < 1; i++)
	{
		Rocket* temp = new Rocket(this->GetPosition());
		temp->SetShot(false);
		bullet.push_back(temp);
	}
	mAnimation = new Animation(FileName(), TotalFrame(), Row(), Column(), SecondPerFrame());
	mAnimation->SetPosition(this->GetPosition());
	setBullet();
	turnLeft = -1;
	vx = 0;
	TagEnemy = Entity::Cannoer;
}
void Canoneer::Update(float dt)
{
	if (GameGlobal::Pause)
	{
		if (_Active == true)
		{
			mAnimation->SetPosition(this->GetPosition());
			if (turnLeft == -1)
				mAnimation->FlipVertical(true);
			else
				mAnimation->FlipVertical(false);
			time += dt;
			if (time >= 4)
			{
				time = 0;
				state = -state;
				delete mAnimation;
				mAnimation = new Animation(FileName(), TotalFrame(), Row(), Column(), SecondPerFrame());
				mAnimation->SetPosition(this->GetPosition());
				for (int i = 0; i < 1; i++)
				{
					bullet[i]->SetShot(-state);

				}
			}
			if (state == WALKING_STATE)
			{
				timeBullet = 0;
				setBullet();
				if (mPlayer != NULL)
					if (mPlayer->GetPosition().x > posX)
					{
						turnLeft = 1;
						for (int i = 0; i < bullet.size(); i++)
						{
							bullet[i]->turn(1);
						}
					}
					else
					{
						turnLeft = -1;
						for (int i = 0; i < bullet.size(); i++)
						{
							bullet[i]->turn(-1);
						}
					}
			}
			else
			{
				timeBullet += dt;
				if (timeBullet >= 0.2)
				{
					//spriteState = false;
					if (timeBullet <= 0.4)
					{
						Sound::getInstance()->play("CannonShooter", true, 0);

						delete mAnimation;
						mAnimation = new Animation("Resources/Enemy/Canoneer_stay.png", TotalFrame(), Row(), Column(), SecondPerFrame());
						mAnimation->SetPosition(this->GetPosition());
						if (turnLeft == -1)
							mAnimation->FlipVertical(true);
						else
							mAnimation->FlipVertical(false);
					}
				}
			}
		}
		GameObject::Update(dt);
	}
	else
	{

	}

}

void Canoneer::turn()
{
	/*turnLeft = -turnLeft;
	vx = vx*turnLeft;*/
}


const char * Canoneer::FileName()
{
	if (state == WALKING_STATE || spriteState == true)
		return "Resources/Enemy/Canoneer_stay.png";
	else
		return "Resources/Enemy/Canoneer_shot.png";
}

vector<GameObject*> Canoneer::GetBullet()
{
	vector<GameObject*> listresult;
	for (int i = 0; i < 1; i++)
	{
		listresult.push_back(bullet[i]);
	}
	return listresult;
}

void Canoneer::setBullet()
{
	for (int i = 0; i < 1; i++)
	{
		D3DXVECTOR3 temp;
		if (i < 1)
			temp.x = posX + i * 10;
		temp.y = posY;
		temp.z = 0;
		bullet[i]->SetOriginalPosition(temp);
	}
}

int Canoneer::TotalFrame()
{
	return 1;
}

int Canoneer::Row()
{
	return 1;
}

int Canoneer::Column()
{
	return 1;
}

float Canoneer::SecondPerFrame()
{
	return 0.2f;
}



void Canoneer::OnCollision(Entity * impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
}
