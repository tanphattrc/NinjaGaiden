#include "PlayerRunningState.h"
#include "PlayerStandingState.h"
#include "PlayerFallingState.h"
#include "../../..//GameDefine/GameDefine.h"

PlayerRunningState::PlayerRunningState(PlayerData *playerData)
{
	this->mPlayerData = playerData;

	acceleratorX = 3.0f;
	this->mPlayerData->player->allowMoveLeft = true;
	this->mPlayerData->player->allowMoveRight = true;
	this->mPlayerData->player->isJummping = false;

}


PlayerRunningState::~PlayerRunningState()
{
}

void PlayerRunningState::Update(float dt)
{
	
}

void PlayerRunningState::HandleKeyboard()
{
	if (IsKeyDown(DIK_RIGHTARROW))
	{
		mPlayerData->player->SetReverse(false);

		//di chuyen sang phai
		if (this->mPlayerData->player->GetVx() < Define::PLAYER_MAX_RUNNING_SPEED)
		{
			this->mPlayerData->player->AddVx(acceleratorX);

			if (this->mPlayerData->player->GetVx() >= Define::PLAYER_MAX_RUNNING_SPEED)
			{
				this->mPlayerData->player->SetVx(Define::PLAYER_MAX_RUNNING_SPEED);
			}
		}
	}	
	else if (IsKeyDown(DIK_LEFTARROW))
	{
		mPlayerData->player->SetReverse(true);
		
		//di chuyen sang trai
		if (this->mPlayerData->player->GetVx() > -Define::PLAYER_MAX_RUNNING_SPEED)
		{
			this->mPlayerData->player->AddVx(-acceleratorX);

			if (this->mPlayerData->player->GetVx() < -Define::PLAYER_MAX_RUNNING_SPEED)
			{
				this->mPlayerData->player->SetVx(-Define::PLAYER_MAX_RUNNING_SPEED);
			}
		}
	}
	/*else
		if (IsKeyDown(DIK_Z))
		{
			this->mPlayerData->player->SetState(new PlayerStandingBeatState(this->mPlayerData));
			return;
		}*/

	else
	{
		this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
		return;
	}
}
void PlayerRunningState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	//lay phia va cham so voi player
	//GameCollision::SideCollisions side = GameCollision::getSideCollision(this->mPlayerData->player, data);
	if (impactor->Tag == Entity::EntityTypes::Stair&& side == Entity::Right)
	{
		this->mPlayerData->player->SetState(new PlayerClimbingState(this->mPlayerData));
		return;
	}
	
	switch (side)
	{
	case Entity::Left:
	{
		//va cham phia ben trai player
		if (this->mPlayerData->player->getMoveDirection() == Player::MoveToLeft )
		{
			this->mPlayerData->player->allowMoveLeft = false;

			//day Player ra phia ben phai de cho player khong bi xuyen qua object
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
		}

		return;
	}

	case Entity::Right:
	{
		//va cham phia ben phai player
		if (this->mPlayerData->player->getMoveDirection() == Player::MoveToRight)
		{
			this->mPlayerData->player->allowMoveRight = false;

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


		}

		return;
	}

	case Entity::Top: case Entity::TopLeft: case Entity::TopRight:
	{	if (impactor->Tag == Entity::EntityTypes::Enemy && impactor->_Active == true && this->mPlayerData->player->invincible == false)
		{
		//this->mPlayerData->player->invincible = true;
		this->mPlayerData->player->AddPosition( (data.RegionCollision.right - data.RegionCollision.left + FrameWidth / 2), -FrameHeight / 2);
		this->mPlayerData->player->SetState(new PlayerDyingState(this->mPlayerData));
		}
	break;



	}
	case Entity::Bottom: case Entity::BottomLeft: case Entity::BottomRight:
	{
		////this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
		if (impactor->Tag == Entity::EntityTypes::Enemy&& impactor->_Active == true && this->mPlayerData->player->invincible == false)
		{
			//this->mPlayerData->player->invincible = true;
			this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left + FrameWidth / 2), -FrameHeight / 2);


			this->mPlayerData->player->SetState(new PlayerDyingState(this->mPlayerData));
			return;
		}
		else
		{
			if (impactor->Tag == Entity::EntityTypes::Static)
			{
				this->mPlayerData->player->SetVy(0);
			}


			
		}
	}
	}
}


PlayerState::StateName PlayerRunningState::GetState()
{
	return PlayerState::Running;
}
