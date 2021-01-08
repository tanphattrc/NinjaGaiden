#pragma once
#include "../StaticGameObject/GameObject.h"
class ExplosionBoss :public GameObject
{
public:
	ExplosionBoss();
	ExplosionBoss(D3DXVECTOR3 position);
	const char* FileName();
	int TotalFrame();
	int Row();
	int Column();
	float SecondPerFrame();

	~ExplosionBoss();
};

