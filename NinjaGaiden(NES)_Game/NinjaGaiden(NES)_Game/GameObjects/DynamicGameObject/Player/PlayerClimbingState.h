#pragma once
#include "PlayerState.h"
#include "Player.h"
class PlayerClimbingState : public PlayerState
{
public:
	PlayerClimbingState(PlayerData *playerData);
	~PlayerClimbingState();
	void Update(float dt);
	

	void HandleKeyboard();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual StateName GetState();
protected:
	float acceleratorY;
};