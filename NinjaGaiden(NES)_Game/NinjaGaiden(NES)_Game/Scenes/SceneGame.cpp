#include "SceneGame.h"
#include "../GameControllers/SceneManager.h"
#include "SceneEndGame.h"
#include "SceneScoreGame.h"

SceneGame::SceneGame(int _level)
{
	level = _level;
	LoadContent();
}

SceneGame::~SceneGame()
{
	delete mMap;
	delete mCamera;
	delete mPlayer;
	delete gameUI;
	for (size_t i = 0; i < listObject.size(); i++)
	{
		if (listObject[i])
			delete listObject[i];
	}
	listObject.clear();

}

void SceneGame::LoadContent()
{
	mPlayer = new Player();
	Sound::getInstance()->LoadAllSound();
	gameUI = new GameUI(GameGlobal::GetCurrentDevice(), 16, GameGlobal::GetWidth(), GameGlobal::GetHeight());
	mCamera = new Camera(GameGlobal::GetWidth(), GameGlobal::GetHeight());

	if (GameGlobal::ContinueGame)
	{
		LoadSaveGame();
	}
	else
	{
		mPlayer->SetPosition(InitPosPlayer());

		mCamera->SetPosition(GameGlobal::GetWidth() / 2,
			GameGlobal::GetHeight() / 2);

		gameUI->initTimer(150);
	}
	Sound::getInstance()->play("Level" + to_string(level), true,0,1);

	mMap = new GameMap(level);
	

	mMap->SetCamera(mCamera);
	
	mPlayer->SetCamera(mCamera);
	
	// Load player vào Object
	for (int i = 0; i < mMap->GetListObject().size(); i++)
	{
		if (mMap->GetListObject()[i]->Tag == Entity::EntityTypes::Enemy && mMap->GetListObject()[i]->TagWeapon==Entity::NoneWeapon)
		{
			mMap->GetListObject()[i]->GetPLayer(mPlayer);
			listObject.push_back(mMap->GetListObject().at(i));
		}
		if (mMap->GetListObject()[i]->TagEnemy == Entity::Boss)
		{
			mMap->GetListObject()[i]->_HP = gameUI->GetenemyHP();
		}
	}
}

void SceneGame::Update(float dt)
{

	if (gameUI->GetenemyHP() <= 0)
	{
		if (gameUI->getTimer() == 0)
		{
			Sound::getInstance()->stop("BonusScoreBoss");
			f_score.open("Resources/Score.txt", ios::out | ios::app);
			f_score << gameUI->GetplayerScore() << endl;
			f_score.close();
			SceneManager::GetInstance()->ReplaceScene(new SceneScoreGame(gameUI->GetplayerScore()));
		return;
		}
		
	}
	if (gameUI->GetLiveCount() < 0)
	{
		SceneManager::GetInstance()->ReplaceScene(new SceneGameOver(level));
		return;
	}
	if (IsKeyDown(DIK_P))
	{
		GameGlobal::Pause = !GameGlobal::Pause;
		if (GameGlobal::Pause)
		{
			Sound::getInstance()->setVolume(100, "Level" + to_string(level));


		}
		else
		{
			Sound::getInstance()->setVolume(0, "Level" + to_string(level));
			Sound::getInstance()->play("Pause", true, 0);

		}
	
	}
	if (IsKeyDown(DIK_F4))
	{
		SaveGame();
	}
	if (IsKeyDown(DIK_Z))
	{
		mPlayer->OnKeyUp(DIK_Z);

		mPlayer->OnKeyPressed(DIK_Z);
	}
	if (IsKeyDown(DIK_C))
	{

		mPlayer->OnKeyUp(DIK_C);

		mPlayer->OnKeyPressed(DIK_C);
		
		
	
	}
	if (IsKeyDown(DIK_SPACE))
	{
		mPlayer->OnKeyUp(DIK_SPACE);
		mPlayer->OnKeyPressed(DIK_SPACE);
	}
#pragma region - UI update-
	gameUI->SetplayerMana(mPlayer->getPlayerMana());
	gameUI->Update(dt);
#pragma endregion

	checkRuleGame();

	mMap->Update(dt);

	mPlayer->HandleKeyboard();
	mPlayer->Update(dt);

	CheckCameraAndWorldMap();
	

}

