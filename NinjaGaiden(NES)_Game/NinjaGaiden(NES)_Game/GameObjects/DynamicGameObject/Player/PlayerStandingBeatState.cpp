#include "PlayerStandingBeatState.h"
#include"PlayerStandingState.h"
PlayerStandingBeatState::PlayerStandingBeatState(PlayerData *playerData)
{ 
	this->mPlayerData = playerData;
//	this->mPlayerData->player->SetVx(0);
	
	if (this->mPlayerData->player->isJummping)
	{
		this->mPlayerData->player->AddVy(6);
		//this->mPlayerData->player->isJummping = false;

	}
	else
	{
		//this->mPlayerData->player->SetVy(0);
		this->mPlayerData->player->SetVx(0);
	}
	
	mTimePerFrame = 0.3;
	
	Sound::getInstance()->play("Beat", true, 0);
	mTimeHit = 15;
	mCurrentTotalTime = 0;
	mTimeChangeState = 0;
	//this->mPlayerData->player->isUpdate = true;
}


PlayerStandingBeatState::~PlayerStandingBeatState()
{
	
}

void PlayerStandingBeatState::OnCollision(Entity * impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	if (impactor->Tag == Entity::EntityTypes::Static)
	{
		this->mPlayerData->player->SetVx(0);
	}
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
			
		}
		break;
	}

	case Entity::Right:
	{
	
		if (impactor->Tag==Entity::EntityTypes::Enemy && impactor->_Active == true && ! this->mPlayerData->player->GetReserse())
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
		if (impactor->Tag == Entity::EntityTypes::Item)
		{

			impactor->OnCollision();
			//impactor->Hidden();
		}
		else
		{
			this->mPlayerData->player->isJummping = false;
		//	this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
			this->mPlayerData->player->SetVy(0);

			
		}
	}

	default:
		break;
	}

}

void PlayerStandingBeatState::Update(float dt)
{
	
	
	if (this->mPlayerData->player->isJummping)
	{
		this->mPlayerData->player->AddVy(6);
		if (this->mPlayerData->player->GetVy() >= Define::PLAYER_MAX_JUMP_VELOCITY)
		{
			this->mPlayerData->player->SetVy(Define::PLAYER_MAX_JUMP_VELOCITY);
		}
		//this->mPlayerData->player->isJummping = false;

	}
	if (mTimeChangeState >= mTimePerFrame * 2)
	{

		mTimeChangeState = 0;
	
			mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
			return;
		


	}
	else
	{
		mCurrentTotalTime += dt;
		mTimeChangeState += dt;
		if (mCurrentTotalTime >= mTimePerFrame)
		{
			this->mPlayerData->player->setIndex(1);
			mCurrentTotalTime = 0;
		}
	}
}

void PlayerStandingBeatState::HandleKeyboard()
{
	
}

PlayerState::StateName PlayerStandingBeatState::GetState()
{
	return PlayerState::StandingBeat;
}
