#include "PlayerState.h"


PlayerState::PlayerState(PlayerData *playerData)
{
    this->mPlayerData = playerData;
}

PlayerState::PlayerState()
{

}

PlayerState::~PlayerState()
{
}

void PlayerState::Update(float dt)
{

}

void PlayerState::HandleKeyboard()
{

}

int PlayerState::IsKeyDown(int keyCode)
{
	return (GameGlobal::GetCurrentKeyState()[keyCode] & 0x80) > 0;

}

void PlayerState::OnCollision(Entity * impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	
}
