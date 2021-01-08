#include "PlayerClingingState.h"

PlayerClingingState::PlayerClingingState(PlayerData * playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
}

PlayerClingingState::~PlayerClingingState()
{
}

void PlayerClingingState::Update(float dt)
{
}

void PlayerClingingState::HandleKeyboard()
{
	if (IsKeyDown(DIK_SPACE))
	{
		if (mPlayerData->player->GetReserse())
		{
			this->mPlayerData->player->AddPosition(4, 0); // cho ra khỏi wall

		}
		else
		{
			this->mPlayerData->player->AddPosition(-4, 0);
		}
		this->mPlayerData->player->SetState(new PlayerJumpingState(this->mPlayerData));
		return;
	}
}

void PlayerClingingState::OnCollision(Entity * impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	if (impactor->Tag == Entity::EntityTypes::Enemy && impactor->_Active == true && this->mPlayerData->player->invincible == false)
	{
		//this->mPlayerData->player->invincible = true;
		
	}
}

PlayerState::StateName PlayerClingingState::GetState()
{
	return PlayerState::Clinging;
}
