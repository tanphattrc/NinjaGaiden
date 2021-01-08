#pragma once

#include "PlayerState.h"
#include "Player.h"
#include "../../ExplosionEffect/ExplosionHit.h"
class PlayerStandingBeatState : public PlayerState
{
public:
	PlayerStandingBeatState(PlayerData *playerData);
	~PlayerStandingBeatState();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
	void Update(float dt);

	void HandleKeyboard();

	virtual StateName GetState();


protected:
	float                       mTimePerFrame, //thoi gian luan chuyen 1 frame
		mCurrentTotalTime,//tong thoi gian hien tai de thuc hien timeperframe
	mTimeChangeState;
	int mTimeHit;

	//bool isLeftOrRightKeyPressed;
	//float acceleratorY,
	//	acceleratorX;

};

