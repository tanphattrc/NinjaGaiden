#pragma once

#include "../../../GameComponents/Animation.h""
#include "../../Entity.h"
#include "../../DynamicGameObject/Player/Player.h"
#include "../../StaticGameObject/GameObject.h"

#define SPEED 50;
#define RUNNING_STATE true;
#define JUMPING_STATE false;

class Runner : public GameObject
{
private:
	int turnLeft;
	bool state;
public:
	Runner(D3DXVECTOR3 position);
	~Runner();

	void Update(float dt);

	const char* FileName();
	int TotalFrame();
	void turn();
	int Row();
	int Column();
	float SecondPerFrame();

	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);
};
