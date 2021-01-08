#pragma once
#include "Weapon.h"

class WindmillStarWeapon : public Weapon
{
public:
	WindmillStarWeapon(D3DXVECTOR3 position);
	~WindmillStarWeapon();
	void Update(float dt);
private:
	int flag;
	int oT;
};

