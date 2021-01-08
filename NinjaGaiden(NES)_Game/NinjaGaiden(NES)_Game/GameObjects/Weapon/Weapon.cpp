#include "Weapon.h"



Weapon::Weapon()
{
	mTimeHit = 5;
}

Weapon::Weapon(D3DXVECTOR3 postition)
{
	_amount = 1;
	
}


Weapon::~Weapon()
{
}

void Weapon::Update(float dt)
{
}

D3DXVECTOR3 Weapon::GetPosWeaponAtPlayer()
{
	return PosWeaponAtPlayer;
}

bool Weapon::getDirection()
{
	return _direction;
}

void Weapon::SetDirection(bool direction)
{
	_direction = direction;
}

bool Weapon::getDirection2()
{
	return _direction2;
}

void Weapon::SetDirection2(bool direction)
{
	_direction2 = direction;
}

void Weapon::setBoundLimit(RECT bound)
{
	_boundLimit = bound;
}

RECT Weapon::getBoundLimit()
{
	return _boundLimit;
}

void Weapon::setBoundplayer(RECT bound)
{
	_boundPlayer = bound;
}

RECT Weapon::getBoundplayer()
{
	return _boundPlayer;
}

void Weapon::SetPosLimitAtMap(D3DXVECTOR3 posLimit)
{
	PosLimitAtMap = posLimit;
}

D3DXVECTOR3 Weapon::GetPosLimitAtMap()
{
	return PosLimitAtMap;
}

int Weapon::getAmount()
{
	return _amount;
}

void Weapon::setAmount(int amount)
{
	_amount = amount;
}

void Weapon::GetPositionPlayer(D3DXVECTOR3 posPlayer)
{
	PosWeaponAtPlayer = posPlayer;
}



void Weapon::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	if (_Active)
	{
		for (int i = 0; i < _Weapon.size(); i++)
		{
			_Weapon[i]->Draw(_Weapon[i]->GetPosition(), sourceRect, scale, transform, angle, rotationCenter, colorKey);

		}
	}
}

std::vector<GameObject*> Weapon::GetWeapon()
{
	return _Weapon;
}

void Weapon::OnCollision(Entity * impactor,ExplosionHit *e_Hit ,Weapon* mWeapon,GameUI *gameUI, int indexWeapon)
{
	if (impactor->Tag == Entity::EntityTypes::Enemy && impactor->_Active == true)
	{
		impactor->_Active == false;

		if (impactor->TagEnemy == Entity::Boss)
		{
			mTimeHit--;
			if (mTimeHit <= 0)
			{
				impactor->_HP -= 1;
				gameUI->SetenemyHP(impactor->_HP);
				mTimeHit = 5;
			}
		}
		else
		//if ()   Xét loại Enemy để tính điểm
		{
			switch (impactor->TagEnemy)
			{
			case Entity::Swordman: case Entity ::Axe_E:
				gameUI->SetplayerScore(gameUI->GetplayerScore() + 100);
				break;
			case Entity::Paner: case Entity::Brute: case Entity::Cannoer: case Entity::Ball_E: case Entity::Runner:
				gameUI->SetplayerScore(gameUI->GetplayerScore() + 200);
				break;
			case Entity::Eagle: case Entity::Goblin:
				gameUI->SetplayerScore(gameUI->GetplayerScore() + 300);
				break;

			default:
				break;
			}
			e_Hit->_Active = true;
			e_Hit ->SetPosition ( impactor->GetPosition());
			//e_Hit = new ExplosionHit(impactor->GetPosition());
			impactor->Hidden();

		}
		Sound::getInstance()->play("BeatEnemy", true, 0);
		
		

		mWeapon->GetWeapon()[indexWeapon]->_Active = false;
		mWeapon->GetWeapon()[indexWeapon]->SetVx(0);
		mWeapon->GetWeapon()[indexWeapon]->SetVy(0);
		mWeapon->SetVx(0);
		mWeapon->SetVy(0);
		mWeapon->_Active = false;

	}
	if (impactor->Tag == Entity::EntityTypes::Item)
	{
		if (impactor->TagItem != Entity::ItemType::Container && impactor->_Active == false)
		{

			impactor->_Active = false;

			mWeapon->SetVx(0);
			mWeapon->SetVy(0);
			mWeapon->_Active = false;
		}
		impactor->OnCollision();


	}
	else
	{

	}

}
