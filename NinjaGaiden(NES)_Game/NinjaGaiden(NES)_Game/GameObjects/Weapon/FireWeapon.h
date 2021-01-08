#pragma once
#include "Weapon.h"
#define MAX_FIRE 9
class FireWeapon :public Weapon
{
public: 
	
	~FireWeapon();
	FireWeapon(D3DXVECTOR3 position);
	
	void Update(float dt);
};

