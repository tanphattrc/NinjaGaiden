#pragma once
#include "GameObject.h"

class BirdBrown : public GameObject
{
public:
	BirdBrown(D3DXVECTOR3 position);
	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side); // Test 8/5


	~BirdBrown();

	const char* FileName();
	int TotalFrame();
	int Row();
	int Column();
	float SecondPerFrame();


};