#include "GameUI.h"


void GameUI::_initialize()
{
	

	
	_hpSprite = new Sprite("Resources/Item_Effect/heal.png");
	_boxWeapon = new Sprite("Resources/Item_Effect/BoxWeapon.png");
	_manaSprite = new Sprite("Resources/Item_Effect/mana.png");
	
	_gameTimer = 0;
	_gameStage = 1;
	_liveCount = 2;
	_playerHP = 16;
	_enemyHP = 16;
	_playerMana = 0;
}
GameUI::GameUI(LPDIRECT3DDEVICE9 d3ddev_, int size_, int screenWidth_, int screenHeight_)
{
	this->_initialize();
	
	_arial = new Font(d3ddev_, size_, screenWidth_, screenHeight_);
}
void GameUI::drawTable()
{
	// draw table
	
	//draw Box Weapon
	_boxWeapon->Draw(D3DXVECTOR3(115,8,0));
	//_Weapon->Draw(D3DXVECTOR3(95, 8, 0));
	// draw Mana
	_manaSprite->Draw(D3DXVECTOR3(45,50,0));
	// draw hp
	// Vẽ hình thứ 2 của HP sprite
	RECT rect;
	rect.left = _hpSprite->GetWidth() / 2;
	rect.right = _hpSprite->GetWidth();
	rect.top = 0;
	rect.bottom = _hpSprite->GetHeight();
	for (int i = 0; i < MAX_HP; i++)
	{
		_hpSprite->Draw(D3DXVECTOR3(150 + 7.5 * i, 30, 0), rect);
	}
	for (int i = 0; i < _playerHP; i++)
	{
		_hpSprite->Draw(D3DXVECTOR3(150 + 7.5 * i, 30, 0));
	}
	
	// boss
	for (int i = 0; i < MAX_HP; i++)
	{
		_hpSprite->Draw(D3DXVECTOR3(150 + 7.5 * i, 45, 0), rect);
	}
	for (int i = 0; i < _enemyHP; i++)
	{
		_hpSprite->Draw(D3DXVECTOR3(150 +7.5 * i, 45, 0));
	}
	



	
}

void GameUI::drawScore()
{
	
	_arial->onLost();
	

	_arial->render("Score:", 5, 0);
	
	_arial->render(_playerScore, 45, 0);

	_arial->render("TIME:", 5,20);
	_arial->render(_gameTimer / 1000, 40, 20);

	_arial->render("STAGE: 3 -", 150, 0);
	_arial->render(_gameStage, 215, 0);
	_arial->render("PLAYER:", 85, 23);
	_arial->render("ENEMY:", 90, 40);

	_arial->render("P:", 5, 40);
	_arial->render(_liveCount, 20, 40);

	_arial->render(_playerMana, 54, 42);
	
}

void GameUI::initTimer(int deltaTime_)
{
	_gameTimer = deltaTime_ * 1000;
}

int GameUI::getTimer()
{
	return _gameTimer / 1000;
}

void GameUI::SetTimer(int x)
{
	_gameTimer += x;
}



void GameUI::SetplayerScore(int x)
{
	_playerScore = x;
}

int GameUI::GetplayerScore()
{
	return _playerScore;
}

void GameUI::SetplayerHP(int x)
{
	_playerHP = x;
}

void GameUI::SetenemyHP(int x)
{
	_enemyHP = x;
}

int GameUI::GetplayerHP()
{
	return _playerHP;
}

int GameUI::GetenemyHP()
{
	return _enemyHP;
}

GameUI::GameUI(void)
{

}

void GameUI::Update(float dt)
{
	if (GameGlobal::Pause)
	{
		if (_gameTimer <= 0)
		{
			_playerHP = 0;

		}
		else
		{
			_gameTimer = _gameTimer - dt * 1000;
		}
	}
	
}

void GameUI::SetLiveCount(int x)
{
	_liveCount = x;
}

int GameUI::GetLiveCount()
{
	return _liveCount;
}

void GameUI::SetplayerMana(int x)
{
	_playerMana = x;
}

int GameUI::GetplayerMana()
{
	return _playerMana;
}
/*
 void GameUI::CheckRuleGame(GameUI * gameUI, Player * mPlayer, Entity * impactor)
{
	if (impactor->Tag == Entity::EntityTypes::Enemy&& impactor->_Active == true && mPlayer->invincible == false && mPlayer->getState() != PlayerState::StandingBeat &&  mPlayer->getState() != PlayerState::SittingBeat)
		{
			gameUI->SetplayerHP(gameUI->GetplayerHP() - 1);
			
			Sound::getInstance()->play("Injured", true, 0);
			
		}
		if (impactor->Tag == Entity::EntityTypes::Item && impactor->_allowPlayerpick == true  )//&& mPlayer->getState()!=PlayerState::StandingBeat)
		{
			
			Sound::getInstance()->play("PickItem", true, 0);
			if (impactor->TagItem == Entity::ItemType::BlueMana)
			{
				//gameUI->SetplayerScore(gameUI->Ge)
				gameUI->SetplayerMana(gameUI->GetplayerMana() + 5);
				mPlayer->setPlayerMana(gameUI->GetplayerMana());
				impactor->Hidden();
			}
			if (impactor->TagItem == Entity::ItemType::RedMana)
			{
				//gameUI->SetplayerScore(gameUI->Ge)
				gameUI->SetplayerMana(gameUI->GetplayerMana() + 10);
				mPlayer->setPlayerMana(gameUI->GetplayerMana());
				impactor->Hidden();
			}

			if (impactor->TagItem == Entity::ItemType::BlueBonus)
			{
				//gameUI->SetplayerScore(gameUI->Ge)
				gameUI->SetplayerScore(gameUI->GetplayerScore() + 500);
				impactor->Hidden();
			}
			if (impactor->TagItem == Entity::ItemType::RedBonus)
			{
				//gameUI->SetplayerScore(gameUI->Ge)
				gameUI->SetplayerScore(gameUI->GetplayerScore() + 1000);
				impactor->Hidden();
			}
			if (impactor->TagItem == Entity::ItemType::RedHP)
			{
				//gameUI->SetplayerScore(gameUI->Ge)
				gameUI->SetplayerHP(gameUI->GetplayerHP() + 6);
				Sound::getInstance()->play("BonusHP", true, 0);
				impactor->Hidden();
			}
			if (impactor->TagItem == Entity::ItemType::ThrowingStar)
			{

				impactor->SetPosition(-100, 14);
			
				mPlayer->mWeapon = new ThrowingStarWeapon(mPlayer->GetPosition());
				gameUI->_boxWeapon = new Sprite("Resources/Item_Effect/ThrowingStarBox.png");



			}
			if (impactor->TagItem == Entity::ItemType::WindmillStar)
			{
				impactor->Hidden();

				mPlayer->mWeapon = new WindmillStarWeapon(mPlayer->GetPosition());
				gameUI->_boxWeapon = new Sprite("Resources/Item_Effect/WindmillStarBox.png");
			}
			if (impactor->TagItem == Entity::ItemType::Fire)
			{
				impactor->Hidden();

				mPlayer->mWeapon = new FireWeapon(mPlayer->GetPosition());
				gameUI->_boxWeapon = new Sprite("Resources/Item_Effect/FireBox.png");
			}
			if (impactor->TagItem == Entity::ItemType::TimeFreeze)
			{

			}
		}
}
*/




GameUI::~GameUI(void)
{
}