void SceneGame::Draw()
{
	mMap->Draw();
	mPlayer->Draw();
	gameUI->drawTable();
	gameUI->drawScore();
}

void SceneGame::OnKeyDown(int keyCode)
{

}

void SceneGame::OnKeyUp(int keyCode)
{

}


int SceneGame::IsKeyDown(int KeyCode)
{
	
		//if (GameGlobal::getCurrentKeypress()[KeyCode]==true)
			return (GameGlobal::GetCurrentKeyState()[KeyCode] & 0x80) > 0;

	
	
}

void SceneGame::SaveGame()
{
	fstream f_Save;
	f_Save.open("Resources/SaveGame.txt", ios::out);
	for (int i = 0; i < 12; i++)
	{
		switch (i)
		{
		case 0:
			f_Save << mPlayer->GetPosition().x << endl;
			break;
		case 1:
			f_Save << mPlayer->GetPosition().y << endl;
			break;
		case 2:
			f_Save << gameUI->GetplayerScore() << endl;

			break;
		case 3:
			f_Save << gameUI->getTimer() << endl;
			break;
		case 4:
			f_Save << gameUI->GetplayerMana() << endl;
			break;
		case 5:
			if (mPlayer->mWeapon)
			{
				if (mPlayer->mWeapon->TagWeapon == Entity::ThrowingStarWeapon)
				{
					f_Save << 1 << endl;
				}
				if (mPlayer->mWeapon->TagWeapon == Entity::FireWeapon)
				{
					f_Save << 2 << endl;
				}
				if (mPlayer->mWeapon->TagWeapon == Entity::WindmillStarWeapon)
				{
					f_Save << 3 << endl;
				}
			}
			else
			{
				f_Save << 0 << endl;
			}
			break;
		case 6:
			f_Save << gameUI->GetplayerHP() << endl;

			break;
		case 7:
			f_Save << gameUI->GetenemyHP() << endl;
			break;
		case 8:
			f_Save << level << endl;
				break;
		case 9:
			f_Save << gameUI->GetLiveCount() << endl;
			break;
		case 10:
			f_Save << mCamera->GetPosition().x << endl;
			break;
		case 11:
			f_Save << mCamera->GetPosition().y << endl;
			break;
		default:
			break;
		}

	}
	f_Save.close();
}

void SceneGame::LoadSaveGame()
{
	fstream f_Save;
	f_Save.open("Resources/SaveGame.txt");
	float posX, posY, score, time, mana, idWeapon, playerHP, enemyHP, liveCount, posXcamera, posYcamera;
	while (!f_Save.fail())
	{
		f_Save >> posX >> posY >> score >> time >> mana >> idWeapon >> playerHP >> enemyHP >> level >> liveCount >> posXcamera >> posYcamera;
	}
	f_Save.close();

	mPlayer->SetPosition(posX, posY);
	gameUI->SetplayerScore(score);
	gameUI->initTimer(time);
	gameUI->SetplayerMana(mana);
	mPlayer->setPlayerMana(mana);
	if (idWeapon == 1)
	{
		mPlayer->mWeapon = new ThrowingStarWeapon(mPlayer->GetPosition());
		gameUI->_boxWeapon = new Sprite("Resources/Item_Effect/ThrowingStarBox.png");
	}
	if (idWeapon == 2)
	{
		mPlayer->mWeapon = new FireWeapon(mPlayer->GetPosition());
		gameUI->_boxWeapon = new Sprite("Resources/Item_Effect/FireBox.png");
	}
	if (idWeapon == 3)
	{
		mPlayer->mWeapon = new WindmillStarWeapon(mPlayer->GetPosition());
		gameUI->_boxWeapon = new Sprite("Resources/Item_Effect/WindmillStarBox.png");
	}
	gameUI->SetplayerHP(playerHP);
	if (level == 3)
	{
		gameUI->SetenemyHP(enemyHP);
	}
	gameUI->SetLiveCount(liveCount);
	mCamera->SetPosition(posXcamera, posYcamera);

}







