#pragma once

#include "../../../GameComponents/Animation.h""
#include "../../Entity.h"
#include "../../DynamicGameObject/Player/Player.h"
#include "../../StaticGameObject/GameObject.h"

#define SPEED 15;

class Swordman : public GameObject
{
private:
	bool falling = false;
public:
	~Swordman();
	Swordman(D3DXVECTOR3 position);
	void Update(float dt);

	const char* FileName();
	int TotalFrame();
	int Row();
	int Column();
	float SecondPerFrame();
	void turn();
	void checkPlayerPosition();
	void SetActive(bool variable) override;

	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side); // Test 8/5

};