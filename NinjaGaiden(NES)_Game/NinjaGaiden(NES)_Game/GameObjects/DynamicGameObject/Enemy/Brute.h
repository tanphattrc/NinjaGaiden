#pragma once

#include "../../../GameComponents/Animation.h""
#include "../../Entity.h"
#include "../../DynamicGameObject/Player/Player.h"
#include "../../StaticGameObject/GameObject.h"
#include "../Enemy/Bullet.h"

#define WALKING_STATE true
#define SHOOTING_STATE false

#define SPEED 10;

class Brute : public GameObject
{
private:
	float time;
	float timeBullet;
	boolean state;
	vector<Bullet*> bullet;
	float bulletTurn;
public:
	~Brute();

	Brute(D3DXVECTOR3 position);
	void Update(float dt);
	void turn();

	const char* FileName();
	int TotalFrame();
	int Row();
	int Column();

	vector<GameObject*> GetBullet() override;
	void setBullet();

	float SecondPerFrame();

	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side); // Test 8/5

};