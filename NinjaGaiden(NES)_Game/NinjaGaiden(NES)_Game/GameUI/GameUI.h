#pragma once
//#include "Sprite.h"
//#include "TextureManager.h"
#include "Font.h"
#include <vector>
#include "../GameComponents/Sprite.h"
//#include "../GameObjects/DynamicGameObject/Player/Player.h"
#include "../GameComponents/Sound.h"
using namespace std;

#define MAX_HP 16

class GameUI
{
protected:
	//GSprite* _sprite;
	Sprite *_manaSprite;

	//Sprite *_Weapon;

	Font* _arial;
	int _playerScore;
	int _gameTimer;
	int _gameStage;
	//int _weaponCount;
	int _playerHP;
	int _enemyHP;
	int _playerMana;
	int _liveCount;
	
	Sprite* _hpSprite;
	void _initialize();


public:
	GameUI(void);
	GameUI(LPDIRECT3DDEVICE9 d3ddev_, int size_, int screenWidth_, int screenHeight_);
	void drawTable();
	void drawScore();
	// deltaTime is in second
	void initTimer(int deltaTime_);
	int getTimer(); // return Time left of game in second
	void SetTimer(int x);
	//int GetWeaponCount();
	//void SetWeaponCount(int x);
	void SetplayerScore(int x);
	int GetplayerScore();
	void SetplayerHP(int x);
	void SetenemyHP(int x);
	int GetplayerHP();
	int GetenemyHP();
	void Update(float dt);
	void SetLiveCount(int x);
	int GetLiveCount();
	void SetplayerMana(int x);
	int GetplayerMana();
	//void CheckRuleGame(GameUI *gameUI, Player *mPlayer, Entity *impactor);
	// deltaTime_ is in milisecond
	Sprite * _boxWeapon;


	~GameUI(void);
};

