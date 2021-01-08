#include "PlayerFallingState.h"
#include "Player.h"
#include "PlayerStandingState.h"
#include "../..//../GameDefine/GameDefine.h"

PlayerFallingState::PlayerFallingState(PlayerData *playerData)
{
    this->mPlayerData = playerData;
    acceleratorY = 10.0f;
    acceleratorX = 3.0f;

    if (this->mPlayerData->player->GetVx() == 0)
    {
        allowMoveX = false;
    }
    else
    {
        allowMoveX = true;
    }
	this->mPlayerData->player->isJummping = true;
	//this->mPlayerData->player->isUpdate = true;
}


PlayerFallingState::~PlayerFallingState()
{
}


void PlayerFallingState::Update(float dt)
{
	
 
	this->mPlayerData->player->AddVy(acceleratorY);

	if (mPlayerData->player->GetVy() > Define::PLAYER_MAX_JUMP_VELOCITY)
	{
		mPlayerData->player->SetVy(Define::PLAYER_MAX_JUMP_VELOCITY);
	}
}

void PlayerFallingState::HandleKeyboard()
{
	if (IsKeyDown(DIK_Z))
	{

		this->mPlayerData->player->SetState(new PlayerStandingBeatState(this->mPlayerData));
		return;
	}
	else
    if (IsKeyDown(DIK_RIGHTARROW))
    {
        mPlayerData->player->SetReverse(false);

        isLeftOrRightKeyPressed = true;
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

        isLeftOrRightKeyPressed = true;
        //di chuyen sang trai
        if (this->mPlayerData->player->GetVx() > -Define::PLAYER_MAX_RUNNING_SPEED)
        {
            this->mPlayerData->player->AddVx(-acceleratorX);

            if (this->mPlayerData->player->GetVx() <= -Define::PLAYER_MAX_RUNNING_SPEED)
            {
                this->mPlayerData->player->SetVx(-Define::PLAYER_MAX_RUNNING_SPEED);
            }
        }
    }
	else
	
    {
        isLeftOrRightKeyPressed = false;    
    }
}

PlayerState::StateName PlayerFallingState::GetState()
{
    return PlayerState::Falling;
}

void PlayerFallingState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	//lay phia va cham so voi player
	//GameCollision::SideCollisions side = GameCollision::getSideCollision(this->mPlayerData->player, data);
	if (impactor->Tag == Entity::EntityTypes::Stair&& side == Entity::Right)
	{
		this->mPlayerData->player->SetState(new PlayerClimbingState(this->mPlayerData));
	
		return;
	}
	if (impactor->Tag == Entity::EntityTypes::Wall)
	{
		/*if (side == Entity::Bottom || side == Entity::BottomRight || side == Entity::BottomLeft)
		{
			this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
			return;
		}*/

		//else
		{
			this->mPlayerData->player->SetState(new PlayerClingingState(this->mPlayerData));
			return;
		}
	}
	switch (side)
	{
	case Entity::Left:
		//if (mPlayerData->player->getMoveDirection() == Player::MoveToLeft)
		//{
		if (impactor->Tag == Entity::EntityTypes::Enemy && impactor->_Active==true && this->mPlayerData->player->invincible == false)
		{
			//this->mPlayerData->player->invincible = true;

			this->mPlayerData->player->AddPosition((data.RegionCollision.right - data.RegionCollision.left + FrameWidth / 2), -FrameHeight / 2);

			this->mPlayerData->player->SetState(new PlayerDyingState(this->mPlayerData));
			return;
		}
		
		else
		{
			if (impactor->Tag != Entity::EntityTypes::Enemy)
			{
				this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
				this->mPlayerData->player->SetVx(0);
			}
		}
		//}
		break;

	case Entity::Right:
		//if (mPlayerData->player->getMoveDirection() == Player::MoveToRight)
		//{
		if (impactor->Tag == Entity::EntityTypes::Enemy && impactor->_Active == true && this->mPlayerData->player->invincible == false)
		{
			//this->mPlayerData->player->invincible = true;

			this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left + FrameWidth / 2), -FrameHeight / 2);

			this->mPlayerData->player->SetState(new PlayerDyingState(this->mPlayerData));
			return;
		}
		else
		{
			if (impactor->Tag != Entity::EntityTypes::Enemy)
			{
				this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
				this->mPlayerData->player->SetVx(0);
			}
		}
		//}
		break;

	case Entity::Top:
		if (impactor->Tag == Entity::EntityTypes::Enemy&& impactor->_Active == true && this->mPlayerData->player->invincible == false)
		{
			//this->mPlayerData->player->invincible = true;

			this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left + FrameWidth / 2), -FrameHeight / 2);

			this->mPlayerData->player->SetState(new PlayerDyingState(this->mPlayerData));
			return;
		}
		
		break;

	case Entity::BottomLeft: case Entity::Bottom: case Entity::BottomRight:
		if (data.RegionCollision.right - data.RegionCollision.left >= 8.0f)

		{
			if (impactor->Tag == Entity::EntityTypes::Enemy&& impactor->_Active == true && this->mPlayerData->player->invincible == false)
			{
				//this->mPlayerData->player->invincible = true;

				this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left + FrameWidth / 2), -FrameHeight / 2);

				this->mPlayerData->player->SetState(new PlayerDyingState(this->mPlayerData));
				return;
			}
			
		else {	
				if (impactor->Tag == Entity::EntityTypes::Static)
 				{
					this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));

					if (isLeftOrRightKeyPressed)
					{
						this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
						return;
					}
					else
					{
						//if (impactor->Tag== Entity::EntityTypes::Stair)
						this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
						return;
					}
				}
		}
		}
		if (impactor->Tag == Entity::EntityTypes::Grass)
		{
			this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
			return;
		}
		return ;

	default:
		break;
	}
}
