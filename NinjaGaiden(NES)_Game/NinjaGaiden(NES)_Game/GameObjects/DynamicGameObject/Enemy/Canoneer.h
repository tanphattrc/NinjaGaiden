#pragma once
#include "../../../GameComponents/Animation.h""
#include "../../Entity.h"
#include "../../DynamicGameObject/Player/Player.h"
#include "../../StaticGameObject/GameObject.h"
#include "../Enemy/Rocket.h"

#define WALKING_STATE true
#define SHOOTING_STATE false

#define SPEED 0;

class Canoneer : public GameObject
{
private:
	float time;
	float timeBullet;
	boolean state;
	vector<Rocket*> bullet;
	boolean spriteState;
public:
	~Canoneer();
	Canoneer(D3DXVECTOR3 position);
	void Update(float dt);
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