void SceneGame::CheckCameraAndWorldMap()
{
	mCamera->SetPosition(mPlayer->GetPosition());

	if (mCamera->GetBound().left < 0)
	{
		//vi position cua camera ma chinh giua camera
		//luc nay o vi tri goc ben trai cua the gioi thuc
		mCamera->SetPosition(mCamera->GetWidth() / 2, mCamera->GetPosition().y);
	}

	if (mCamera->GetBound().right > mMap->GetWidth())
	{
		//luc nay cham goc ben phai cua the gioi thuc
		mCamera->SetPosition(mMap->GetWidth() - mCamera->GetWidth() / 2,
			mCamera->GetPosition().y);
	}

	if (mCamera->GetBound().top < 0)
	{
		//luc nay cham goc tren the gioi thuc
		mCamera->SetPosition(mCamera->GetPosition().x, mCamera->GetHeight() / 2);
	}

	if (mCamera->GetBound().bottom > mMap->GetHeight())
	{
		//luc nay cham day cua the gioi thuc
		mCamera->SetPosition(mCamera->GetPosition().x,
			mMap->GetHeight() - mCamera->GetHeight() / 2);
	}
}



D3DXVECTOR2 SceneGame::InitPosPlayer()
{
	return D3DXVECTOR2(50,114);
}



