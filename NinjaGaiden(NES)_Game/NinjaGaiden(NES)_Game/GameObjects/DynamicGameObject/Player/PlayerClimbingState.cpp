#include "PlayerClimbingState.h"

PlayerClimbingState::PlayerClimbingState(PlayerData * playerData)
{
	this->mPlayerData = playerData;
	acceleratorY = 3;
	this->mPlayerData->player->SetVy(0);
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->isOnStair = true;
	this->mPlayerData->player->isUpdate = true;
}

PlayerClimbingState::~PlayerClimbingState()
{
}

void PlayerClimbingState::Update(float dt)
{
	if (mPlayerData->player->GetReserse())
	{
		mPlayerData->player->SetReverse(false);
	}
	if (this->mPlayerData->player->GetPosition().y >= 135) // Vị trí dựng state của cầu thang thứ 2
	{
		this->mPlayerData->player->isOnStair = false;
		this->mPlayerData->player->SetVy(0);
	}
}

void PlayerClimbingState::HandleKeyboard()
{
	if (IsKeyDown(DIK_UPARROW) && this->mPlayerData->player->isOnStair == true)
	{
		if (this->mPlayerData->player->GetVy() > -Define::PLAYER_MAX_CLIMBING_SPEED)
		{
			this->mPlayerData->player->AddVy(-acceleratorY);

			if (this->mPlayerData->player->GetVy() < -Define::PLAYER_MAX_CLIMBING_SPEED)
			{
				this->mPlayerData->player->SetVy(-Define::PLAYER_MAX_CLIMBING_SPEED);
			}
		}
		this->mPlayerData->player->isUpdate = true;
		return;
	}
	
	if (IsKeyDown(DIK_DOWNARROW) && this->mPlayerData->player->isOnStair == true)
	{
		//this->mPlayerData->player->AddVy(acceleratorY);
		if (this->mPlayerData->player->GetVy() < Define::PLAYER_MAX_CLIMBING_SPEED)
		{
			this->mPlayerData->player->AddVy(acceleratorY);

			if (this->mPlayerData->player->GetVy() >= Define::PLAYER_MAX_CLIMBING_SPEED)
			{
				this->mPlayerData->player->SetVy(Define::PLAYER_MAX_CLIMBING_SPEED);
			}
		}
		this->mPlayerData->player->isUpdate = true;
	}
	else
	{
		this->mPlayerData->player->SetVy(0);
		
	}
	if (IsKeyDown(DIK_SPACE))
	{
		this->mPlayerData->player->AddPosition(-4, 0); // cho ra khỏi thang
		this->mPlayerData->player->SetState(new PlayerJumpingState(this->mPlayerData));
		return;
	}
	//this->mPlayerData->player->
}

void PlayerClimbingState::OnCollision(Entity * impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{

	if (impactor->Tag == Entity::EntityTypes::StairTop)
	{
		this->mPlayerData->player->isOnStair = true;
		this->mPlayerData->player->SetVy(acceleratorY);
		
	}
	if (impactor->Tag == Entity::EntityTypes::StairBottom)
	{
		this->mPlayerData->player->isOnStair = false;
	
		this->mPlayerData->player->SetPosition(1080, 117); // Vị trí tạm trước khi lên thang
		this->mPlayerData->player->SetState(new PlayerSittingState(this->mPlayerData));
		return;

	}
	if (side== Entity::SideCollisions::Right && impactor->Tag == Entity::EntityTypes::Stair)
	
	{
		
		
	}
	else
	{
		
	}
	if (side == Entity::SideCollisions::Left)
	{
		this->mPlayerData->player->SetState(new PlayerFallingState(this->mPlayerData));

		return;
	}
	if (impactor->Tag == Entity::EntityTypes::Enemy && impactor->_Active == true && this->mPlayerData->player->invincible == false)
	{
		//this->mPlayerData->player->invincible = true;

	}
	
	
}

PlayerState:: StateName PlayerClimbingState::GetState()
{
	return PlayerState::StateName::Climbing;
}
