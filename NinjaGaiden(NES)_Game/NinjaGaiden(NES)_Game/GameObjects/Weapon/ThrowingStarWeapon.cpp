#include "ThrowingStarWeapon.h"



ThrowingStarWeapon::ThrowingStarWeapon(D3DXVECTOR3 position)
{
	_amount = 1;
	//= new GameObject(position,"Resources/Item_Effect/ThrowingStar.png",1,);
	GameObject  *object = new GameObject(position, "Resources/Item_Effect/ThrowingStarWeapon.png", 1, 1, 1, 1);

	
	
	_Weapon.push_back( object);
	this->SetPosition(position);
	_Weapon[0]->SetPosition(position);
	this->SetWidth(_Weapon[0]->GetWidth());
	this->SetHeight(_Weapon[0]->GetHeight());

	this->TagWeapon = Entity::WeaponType::ThrowingStarWeapon;
}


ThrowingStarWeapon::~ThrowingStarWeapon()
{
}

void ThrowingStarWeapon::Update(float dt)
{
	
	if (posX>= _boundLimit.right || posX <= _boundLimit.left || posY >= _boundLimit.bottom || posY <= _boundLimit.top)
	{
		this->SetPosition(GetPosWeaponAtPlayer());
		vx = 0;
		_Active = false;

	}
	if (_Active)
	{
		if (! _direction2)
		{
			this->vx += 10;
		}
		else
		{
			this->vx -=10 ;
		}
		
		Entity::Update(dt);
		//this->S
		_Weapon[0]->SetPosition(this->GetPosition());

	}
	else {
		this->SetPosition(GetPosWeaponAtPlayer());
	}
}
