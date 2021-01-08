
#include "PlayerStandingBeatState.h"
#include "PlayerStandingState.h"
#include "PlayerSittingBeatState.h"
PlayerSittingBeatState::PlayerSittingBeatState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
	mTimePerFrame = 0.3;
	//this->mPlayerData->player->isUpdate = true;
	
	Sound::getInstance()->play("Beat", true, 0);
	mTimeHit = 15;
}


PlayerSittingBeatState::~PlayerSittingBeatState()
{
}

void PlayerSittingBeatState::OnCollision(Entity * impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	switch (side)
	{
	case Entity::Left:
	{
		if (impactor->Tag == Entity::EntityTypes::Enemy&& impactor->_Active && this->mPlayerData->player->GetReserse())
		{

			if (impactor->TagEnemy == Entity::EnemyType::Boss)
			{
				mTimeHit--;
				if (mTimeHit <= 0)
				{
					impactor->_HP -= 1;
					//	this->mPlayerData->player->setAllowHit(false);
					mTimeHit = 15;
				}

				//this->mPlayerData->player->
			}
			else
			{
				this->mPlayerData->player->e_Hit = new ExplosionHit(impactor->GetPosition());
				this->mPlayerData->player->setAllowHit(false);
				impactor->Hidden();

			}


		}
		if (impactor->Tag == Entity::EntityTypes::Item)
		{



			impactor->OnCollision();
			//impactor->Hidden();
		}
		break;
	}

	case Entity::Right:
	{

		if (impactor->Tag == Entity::EntityTypes::Enemy && impactor->_Active == true && !this->mPlayerData->player->GetReserse())
		{
			if (impactor->TagEnemy == Entity::EnemyType::Boss)
			{
				mTimeHit--;
				if (mTimeHit <= 0)
				{
					impactor->_HP -= 1;
					//this->mPlayerData->player->setAllowHit(false);
					mTimeHit = 15;
				}
			}

			else
			{
				this->mPlayerData->player->e_Hit = new ExplosionHit(impactor->GetPosition());
				this->mPlayerData->player->setAllowHit(false);
				impactor->Hidden();
			}

		}
		if (impactor->Tag == Entity::EntityTypes::Item)
		{



			impactor->OnCollision();
			//impactor->Hidden();
		}
		break;
	}

	case Entity::TopRight: case Entity::TopLeft: case Entity::Top:
	{
		if (impactor->Tag == Entity::EntityTypes::Enemy&& impactor->_Active == true && this->mPlayerData->player->invincible == false)

		{
			//this->mPlayerData->player->invincible = true;
			this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left + FrameWidth / 2, -FrameHeight / 2);

			this->mPlayerData->player->SetState(new PlayerDyingState(this->mPlayerData));
			return;
		}
		
		
		if (impactor->Tag == Entity::EntityTypes::Item)
		{


			impactor->OnCollision();
			
		}
		break;
	}

	case Entity::BottomRight: case Entity::BottomLeft: case Entity::Bottom:
	{

		if (impactor->Tag == Entity::EntityTypes::Enemy)
		{
			if (impactor->Tag == Entity::EntityTypes::Enemy&& impactor->_Active == true && this->mPlayerData->player->invincible == false)

			{
				//this->mPlayerData->player->invincible = true;
				this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left + FrameWidth / 2, -FrameHeight / 2);

				this->mPlayerData->player->SetState(new PlayerDyingState(this->mPlayerData));
				return;
			}
		}
		if (impactor->Tag == Entity::EntityTypes::Enemy)
		{

		}
		if (impactor->Tag == Entity::EntityTypes::Item)
		{

			impactor->OnCollision();
			//impactor->Hidden();
		}
		else
		{
			//	this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
			this->mPlayerData->player->SetVy(0);


		}
	}

	default:
		break;
	}
}

void PlayerSittingBeatState::Update(float dt)
{
	if (mCurrentTotalTime >= mTimePerFrame * 2)
	{

		mCurrentTotalTime = 0;
		mPlayerData->player->SetState(new PlayerSittingState(this->mPlayerData));
		return;


	}
	else
	{
		mCurrentTotalTime += dt;
	}
}

void PlayerSittingBeatState::HandleKeyboard()
{
	if (IsKeyDown(DIK_LEFTARROW) || IsKeyDown(DIK_RIGHTARROW))
	{
		
		this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
		return;
	}
}

PlayerState::StateName PlayerSittingBeatState::GetState()
{
	return PlayerState::SittingBeat;
}
