#include "WindmillStarWeapon.h"

WindmillStarWeapon::WindmillStarWeapon(D3DXVECTOR3 position)
{
	GameObject  *object = new GameObject(position, "Resources/Item_Effect/WindmillStarWeapon.png", 1, 1, 1, 1);
	flag = 1;


	_Weapon.push_back(object);
	this->SetPosition(position);
	_Weapon[0]->SetPosition(position);
	this->SetWidth(_Weapon[0]->GetWidth());
	this->SetHeight(_Weapon[0]->GetHeight());
	this->TagWeapon = Entity::WeaponType::WindmillStarWeapon;
	oT = 65840;
	this->_Active = false;
	_Weapon[0]->_Active = false;
}

WindmillStarWeapon::~WindmillStarWeapon()
{
}

void WindmillStarWeapon::Update(float dt)
{
	
	{
		if (posX >= _boundLimit.right || posX <= _boundLimit.left || posY <= _boundLimit.top )
		{
			this->SetPosition(GetPosWeaponAtPlayer());
			vx = 0;
			vy = 0;
			_Active = false;
			oT = 65840;
		}
		if (oT >= 65931)
		{
			oT = 65840;
		}
		if (_Active)
		{
			oT+=1;
			
			Entity::CollisionReturn r = GameCollision::RecteAndRect(_Weapon[0]->GetBound(), _boundPlayer);

	
			if (r.IsCollided && oT>= 65885 )
			{
				_Active = false;
				oT = 65840;
			}
	    
		

		

		Entity::Update(dt);

	
			if (_direction2)
			{

				this->vx = ((100 * cos(2 * 3.14*0.01*oT + 3.14 / 2)) + GetPosWeaponAtPlayer().x) / dt;
				this->vy = (GetPosWeaponAtPlayer().y - 10 - this->posY);
				

			}
			else
			{

				this->vx = ((100 * cos(2 * 3.14*0.01*oT + -3.14 / 2)) + GetPosWeaponAtPlayer().x) / dt;
				this->vy = (GetPosWeaponAtPlayer().y - 10 - this->posY);

			}

			posX = vx * dt ;

			posY += vy * dt;

		




			//Entity::Update(dt);


			//GetPosWeaponAtPlayer().y


			_Weapon[0]->SetPosition(this->GetPosition());
		}
		else {
			this->SetPosition(GetPosWeaponAtPlayer());
		}
	}
	
}
