#pragma once

#include "../../../GameComponents/Animation.h""
#include "../../Entity.h"
//#include "../../DynamicGameObject/Player/Player.h"
#include "../../StaticGameObject/GameObject.h"

#define SPEED 100; 

#include <Windows.h>
#include <iostream>
#include <sstream>

#define DBOUT( s )            \
{                             \
   std::wostringstream os_;    \
   os_ << s;                   \
   OutputDebugStringW( os_.str().c_str() );  \
}


class Panther : public GameObject
{
private:
	int turnLeft;
	int timePauseUpdate;
public:
	~Panther();

	Panther(D3DXVECTOR3 position);
	void Update(float dt);

	void turn();

	const char* FileName();
	int TotalFrame();
	int Row();
	int Column();
	float SecondPerFrame();

	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side); // Test 8/5

};