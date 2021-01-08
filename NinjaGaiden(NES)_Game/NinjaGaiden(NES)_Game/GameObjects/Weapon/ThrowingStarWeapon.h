#pragma once
#include "Weapon.h"

class ThrowingStarWeapon : public Weapon
{
public:
	ThrowingStarWeapon(D3DXVECTOR3 position);
	~ThrowingStarWeapon();
	void Update(float dt);
};

