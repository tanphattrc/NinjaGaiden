#include "PlayerStandingState.h"
#include "Player.h"
#include "PlayerFallingState.h"

#include "../../..//GameDefine/GameDefine.h"
#include "PlayerSittingState.h"


PlayerStandingState::PlayerStandingState(PlayerData *playerData)
{
    this->mPlayerData = playerData;
    this->mPlayerData->player->SetVx(0);
    this->mPlayerData->player->SetVy(0);
	//this->mPlayerData->player->isUpdate = true;
}


PlayerStandingState::~PlayerStandingState()
{
}

void PlayerStandingState::Update(float dt)
{
	

}

void PlayerStandingState::HandleKeyboard()
{
	if (IsKeyDown(DIK_DOWNARROW))
	{
		this->mPlayerData->player->SetState(new PlayerSittingState(this->mPlayerData));
		return;
	}
    if ( IsKeyDown(DIK_LEFTARROW)|| IsKeyDown(DIK_RIGHTARROW))
    {
        this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
        return;
    }
	/*if (IsKeyDown(DIK_UPARROW))
	{
		this->mPlayerData->player->SetState(new PlayerClimbingState (this->mPlayerData));
		return;
	}
	*/
	//if (IsKeyDown(DIK_Z))
	//{
	//	this->mPlayerData->player->SetState(new PlayerStandingBeatState(this->mPlayerData));
	//	return;
	//}
	//
	
}

void PlayerStandingState::OnCollision(Entity * impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	switch (side)
	{
	case Entity::Left:
	{
	
		

			//day Player ra phia ben phai de cho player khong bi xuyen qua object
			if (impactor->Tag == Entity::EntityTypes::Enemy&& impactor->_Active == true && this->mPlayerData->player->invincible ==false)

			{
				//this->mPlayerData->player->invincible = true;
				this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left + FrameWidth / 2, -FrameHeight / 2);

				this->mPlayerData->player->SetState(new PlayerDyingState(this->mPlayerData));
			}
			
		

		return ;
	}

	case Entity::Right:
	{
		//va cham phia ben phai player
		
			this->mPlayerData->player->allowMoveRight = false;

			if (impactor->Tag == Entity::EntityTypes::Enemy && impactor->_Active == true && this->mPlayerData->player->invincible ==false)
			{
				//this->mPlayerData->player->invincible = true;
				this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left + FrameWidth / 2), -FrameHeight / 2);
				this->mPlayerData->player->SetState(new PlayerDyingState(this->mPlayerData));
			}
			

			return;
		

	}

	case Entity::Top: case Entity::TopLeft: case Entity::TopRight:
		if (impactor->Tag == Entity::EntityTypes::Enemy&& impactor->_Active == true && this->mPlayerData->player->invincible == false)
		{
			//this->mPlayerData->player->invincible = true;
			this->mPlayerData->player->AddPosition(-FrameWidth, - FrameHeight/2);
			this->mPlayerData->player->SetState(new PlayerDyingState(this->mPlayerData));
		}
		break;




	case Entity::Bottom: case Entity::BottomLeft: case Entity::BottomRight:
	{
		////this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
		//if (impactor->Tag == Entity::EntityTypes::Enemy)
		//{
		//	this->mPlayerData->player->AddPosition(0, data.RegionCollision.bottom - data.RegionCollision.top);
		//	this->mPlayerData->player->SetState(new PlayerDyingState(this->mPlayerData));
		//}
			if (impactor->Tag == Entity::EntityTypes::Enemy && impactor->_Active == true && this->mPlayerData->player->invincible == false)
		{
			//this->mPlayerData->player->OnNoCollisionWithBottom();
			//this->mPlayerData->player->invincible = true;
			this->mPlayerData->player->AddPosition(data.RegionCollision.right-data.RegionCollision.left+FrameWidth/2,-FrameHeight/2);
			this->mPlayerData->player->SetState(new PlayerDyingState(this->mPlayerData));
			return;
		}
			else
			{
				if (impactor->Tag == Entity::EntityTypes::Static)
				{
					this->mPlayerData->player->SetVy(0);
					return;

				}
			}

	}
	}
}

PlayerState::StateName PlayerStandingState::GetState()
{
    return PlayerState::Standing;
}
