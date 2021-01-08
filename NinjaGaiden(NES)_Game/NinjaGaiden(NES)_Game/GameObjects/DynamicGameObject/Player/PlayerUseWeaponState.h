#pragma once
#include "PlayerState.h"
#include "Player.h"
#include "../../ExplosionEffect/ExplosionHit.h"
class PlayerUseWeaponState :
	public PlayerState
{
public:
	PlayerUseWeaponState(PlayerData *playerData);
	~PlayerUseWeaponState();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
	void Update(float dt);

	void HandleKeyboard();

	virtual StateName GetState();
protected:
	float                       mTimePerFrame, //thoi gian luan chuyen 1 frame
		mCurrentTotalTime; //tong thoi gian hien tai de thuc hien timeperframe
};

