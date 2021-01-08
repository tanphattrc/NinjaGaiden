#pragma once
#include "Player.h"
#include "PlayerState.h"
#include "PlayerStandingBeatState.h"

class PlayerJumpingState : public PlayerState
{
public:
    PlayerJumpingState(PlayerData *playerData);
    ~PlayerJumpingState();

    void Update(float dt);

    void HandleKeyboard();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
    virtual StateName GetState();

protected:
    //do bien tien van toc sau moi frame tinh bang pixel / s
    float acceleratorY;
    float acceleratorX;
    bool noPressed;
    bool allowMoveRight, allowMoveLeft;
};

