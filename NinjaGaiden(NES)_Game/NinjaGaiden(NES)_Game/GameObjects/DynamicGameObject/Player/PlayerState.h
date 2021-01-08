#pragma once
#include "PlayerData.h"
#include "../../Entity.h"
#include <map>

class PlayerState
{
public:
    enum StateName
    {
        Standing,
        Running,
        Falling,
        Jumping,
		StandingBeat,
		Sitting,
		SittingBeat,
        Die,
		Climbing,
		Clinging,
		UseWeapon
    };

    ~PlayerState();

    virtual void Update(float dt);

    virtual void HandleKeyboard();
	int IsKeyDown(int keyCode);
	virtual void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
	
    //ham thuan ao bat buoc phai ke thua
    virtual StateName GetState() = 0;

protected:
    PlayerState(PlayerData *playerData);
    PlayerState();

    PlayerData *mPlayerData;
};

