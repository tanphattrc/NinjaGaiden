
#include "Boss.h"


Boss::~Boss()
{
}





Boss::Boss(D3DXVECTOR3 position)
{
	_HP = 16;
	init(position);
	vx = SPEED;
	vy = 0;
	time = 0;
	timeBullet = 0;
	state = STANDING_STATE;
	originalPos = position;
	for (int i = 0; i < 3; i++)
	{
		Ball* temp = new Ball(this->GetPosition());
		temp->SetShot(false);
		bullet.push_back(temp);
	}
	mAnimation->FlipVertical(true);
	setBullet();
	bulletTracking = 0;
	turnLeft = 1;
	mAnimationJumpingState = new Animation("Resources/Enemy/Boss_jump.png", 1, 1, 1, 0.5f);
	mAnimationStandingState = new Animation("Resources/Enemy/Boss_stand.png", 1, 1, 1, 0.5f);
	e_Boss = new ExplosionBoss(this->GetPosition());
	timeDie = 0;
	
}
void Boss::changeAnimation(boolean _state)
{
	switch (state)
	{
	case STANDING_STATE:
		mAnimationStandingState->SetPosition(this->GetPosition());
		mAnimation = mAnimationStandingState;
		//vx = 0;
		//mAnimation->FlipHorizontal(true);
		break;
	case JUMPING_STATE:
		mAnimationJumpingState->SetPosition(this->GetPosition());
		mAnimation = mAnimationJumpingState;
	//	mAnimation->FlipVertical(true);
		//vx = 0;
		break;
	}
	this->width = mAnimation->GetWidth();
	this->height = mAnimation->GetHeight();
	
}
void Boss::Update(float dt)
{
	if (GameGlobal::Pause)
	{
		if (isUpdate)
		{
			if (_HP == 0)
			{
				isUpdate = false;
				return;
			}
			GameObject::Update(dt);
			Entity::Update(dt);

			DBOUT("PosY:" << posY);
			if (_Active == true)
				if (state == JUMPING_STATE)
				{
					changeAnimation(JUMPING_STATE);
					setBullet();
					if (turnLeft == -1)
					{
						mAnimation->FlipVertical(true);
					}
					else
					{
						mAnimation->FlipVertical(false);
					}
					vy = vy + 10;
					vx = turnLeft * SPEED;
					if (posY >= originalPos.y)
					{
						timeBullet++;
						state = STANDING_STATE;

					}
				}
				else
				{
					time += dt;
					changeAnimation(STANDING_STATE);
					vx = 0;
					vy = 0;
					if (timeBullet >= 3)
					{
						for (int i = 0; i < 3; i++)
						{
							if (mPlayer->GetPosition().x > posX)
							{
								bullet[i]->turn(1);
							}
							else
							{
								bullet[i]->turn(-1);
							}
							bullet[i]->SetShot(true);
						}

						timeBullet = 0;
					}

					if (time >= 1)
					{
						vy = -200;
						time = 0;

						turn();
						posY = originalPos.y - 1;
						state = JUMPING_STATE;

					}
				}
		}
		else
		{
			//e_Boss->SetPosition(this->GetPosition());
			if (timeDie < 4)
			{
				timeDie += dt;
				e_Boss->Update(dt);
				Sound::getInstance()->play("BossDie", true, 0);
			}
			else
			{
				Sound::getInstance()->stop("BossDie");
				e_Boss->SetPosition(-100, -100);
				this->SetPosition(-100, -100);
			}


		}
	}
	else
	{

	}

}
void Boss::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	GameObject::Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);
	if (!isUpdate)
	{
		e_Boss->Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);
	}
}
void Boss::turn()
{
	turnLeft = -turnLeft;
	vx = vx * turnLeft;
}




const char* Boss::FileName()
{
		return "Resources/Enemy/Boss_stand.png";

}

vector<GameObject*> Boss::GetBullet()
{
	vector<GameObject*> listresult;
	for (int i = 0; i < 3; i++)
	{
		listresult.push_back(bullet[i]);
	}
	return listresult;
}

void Boss::setBullet()
{
	for (int i = 0; i < 3; i++)
	{
		D3DXVECTOR3 temp;
		temp.y = posY + i * 10;
		temp.x = posX;
		temp.z = 0;
		bullet[i]->SetOriginalPosition(temp);
	}

}

int Boss::TotalFrame()
{
	return 1;
}

int Boss::Row()
{
	return 1;
}

int Boss::Column()
{
	return 1;
}

float Boss::SecondPerFrame()
{
	return 0.5f;
}



void Boss::OnCollision(Entity * impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
}