void SceneGame::checkRuleGame()
{

	for (size_t i = 0; i < listObject.size(); i++)
	{
		if (listObject.at(i)->_Active == true)
		{
			vector<Entity*> listCollisionWithObject;
			mMap->GetQuadTree()->getEntitiesCollideAble(listCollisionWithObject, listObject.at(i));
			for (size_t j = 0; j < listCollisionWithObject.size(); j++)
			{
				if (listCollisionWithObject.at(j)->Tag == Entity::EntityTypes::Static)
				{
					Entity::CollisionReturn m = GameCollision::RecteAndRect(listObject.at(i)->GetBound(),
						listCollisionWithObject.at(j)->GetBound());
					if (m.IsCollided)
					{
						//Lay phia va cham cua Entity voi nhau
						Entity::SideCollisions sideEntity = GameCollision::getSideCollision(listObject.at(i), m);
						listObject.at(i)->OnCollision(listCollisionWithObject.at(j), m, sideEntity);
					}
				}

			}
		}
	}
	/*su dung de kiem tra xem khi nao ninja khong dung tren 1 object hoac
	dung qua sat mep trai hoac phai cua object do thi se chuyen state la falling*/
	int widthBottom = 0;
	
	vector<Entity*> listCollisionWithPlayer, listCollisionWithWeaponPlayer;

	// Lấy danh sách có khả năng va chạm với Player
	mMap->GetQuadTree()->getEntitiesCollideAble(listCollisionWithPlayer, mPlayer);
	
	for (size_t i = 0; i < listCollisionWithPlayer.size(); i++)
	{
		
	

#pragma region - Collision with Wepaon
		if (mPlayer->mWeapon &&mPlayer->mWeapon->_Active)
		{
			for (int j = 0; j < mPlayer->mWeapon->GetWeapon().size(); j++)
			{
				if (mPlayer->mWeapon->GetWeapon()[j]->_Active)
				{
					Entity::CollisionReturn r2 = GameCollision::RecteAndRect(mPlayer->mWeapon->GetWeapon()[j]->GetBound(), listCollisionWithPlayer.at(i)->GetBound());
					if (r2.IsCollided)
					{
						mPlayer->mWeapon->OnCollision(listCollisionWithPlayer.at(i),mPlayer->e_Hit,mPlayer->mWeapon,gameUI,j );						
					}
				}
			}
		}
#pragma endregion

#pragma region - Collision With Player -
		Entity::CollisionReturn r = GameCollision::RecteAndRect(mPlayer->GetBound(),
			listCollisionWithPlayer.at(i)->GetBound());
		if (r.IsCollided)
		{
			//lay phia va cham cua Entity so voi Player
			Entity::SideCollisions sidePlayer = GameCollision::getSideCollision(mPlayer, r);

			//lay phia va cham cua Player so voi Entity
			Entity::SideCollisions sideImpactor = GameCollision::getSideCollision(listCollisionWithPlayer.at(i), r);

#pragma region	-Update GUI theo luật game -
		
			if (listCollisionWithPlayer.at(i)->Tag == Entity::EntityTypes::Item && listCollisionWithPlayer.at(i)->_allowPlayerpick == true)			
			{	
				if( (mPlayer->getState() == PlayerState::StandingBeat && sidePlayer == Entity::Right &&  mPlayer->GetBound().right - listCollisionWithPlayer[i]->GetBound().left > 5 )
					|| (mPlayer->getState() == PlayerState::StandingBeat && sidePlayer == Entity::Left &&  listCollisionWithPlayer[i]->GetBound().right - mPlayer->GetBound().left > 5 )
					|| mPlayer->getState()!= PlayerState::StandingBeat
					)
				{
					goto Next;
				}
				else
				{
					goto Exit;
				}
				Next:
				Sound::getInstance()->play("PickItem", true, 0);
				if (listCollisionWithPlayer.at(i)->TagItem == Entity::ItemType::BlueMana)
				{
					gameUI->SetplayerMana(gameUI->GetplayerMana() + 5);
					mPlayer->setPlayerMana(gameUI->GetplayerMana());
					listCollisionWithPlayer.at(i)->Hidden();
				}
				if (listCollisionWithPlayer.at(i)->TagItem == Entity::ItemType::RedMana)
				{
					gameUI->SetplayerMana(gameUI->GetplayerMana() + 10);
					mPlayer->setPlayerMana(gameUI->GetplayerMana());
					listCollisionWithPlayer.at(i)->Hidden();
				}

				if (listCollisionWithPlayer.at(i)->TagItem == Entity::ItemType::BlueBonus)
				{
					gameUI->SetplayerScore(gameUI->GetplayerScore() + 500);
					listCollisionWithPlayer.at(i)->Hidden();
				}
				if (listCollisionWithPlayer.at(i)->TagItem == Entity::ItemType::RedBonus)
				{
					gameUI->SetplayerScore(gameUI->GetplayerScore() + 1000);
					listCollisionWithPlayer.at(i)->Hidden();
				}
				if (listCollisionWithPlayer.at(i)->TagItem == Entity::ItemType::RedHP)
				{
					gameUI->SetplayerHP(gameUI->GetplayerHP() + 6);
					Sound::getInstance()->play("BonusHP", true, 0);
					listCollisionWithPlayer.at(i)->Hidden();
				}
				if (listCollisionWithPlayer.at(i)->TagItem == Entity::ItemType::ThrowingStar)
				{
					listCollisionWithPlayer.at(i)->SetPosition(-100, 14);
					mPlayer->mWeapon = new ThrowingStarWeapon(mPlayer->GetPosition());
					gameUI->_boxWeapon = new Sprite("Resources/Item_Effect/ThrowingStarBox.png");
				}
				if (listCollisionWithPlayer.at(i)->TagItem == Entity::ItemType::WindmillStar)
				{
					listCollisionWithPlayer.at(i)->Hidden();

					mPlayer->mWeapon = new WindmillStarWeapon(mPlayer->GetPosition());
					gameUI->_boxWeapon = new Sprite("Resources/Item_Effect/WindmillStarBox.png");
				}
				if (listCollisionWithPlayer.at(i)->TagItem == Entity::ItemType::Fire)
				{
					listCollisionWithPlayer.at(i)->Hidden();
					mPlayer->mWeapon = new FireWeapon(mPlayer->GetPosition());
					gameUI->_boxWeapon = new Sprite("Resources/Item_Effect/FireBox.png");
				}
				if (listCollisionWithPlayer.at(i)->TagItem == Entity::ItemType::TimeFreeze)
				{
					for (int i = 0; i < mMap->GetListObject().size(); i++)
					{
						if (mMap->GetListObject()[i]->Tag == Entity::Enemy)
						{
							mMap->GetListObject()[i]->isUpdate = false;
						}
					}
					listCollisionWithPlayer.at(i)->Hidden();

				}
			}
			Exit:
			if (mPlayer->getState() != PlayerState::StandingBeat && listCollisionWithPlayer.at(i)->Tag == Entity::EntityTypes::Item)
			{
				goto ExitPlayerOnCollision;

			}
			if (mPlayer->getState() == PlayerState::StandingBeat && listCollisionWithPlayer.at(i)->_Active == true && listCollisionWithPlayer.at(i)->Tag == Entity::EntityTypes::Enemy || mPlayer->getState() == PlayerState::SittingBeat && listCollisionWithPlayer.at(i)->Tag == Entity::EntityTypes::Enemy)
			{
				if (listCollisionWithPlayer[i]->TagEnemy == Entity::EnemyType::Boss )
				{
					gameUI->SetenemyHP(listCollisionWithPlayer[i]->_HP);
				}
				else
				{
					if (sidePlayer==Entity::Right && ! this->mPlayer->GetReserse()&& mPlayer->getAllowHit() || sidePlayer==Entity::Left && this->mPlayer->GetReserse() && mPlayer->getAllowHit())
						switch (listCollisionWithPlayer[i]->TagEnemy)
						{
						case Entity::Swordman: case Entity::Axe_E:
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

				}
				Sound::getInstance()->play("BeatEnemy", true, 0);
			}
			else
			{

			} 
#pragma endregion
			if ( (mPlayer->getState() != PlayerState::Climbing && listCollisionWithPlayer.at(i)->Tag == Entity::EntityTypes::StairTop) 
				|| ( mPlayer->getState() != PlayerState::Climbing && listCollisionWithPlayer.at(i)->Tag == Entity::EntityTypes::StairBottom) 
				|| (mPlayer->getState() == PlayerState::Climbing && listCollisionWithPlayer[i]->Tag == Entity::EntityTypes::Grass))
			{
				goto ExitPlayerOnCollision;
			}
			if (listCollisionWithPlayer[i]->TagEnemy == Entity::Boss && !listCollisionWithPlayer[i]->isUpdate)
			{
				goto ExitPlayerOnCollision;
			}

			mPlayer->OnCollision(listCollisionWithPlayer.at(i), r, sidePlayer);

			if (listCollisionWithPlayer.at(i)->Tag == Entity::EntityTypes::Enemy&&listCollisionWithPlayer.at(i)->_Active == true && mPlayer->invincible == false && mPlayer->getState() != PlayerState::StandingBeat &&  mPlayer->getState() != PlayerState::SittingBeat
				|| listCollisionWithPlayer.at(i)->Tag == Entity::EntityTypes::Enemy&&listCollisionWithPlayer.at(i)->_Active == true && mPlayer->invincible == false && mPlayer->getState() == PlayerState::StandingBeat && sidePlayer != Entity::Right&& sidePlayer != Entity::Left
				|| listCollisionWithPlayer.at(i)->Tag == Entity::EntityTypes::Enemy&&listCollisionWithPlayer.at(i)->_Active == true && mPlayer->invincible == false  && mPlayer->getState() == PlayerState::SittingBeat && sidePlayer != Entity::Right && sidePlayer != Entity::Left)
			{
				gameUI->SetplayerHP(gameUI->GetplayerHP() - 1);

				Sound::getInstance()->play("Injured", true, 0);
				mPlayer->invincible = true;

			}

		ExitPlayerOnCollision:
#pragma endregion
				//kiem tra neu va cham voi phia duoi cua Player 
			if (sidePlayer == Entity::Bottom || sidePlayer == Entity::BottomLeft
				|| sidePlayer == Entity::BottomRight)
			{
				//kiem cha do dai ma ninja tiep xuc phia duoi day
				int bot = r.RegionCollision.right - r.RegionCollision.left;
				if (bot > widthBottom)
					widthBottom = bot;
			}
			if (listCollisionWithPlayer[i]->Tag == Entity::EntityTypes::Grass)
			{
				widthBottom = Define::PLAYER_BOTTOM_RANGE_FALLING + 5; // cho khỏi bị rơi
			}
		}
	}

	// Chỉnh sửa các thông số theo luật game 
	if (gameUI->GetplayerHP() == 0 || CheckPositionPlayer())
	{
		Sound::getInstance()->play("Death", true, 0);
		Sound::getInstance()->stop("Level" + to_string(level) );
		//Sound::getInstance()->play("Death", true, 0);
		Sleep(2000);

		mPlayer->SetPosition(InitPosPlayer());
		mPlayer->SetState(new PlayerStandingState(mPlayer->mPlayerData));
		mPlayer->mWeapon = nullptr;
		gameUI->_boxWeapon = new Sprite("Resources/Item_Effect/BoxWeapon.png");
		if(level<3)
		mMap = new GameMap(level);
		else
		{
			level = 2;
			mMap = new GameMap(level);
			gameUI->SetenemyHP(16);
		}

		Sound::getInstance()->play("Level"+ to_string(level), true, 0,1);
		mCamera = new Camera(GameGlobal::GetWidth(), GameGlobal::GetHeight());
		mCamera->SetPosition(GameGlobal::GetWidth() / 2,
			GameGlobal::GetHeight() / 2);
		mMap->SetCamera(mCamera);
		mPlayer->SetCamera(mCamera);
		for (int i = 0; i < mMap->GetListObject().size(); i++)
		{
			if (mMap->GetListObject()[i]->Tag == Entity::EntityTypes::Enemy&&mMap->GetListObject()[i]->TagWeapon == Entity::NoneWeapon)
			{
				mMap->GetListObject()[i]->GetPLayer(mPlayer);
				listObject.push_back(mMap->GetListObject().at(i));
			}
		}
		


		if (gameUI->GetLiveCount() > 0)
		{
			gameUI->SetLiveCount(gameUI->GetLiveCount() - 1);

			
			gameUI->SetplayerHP(MAX_HP);
			mPlayer->setPlayerMana(mPlayer->getPlayerMana() / 2);
			

			gameUI->initTimer(150);
		}
		else
		{
			gameUI->SetLiveCount(gameUI->GetLiveCount() - 1);
			Sound::getInstance()->stop("Level" + to_string(level));
		}
	}
	if (level < 3)
	{
		if (mPlayer->GetPosition().x >= mMap->GetWidth()-FrameWidth)
		{
			Sound::getInstance()->stop("Level" + to_string(level));

			level++;
			Sound::getInstance()->play("Level" + to_string(level),true,0,1);
			mMap = new GameMap(level);
			if (level < 3)
			{
				gameUI->SetplayerHP(MAX_HP);

			}

			gameUI->initTimer(150);
			mPlayer->SetPosition(InitPosPlayer());
			mCamera = new Camera(GameGlobal::GetWidth(), GameGlobal::GetHeight());
			mCamera->SetPosition(GameGlobal::GetWidth() / 2,
				GameGlobal::GetHeight() / 2);
			mMap->SetCamera(mCamera);
			mPlayer->SetCamera(mCamera);
			for (int i = 0; i < mMap->GetListObject().size(); i++)
			{
				if (mMap->GetListObject()[i]->Tag == Entity::EntityTypes::Enemy&&mMap->GetListObject()[i]->TagWeapon == Entity::NoneWeapon)
				{
					mMap->GetListObject()[i]->GetPLayer(mPlayer);
					listObject.push_back(mMap->GetListObject().at(i));
				}
			}
		}
	}
	else
	{
		if (gameUI->GetenemyHP() <= 0)
		{
			Sound::getInstance()->play("BonusScoreBoss", true, 0, 1);

			Sound::getInstance()->stop("Level3");
			mPlayer->setPlayerMana(mPlayer->getPlayerMana() - 2);
			if (mPlayer->getPlayerMana() <= 0)
			{
				mPlayer->setPlayerMana(0);
			}
			if (gameUI->getTimer() > 0)
			{
				gameUI->SetplayerScore(gameUI->GetplayerScore() + 15);
				gameUI->SetTimer(-(gameUI->getTimer() - 3));

			}
			else
			{
				//Sleep(3500);
			}
		}
	}
	
	
	//Neu ninja dung ngoai mep thi luc nay cho ninja rot xuong duoi dat    
	if (widthBottom < Define::PLAYER_BOTTOM_RANGE_FALLING)
	{
		mPlayer->OnNoCollisionWithBottom();
	}


}

int SceneGame::CheckPositionPlayer()
{
	if (mPlayer->GetPosition().y > mMap->GetHeight())
	{
		return 1;
	}

	return 0;
}
