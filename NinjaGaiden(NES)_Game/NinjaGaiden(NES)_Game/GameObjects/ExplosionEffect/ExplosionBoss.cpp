#include "ExplosionBoss.h"





ExplosionBoss::ExplosionBoss()
{
}

ExplosionBoss::ExplosionBoss(D3DXVECTOR3 position)
{
	init(position);
	_Active = true;
	_timeSpawn = 0;
}

const char * ExplosionBoss::FileName()
{
	return "Resources/Item_Effect/EffectBossDie.png";
}

int ExplosionBoss::TotalFrame()
{
	return 2;
}

int ExplosionBoss::Row()
{
	return 1;
}

int ExplosionBoss::Column()
{
	return 2;
}

float ExplosionBoss::SecondPerFrame()
{
	return 0.2;
}

ExplosionBoss::~ExplosionBoss()
{
}
