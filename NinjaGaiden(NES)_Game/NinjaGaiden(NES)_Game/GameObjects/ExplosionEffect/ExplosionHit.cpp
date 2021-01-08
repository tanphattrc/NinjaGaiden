#include "ExplosionHit.h"





ExplosionHit::ExplosionHit()
{
}

ExplosionHit::ExplosionHit(D3DXVECTOR3 position)
{
	init(position);
	_Active = true;
	_timeSpawn = 0;
}

const char * ExplosionHit::FileName()
{
	return "Resources/Item_Effect/EffectHit.png";
}

int ExplosionHit::TotalFrame()
{
	return 3;
}

int ExplosionHit::Row()
{
	return 1;
}

int ExplosionHit::Column()
{
	return 3;
}

float ExplosionHit::SecondPerFrame()
{
	return 0.2;
}

ExplosionHit::~ExplosionHit()
{
}
