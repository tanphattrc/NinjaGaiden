#pragma once
#include "../../../GameComponents/Animation.h""
#include "../../Entity.h"
#include "../../DynamicGameObject/Player/Player.h"
#include "../../StaticGameObject/GameObject.h"
#include "Ball.h"
#include <Windows.h>
#include <iostream>
#include <sstream>
#include "../../ExplosionEffect/ExplosionBoss.h"
#define SPEED 90;
#define STANDING_STATE true
#define JUMPING_STATE false

#define DBOUT( s )            \
{                             \
   std::wostringstream os_;    \
   os_ << s;                   \
   OutputDebugStringW( os_.str().c_str() );  \
}

class Boss : public GameObject
{
private:
	float time;
	int timeFlip;
	int timeBullet;
	boolean state;
	vector<Ball*> bullet;
	int bulletTracking;
	Animation *mAnimationJumpingState,
		*mAnimationStandingState;
	void changeAnimation(boolean _state);
	ExplosionBoss *e_Boss;
	float timeDie;
public:
	~Boss();
	Boss(D3DXVECTOR3 position);
	void Update(float dt);
	void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255, 255));
	void turn();
	const char* FileName();
	int TotalFrame();
	int Row();
	int Column();
	float SecondPerFrame();
	vector<GameObject*> GetBullet() override;
	void setBullet();

	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side); // Test 8/5
};