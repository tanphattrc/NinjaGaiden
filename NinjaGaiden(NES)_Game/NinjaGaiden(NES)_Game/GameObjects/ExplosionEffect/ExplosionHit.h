#pragma once
#include "../StaticGameObject/GameObject.h"
class ExplosionHit :public GameObject
{
public:
	ExplosionHit();
	ExplosionHit(D3DXVECTOR3 position);
	const char* FileName();
	int TotalFrame();
	int Row();
	int Column();
	float SecondPerFrame();
	
	~ExplosionHit();
};

