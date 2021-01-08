#include "PlayerUseWeaponState.h"






PlayerUseWeaponState::PlayerUseWeaponState(PlayerData * playerData)
{
	this->mPlayerData = playerData;
	if (this->mPlayerData->player->isJummping)
	{
		this->mPlayerData->player->AddVy(6);

	}
	else
	{
		this->mPlayerData->player->SetVy(0);
		this->mPlayerData->player->SetVx(0);
	}
	mTimePerFrame = 0.1;
}

PlayerUseWeaponState::~PlayerUseWeaponState()
{
}

void PlayerUseWeaponState::OnCollision(Entity * impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	switch (side)
	{
	case Entity::Left:
	{
		if (impactor->Tag == Entity::EntityTypes::Enemy && impactor->_Active == true && this->mPlayerData->player->invincible == false)
		{
			//this->mPlayerData->player->invincible = true;

			this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left + FrameWidth / 2, -FrameHeight / 2);

			this->mPlayerData->player->SetState(new PlayerDyingState(this->mPlayerData));
		}
		else
		{
			if (impactor->Tag == Entity::EntityTypes::Static)
			{
				this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);

				this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
			}
		}
		return;
		break;
	}

	case Entity::Right:
	{
		if (impactor->Tag == Entity::EntityTypes::Enemy&& impactor->_Active == true && this->mPlayerData->player->invincible == false)
		{
			//this->mPlayerData->player->invincible = true;

			this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left + FrameWidth / 2), -FrameHeight / 2);

			this->mPlayerData->player->SetState(new PlayerDyingState(this->mPlayerData));
		}
		else
		{
			if (impactor->Tag == Entity::EntityTypes::Static)
			{
				this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
				this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));

			}
		}
		return;
		
		break;
	}

	case Entity::TopRight: case Entity::TopLeft: case Entity::Top:
	{
		if (impactor->Tag == Entity::EntityTypes::Enemy && impactor->_Active == true && this->mPlayerData->player->invincible == false)
		{
			//this->mPlayerData->player->invincible = true;
			this->mPlayerData->player->AddPosition(-FrameWidth, -FrameHeight/2);
			this->mPlayerData->player->SetState(new PlayerDyingState(this->mPlayerData));
		}
		break;
	}

	case Entity::BottomRight: case Entity::BottomLeft: case Entity::Bottom:
	{

		if (impactor->Tag == Entity::EntityTypes::Enemy&& impactor->_Active == true && this->mPlayerData->player->invincible == false)
		{
			//this->mPlayerData->player->invincible = true;
			this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left + FrameWidth / 2), -FrameHeight / 2);


			this->mPlayerData->player->SetState(new PlayerDyingState(this->mPlayerData));
			return;
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

void PlayerUseWeaponState::Update(float dt)
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
	if (mCurrentTotalTime >= mTimePerFrame * 3)
	{

		mCurrentTotalTime = 0;
	
		mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
		return;
		//}
		/*else {
			mPlayerData->player->SetState(new PlayerFallingState(this->mPlayerData));
			return;
		}*/


	}
	else
	{
		mCurrentTotalTime += dt;
	}
}

void PlayerUseWeaponState::HandleKeyboard()
{
}

PlayerState::StateName PlayerUseWeaponState::GetState()
{
	return PlayerState::UseWeapon;
}
