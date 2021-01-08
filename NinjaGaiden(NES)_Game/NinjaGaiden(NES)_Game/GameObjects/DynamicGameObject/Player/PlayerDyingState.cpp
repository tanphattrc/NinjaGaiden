#include "PlayerDyingState.h"





PlayerDyingState::PlayerDyingState(PlayerData * playerData)
{
	this->mPlayerData = playerData;
	//this->mPlayerData->player->SetPosition(this->mPlayerData->player->GetPosition());
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
	this->mPlayerData->player->isJummping = false;
	
	
}

PlayerDyingState::~PlayerDyingState()
{

}

void PlayerDyingState::Update(float dt)
{
	this->mPlayerData->player->OnNoCollisionWithBottom();
	
}

void PlayerDyingState::OnCollision(Entity * impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	
	/*switch (side)
	{
	case Entity::Left:
		if (mPlayerData->player->getMoveDirection() == Player::MoveToLeft)
		{
			this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
			this->mPlayerData->player->SetVx(0);
		}
		break;

	case Entity::Right:
		if (mPlayerData->player->getMoveDirection() == Player::MoveToRight)
		{
			this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
			this->mPlayerData->player->SetVx(0);
		}
		break;

	case Entity::Top:
		break;

	case Entity::Bottom:
	case Entity::BottomRight:
	case Entity::BottomLeft:
		if (data.RegionCollision.right - data.RegionCollision.left >= 8.0f)
		{
			this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));

			
			
				this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
			
		}
		return;

	default:
		break;
	}*/

}

PlayerState:: StateName PlayerDyingState::GetState()
{
	return PlayerState::Die;
}
