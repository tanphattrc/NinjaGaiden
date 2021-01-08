#include "PlayerJumpingState.h"
#include "PlayerStandingState.h"
#include "PlayerFallingState.h"
#include "../../..//GameDefine/GameDefine.h"

PlayerJumpingState::PlayerJumpingState(PlayerData *playerData)
{
    this->mPlayerData = playerData;
    this->mPlayerData->player->SetVy(Define::PLAYER_MIN_JUMP_VELOCITY);
	this->mPlayerData->player->isJummping = true;
    acceleratorY = 5.0f;
    acceleratorX = 6.0f;

    noPressed = false;
	this->mPlayerData->player->isUpdate = true;
	Sound::getInstance()->play("Jump", true, 0);
}


PlayerJumpingState::~PlayerJumpingState()
{

}

void PlayerJumpingState::Update(float dt)
{
    this->mPlayerData->player->AddVy(acceleratorY);    

    if (mPlayerData->player->GetVy() >= 0)
    {
	//	this->mPlayerData->player->isJummping = false;
        mPlayerData->player->SetState(new PlayerFallingState(this->mPlayerData));

        return;
    }
	
    if (noPressed)
    {
        if (mPlayerData->player->getMoveDirection() == Player::MoveToLeft)
        {
            //player dang di chuyen sang ben trai      
            if (mPlayerData->player->GetVx() < 0)
            {
                this->mPlayerData->player->AddVx(acceleratorX);

                if (mPlayerData->player->GetVx() > 0)
                    this->mPlayerData->player->SetVx(0);
            }
        }
        else if (mPlayerData->player->getMoveDirection() == Player::MoveToRight)
        {
            //player dang di chuyen sang phai   
            if (mPlayerData->player->GetVx() > 0)
            {
                this->mPlayerData->player->AddVx(-acceleratorX);

                if (mPlayerData->player->GetVx() < 0)
                    this->mPlayerData->player->SetVx(0);
            }
        }
	
		
    }
}

void PlayerJumpingState::HandleKeyboard()
{
	//if (keys[VK_SHIFT])
	//{
	//	mPlayerData->player->SetState(new PlayerStandingBeatState(this->mPlayerData));
	//	return;
	//	noPressed = false;


	//}

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

        noPressed = false; 
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
			noPressed = false;

        }
	

    }
	else 
		if (IsKeyDown(DIK_Z))
		{

			if (mPlayerData->player->GetVy() <= -60 || mPlayerData->player->GetVy()>=-acceleratorY*8)
			{
				mPlayerData->player->SetVy(Define::PLAYER_MAX_JUMP_VELOCITY/4);
			}

			this->mPlayerData->player->SetState(new PlayerStandingBeatState(this->mPlayerData));
			return;
		}
	
	else
	{
		noPressed = true;
	}
}

PlayerState::StateName PlayerJumpingState::GetState()
{
    return PlayerState::Jumping;
}

void PlayerJumpingState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	if (impactor->Tag == Entity::EntityTypes::Stair && side==Entity::Right)
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
		}

		else*/
		{
			this->mPlayerData->player->SetState(new PlayerClingingState(this->mPlayerData));
			return;
		}
	}
	switch (side)	
	{
	case Entity::Left:
	{
		if (impactor->Tag == Entity::EntityTypes::Enemy&& impactor->_Active == true && this->mPlayerData->player->invincible == false)
		{
			//this->mPlayerData->player->invincible = true;
			this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left + FrameWidth / 2, -FrameHeight / 2);
			//this->mPlayerData->player->isJummping = false;
			this->mPlayerData->player->SetState(new PlayerDyingState(this->mPlayerData));
			break;
		}
		else
		{
			if (impactor->Tag == Entity::EntityTypes::Static)
			{
				this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
				this->mPlayerData->player->SetVx(0);
			}
		}
		return;
	}

	case Entity::Right:

	{
		if (impactor->Tag == Entity::EntityTypes::Enemy&& impactor->_Active == true && this->mPlayerData->player->invincible == false)
		{
			//this->mPlayerData->player->invincible = true;

			this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left + FrameWidth / 2), -FrameHeight / 2);
			//this->mPlayerData->player->isJummping = false;
			this->mPlayerData->player->SetState(new PlayerDyingState(this->mPlayerData));
		}
		else
		{
			if (impactor->Tag == Entity::EntityTypes::Static)
			{
				this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
				this->mPlayerData->player->SetVx(0);
			}
		}
		return;
	}

	case Entity::TopRight: case Entity::TopLeft: case Entity::Top:
	{
		if (impactor->Tag == Entity::EntityTypes::Enemy && impactor->_Active == true && this->mPlayerData->player->invincible == false)
		{
			//this->mPlayerData->player->invincible = true;

			this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left + FrameWidth / 2), -FrameHeight / 2);
			//this->mPlayerData->player->isJummping = false;
			this->mPlayerData->player->SetState(new PlayerDyingState(this->mPlayerData));
		}
		else
		{
			//this->mPlayerData->player->AddPosition(0, data.RegionCollision.bottom - data.RegionCollision.top);
			//this->mPlayerData->player->SetVy(0);
		}
		break;
	}

	case Entity::BottomRight: case Entity::BottomLeft: case Entity::Bottom:
	{
		if (impactor->Tag == Entity::EntityTypes::Enemy && impactor->_Active == true && this->mPlayerData->player->invincible == false)
		{
			//this->mPlayerData->player->invincible = true;

			this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left + FrameWidth / 2), -FrameHeight / 2);
			//this->mPlayerData->player->isJummping = false;
			this->mPlayerData->player->SetState(new PlayerDyingState(this->mPlayerData));
		}
		else
			if (impactor->Tag == Entity::EntityTypes::Static)
			{
				this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
			}
	}

	default:
		break;
	}
}