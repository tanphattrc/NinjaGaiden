//#include "PlayerStandingState.h"
//#include "Player.h"
//#include "PlayerFallingState.h"
//#include "../../GameDefines/GameDefine.h"
#include "Player.h"
#include "PlayerSittingState.h"
#include "../../..//GameDefine/GameDefine.h"
#include "PlayerStandingState.h"
#include "PlayerSittingBeatState.h"

PlayerSittingState::PlayerSittingState(PlayerData *playerData)
{
	this->mPlayerData = playerData;

	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
	//this->mPlayerData->player->isUpdate = true;
}


PlayerSittingState::~PlayerSittingState()
{
}

void PlayerSittingState::OnCollision(Entity * impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	switch (side)
	{
	case Entity::Left:
	{



		//day Player ra phia ben phai de cho player khong bi xuyen qua object
		if (impactor->Tag == Entity::EntityTypes::Enemy && impactor->_Active == true && this->mPlayerData->player->invincible == false)

		{
			//this->mPlayerData->player->invincible = true;
			this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left + FrameWidth / 2, -FrameHeight / 2);

			this->mPlayerData->player->SetState(new PlayerDyingState(this->mPlayerData));
		}



		return;
	}

	case Entity::Right:
	{
		//va cham phia ben phai player

		this->mPlayerData->player->allowMoveRight = false;

		if (impactor->Tag == Entity::EntityTypes::Enemy && impactor->_Active == true && this->mPlayerData->player->invincible == false)
		{
			//this->mPlayerData->player->invincible = true;
			this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left + FrameWidth / 2), -FrameHeight / 2);
			this->mPlayerData->player->SetState(new PlayerDyingState(this->mPlayerData));
		}


		return;


	}

	case Entity::Top: case Entity::TopLeft: case Entity::TopRight:
		if (impactor->Tag == Entity::EntityTypes::Enemy && impactor->_Active == true && this->mPlayerData->player->invincible == false)
		{
			//this->mPlayerData->player->invincible = true;
			this->mPlayerData->player->AddPosition(-FrameWidth/2, -FrameHeight/2);
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
		if (impactor->Tag == Entity::EntityTypes::Enemy&& impactor->_Active == true && this->mPlayerData->player->invincible==false)
		{
			//this->mPlayerData->player->OnNoCollisionWithBottom();
			//this->mPlayerData->player->invincible = true;
			this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left + FrameWidth / 2, -FrameHeight/2);
			this->mPlayerData->player->SetState(new PlayerDyingState(this->mPlayerData));
			return;
		}
		else
			//if (impactor->Tag == Entity::EntityTypes::Static)
			//{
				this->mPlayerData->player->SetVy(0);
			//}

		return;
	}
	}
}

void PlayerSittingState::Update(float dt)
{

}

void PlayerSittingState::HandleKeyboard()
{
	if (IsKeyDown(DIK_LEFTARROW) || IsKeyDown(DIK_RIGHTARROW))
	{
		this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
		return;
	}
	if (IsKeyDown(DIK_UPARROW))
	{
		this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
		return;
	}
	if (IsKeyDown(DIK_Z))
	{
		this->mPlayerData->player->SetState(new PlayerSittingBeatState(this->mPlayerData));
		return;
	}
	
}

PlayerState::StateName PlayerSittingState::GetState()
{
	return PlayerState::Sitting;
}
