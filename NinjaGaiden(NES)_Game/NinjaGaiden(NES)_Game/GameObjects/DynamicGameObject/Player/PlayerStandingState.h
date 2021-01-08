#pragma once
#include "PlayerState.h"

class PlayerStandingState : public PlayerState
{
public:
    PlayerStandingState(PlayerData *playerData);
    ~PlayerStandingState();

    void Update(float dt);

    void HandleKeyboard();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
    virtual StateName GetState();

protected:
};

