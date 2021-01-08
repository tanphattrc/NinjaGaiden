#pragma once

#include "../../../GameComponents/Animation.h""
#include "../../Entity.h"
#include "../../DynamicGameObject/Player/Player.h"
#include "../../StaticGameObject/GameObject.h"
#include "Axe.h"

#define SPEED 10;
#define WALKING_STATE true
#define SHOOTING_STATE false

class Goblin : public GameObject
{
private:
	float time;
	float timeBullet;
	boolean state;
	vector<Axe*> bullet;
	int bulletTracking;
	int timePauseUpdate;
public:
	~Goblin();

	Goblin(D3DXVECTOR3 position);
	void Update(float dt);

	const char* FileName();
	int TotalFrame();
	int Row();
	int Column();
	float SecondPerFrame();

	vector<GameObject*> GetBullet() override;
	void setBullet();
	void turn();

	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side); // Test 8/5

};