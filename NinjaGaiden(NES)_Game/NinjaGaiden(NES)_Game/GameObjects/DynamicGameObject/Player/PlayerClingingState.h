#pragma once
#include "PlayerState.h"
#include "Player.h"
#include "PlayerJumpingState.h"

class PlayerClingingState : public PlayerState
{
public:
	PlayerClingingState(PlayerData *playerData);
	~PlayerClingingState();

	void Update(float dt);

	void HandleKeyboard();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
	virtual StateName GetState();

protected:
};

