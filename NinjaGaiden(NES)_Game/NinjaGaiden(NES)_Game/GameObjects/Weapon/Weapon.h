#pragma once
#include "../Entity.h"
#include "../../GameComponents/Sprite.h"
#include "../StaticGameObject/GameObject.h"
#include <vector>
#include"../../GameComponents/GameCollision.h"
#include "../../GameUI/GameUI.h"
#include "../../GameComponents/Sound.h"
#include "../ExplosionEffect/ExplosionHit.h"

class Weapon : public Entity
{
public:
	Weapon();
	Weapon(D3DXVECTOR3 position);
	~Weapon();
	void Update(float dt);
	void GetPositionPlayer(D3DXVECTOR3 posPlayer);
	D3DXVECTOR3 GetPosWeaponAtPlayer();
	bool getDirection();
	void SetDirection(bool direction);
	bool getDirection2();
	void SetDirection2(bool direction);
	void setBoundLimit(RECT bound);
	
	RECT getBoundLimit();
	void setBoundplayer(RECT bound);
	RECT getBoundplayer();
	void SetPosLimitAtMap(D3DXVECTOR3 posLimit);
	D3DXVECTOR3 GetPosLimitAtMap();
	int getAmount();
	void setAmount(int amount);
	void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 163, 177));
	std::vector<GameObject*> GetWeapon();
	void OnCollision(Entity *impactor ,ExplosionHit *e_Hit,Weapon*_Weapon,GameUI *gameUI ,int indexWeapon );

protected:
	std::vector<GameObject*> _Weapon;
	int mTimeHit;
	D3DXVECTOR3 PosWeaponAtPlayer;
	D3DXVECTOR3 PosLimitAtMap;
	bool _direction;

	bool _direction2;
	RECT _boundLimit;
	int _amount;
	RECT _boundPlayer;
};

