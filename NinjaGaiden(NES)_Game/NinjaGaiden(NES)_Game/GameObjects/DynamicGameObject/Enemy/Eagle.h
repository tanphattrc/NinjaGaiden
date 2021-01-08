#pragma once

#include "../../../GameComponents/Animation.h""
#include "../../Entity.h"
#include "../../DynamicGameObject/Player/Player.h"
#include "../../StaticGameObject/GameObject.h"
class Eagle : public GameObject
{
private:
	int turnLeft;
	float time;
	D3DXVECTOR3 playerPos;
	D3DXVECTOR3 startPos;
	float distance;
	float distanced;
	bool moving;
	D3DXVECTOR3 temp;
	D3DXVECTOR3 normalise;
	int oT;
	float direction;
	D3DXVECTOR2 directionVector;
	int timePauseUpdate;
public:
	~Eagle();

	Eagle(D3DXVECTOR3 position);
	void Update(float dt);

	const char* FileName();
	int TotalFrame();
	int Row();
	int Column();
	float SecondPerFrame();

	void turn();

	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side); // Test 8/5

};