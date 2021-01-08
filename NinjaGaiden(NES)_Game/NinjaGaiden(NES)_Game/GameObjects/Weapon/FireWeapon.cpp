#include "FireWeapon.h"



FireWeapon::FireWeapon(D3DXVECTOR3 position)
{
	GameObject  *object1 = new GameObject(position, "Resources/Item_Effect/FireWeapon.png", 1, 1, 1, 1);
	GameObject  *object2 = new GameObject(position, "Resources/Item_Effect/FireWeapon.png", 1, 1, 1, 1);
	GameObject  *object3 = new GameObject(position, "Resources/Item_Effect/FireWeapon.png", 1, 1, 1, 1);

	_Weapon.push_back(object1);
	_Weapon.push_back(object2);
	_Weapon.push_back(object3);
	this->SetPosition(position);
	for (int i = 0; i < _Weapon.size(); i++)
	{
		_Weapon[i]->SetPosition(position);
		this->SetWidth(_Weapon[i]->GetWidth());
		this->SetHeight(_Weapon[i]->GetHeight());
	}
	this->TagWeapon = Entity::WeaponType::FireWeapon;


}


FireWeapon::~FireWeapon()
{
}

void FireWeapon::Update(float dt)
{
	
	for (int i = 0; i < _Weapon.size(); i++)
	{
		if (_Weapon[i]->GetPosition().x >= _boundLimit.right || _Weapon[i]->GetPosition().x <= _boundLimit.left || _Weapon[i]->GetPosition().y <= 20)
		{
			_Weapon[i]->SetPosition(GetPosWeaponAtPlayer());
			this->SetVx(0);
			this->SetVy(0);
			//_Weapon[i]->SetVx(0);
			//_Weapon[i]->SetVy(0);
			_Weapon[i]->_Active = false;
			if (i == 0)
			{
				_Active = false;
			}
			
		}
		if (_Weapon[i]->_Active)
		{
			
			this->vx += 2;
			this->vy -= 4;
			if (!_direction2)
			{
				_Weapon[i]->SetVx(vx);
				_Weapon[i]->SetVy((vy));
				_Weapon[i]->SetPosition(_Weapon[i]->GetPosition().x + _Weapon[i]->GetVx()*(i+6)*dt, _Weapon[i]->GetPosition().y + _Weapon[i]->GetVy()*(sin(120)*(4)*dt));

			}
			else
			{
				_Weapon[i]->SetVx(-(vx));
				_Weapon[i]->SetVy((vy));
				//_Weapon[i]->Update(dt);
				_Weapon[i]->SetPosition(_Weapon[i]->GetPosition().x + _Weapon[i]->GetVx()*(i+6)*dt, _Weapon[i]->GetPosition().y + _Weapon[i]->GetVy()*(sin(120)*(4)*dt));

			}
			//Entity::Update(dt);
		}
		else
		{
			this->SetPosition(GetPosWeaponAtPlayer());
			_Weapon[i]->SetPosition(GetPosWeaponAtPlayer());
		}

	}




}
