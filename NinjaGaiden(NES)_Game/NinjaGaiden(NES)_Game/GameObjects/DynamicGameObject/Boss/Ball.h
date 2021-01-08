#pragma once
#include "../../../GameComponents/Animation.h""
#include "../../Entity.h"
#include "../../DynamicGameObject/Player/Player.h"
#include "../../StaticGameObject/GameObject.h"

#define SHOT true
#define STAY false
#define SPEED 50;

class Ball : public GameObject
{
private:
	float time;
	D3DXVECTOR3 originalPos;
	boolean state;
public:
	~Ball();
	Ball(D3DXVECTOR3 position);
	void Update(float dt);
	void turn(int dir);
	const char* FileName();
	int TotalFrame();
	int Row();
	int Column();
	float SecondPerFrame();
	void SetShot(boolean shot);
	void SetOriginalPosition(D3DXVECTOR3 position);

//	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side); // Test 8/5
};