#pragma once
#include "PlayerState.h"
#include "Player.h"
#include "PlayerStandingState.h"
class PlayerDyingState :
	public PlayerState
{
public:
	PlayerDyingState(PlayerData *playerData);
	~PlayerDyingState();
	void Update(float dt);
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
	virtual StateName GetState();
protected:
	
};

