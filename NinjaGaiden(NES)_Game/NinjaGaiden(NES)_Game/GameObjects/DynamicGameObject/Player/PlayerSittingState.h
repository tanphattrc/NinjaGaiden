#pragma once
#include "PlayerState.h"
class PlayerSittingState : public PlayerState
{
public:
	PlayerSittingState(PlayerData *playerData);
	~PlayerSittingState();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
	void Update(float dt);

	void HandleKeyboard();

	virtual StateName GetState();

protected:
};

