#include "GameMap.h"
#include <string>
GameMap::GameMap(int level)
{
	LoadMap(level);
}
void GameMap::LoadMap( int level)
{
	

	fstream fs("Resources/Map/Map" + to_string(level) + "/map.txt");
	//fs >> mtotalTile;
	fs >> mcolumnCount >> mrowCount;
	matrixTile = new int *[mrowCount];
	for (int rowIndex = 0; rowIndex < mrowCount; rowIndex++)
	{
		matrixTile[rowIndex] = new int[mcolumnCount];
		for (int columIndex = 0; columIndex < mcolumnCount; columIndex++)
		{
			fs >> matrixTile[rowIndex][columIndex];
		}
	}
	fs.close();
	string  tileSet = "Resources/Map/Map"+ to_string(level) + "/tileSet.png";
	mTileMap = new Sprite(tileSet.c_str());

	RECT r;
	r.left = 0;
	r.top = 0;
	r.right = this->GetWidth();
	r.bottom = this->GetHeight();

	mQuadTree = new QuadTree(1, r);
#pragma region -ENEMY-
	fstream f_ei("Resources/Map/Map" + to_string(level) + "/Enemy.txt");
	float idType, posX, posY, minX, maxX, originalTurn;
	while (!f_ei.eof())
	{
		f_ei >> idType >> posX >> posY >> minX >> maxX >> originalTurn;
		D3DXVECTOR3 position;
			//fstream fs("Brick");
		position = D3DXVECTOR3(posX, posY, 0);
		
		GameObject *object = nullptr;
		switch (int(idType))
		{
		case 1:
			object = new Swordman(position);			
			object->Tag = Entity::EntityTypes::Enemy;
			break;		
		case 3:
			object = new Panther(position);
			object->Tag = Entity::EntityTypes::Enemy;		
			break;
		case 4:
			object = new Eagle(position);
			object->Tag = Entity::EntityTypes::Enemy;		
			break;
		case 5:
			object = new Goblin(position);
			object->Tag = Entity::EntityTypes::Enemy;	
			for (int i = 0; i < object->GetBullet().size(); i++)
			{
				object->GetBullet()[i]->Tag = Entity::EntityTypes::Enemy;
				mListObjects.push_back(object->GetBullet()[i]);
				mQuadTree->insertEntity(object->GetBullet()[i]);
			}
			break;		
		case 6:
			object = new Brute(position);
			object->Tag = Entity::EntityTypes::Enemy;	
			for (int i = 0; i < object->GetBullet().size(); i++)
			{
				object->GetBullet()[i]->Tag = Entity::EntityTypes::Enemy;
				mListObjects.push_back(object->GetBullet()[i]);
				mQuadTree->insertEntity(object->GetBullet()[i]);
			}
			break;
		case 7:
			object = new Canoneer(position);

			object->Tag = Entity::EntityTypes::Enemy;


			for (int i = 0; i < object->GetBullet().size(); i++)
			{
				object->GetBullet()[i]->Tag = Entity::EntityTypes::Enemy;
				mListObjects.push_back(object->GetBullet()[i]);
				mQuadTree->insertEntity(object->GetBullet()[i]);
			}

			break;
		case 8:
			object = new Runner(position);

			object->Tag = Entity::EntityTypes::Enemy;
			break;
		case 9:
			object = new Boss(position);
		    object->Tag = Entity::EntityTypes::Enemy;
			object->TagEnemy = Entity::EnemyType::Boss;

		
			for (int i = 0; i < object->GetBullet().size(); i++)
			{
				object->GetBullet()[i]->Tag = Entity::EntityTypes::Enemy;

				mListObjects.push_back(object->GetBullet()[i]);
				mQuadTree->insertEntity(object->GetBullet()[i]);
			}
			
			break;
	


		}
		if (object)
		{
			object->SetRange(minX, maxX);
			object->SetOriginalTurn(originalTurn);
			mListObjects.push_back(object);
			mQuadTree->insertEntity(object);
		}
		
	
	}
	f_ei.close();
	
#pragma endregion

#pragma region -Item-
	fstream f_item("Resources/Map/Map" + to_string(level) + "/Item.txt");
	float  posStop;
	while (!f_item.eof())
	{
		f_item >> idType >> posX >> posY >> posStop;
		D3DXVECTOR3 position;
		position = D3DXVECTOR3(posX, posY, 0);
		GameObject *object = nullptr;
		switch (int(idType))
		{
		case 0:
			object = new Butterfly(position);
			break;
		case 1:
			object = new BlueMana(position,posStop);
			break;
		case 2:
			object = new RedMana(position, posStop);
			break;
		case 3:
			object = new RedBonus(position, posStop);
			break;
		case 4:
			object = new BlueBonus(position, posStop);
			break;
		case 5:
			object = new RedHP(position, posStop);
			break;
		case 6:
			object = new Fire(position, posStop);
			break;
		case 7:
			object = new ThrowingStar(position, posStop);
			break;
		case 8:
			object = new TimeFreeze(position, posStop);
			break;
		case 9:
			object = new WindmillStar(position, posStop);
			break;
		case 10:
			object = new BirdBrown(position);
			break;
		
		
		}

		if (object)
		{
			object->Tag = Entity::EntityTypes::Item;

			mListObjects.push_back(object);
			mQuadTree->insertEntity(object);

		}
	}
		f_item.close();
		

#pragma endregion
#pragma region -OBJECTGROUP, STATIC OBJECT-

	
	fstream f("Resources/Map/Map" + to_string(level) + "/StaticObjectMap.txt");
	float widthObject, heightObject;
	//f >> widthObject;
	while (!f.eof())
	{
		f >>idType>> widthObject >> heightObject >> posX >> posY;
		Entity *entity = nullptr;
		entity = new Entity();
		entity->SetPosition(posX,posY);
		entity->SetWidth(widthObject);
		entity->SetHeight(heightObject);
		
		switch (int (idType))
		{

		case 0:
			
			
			entity->Tag = Entity::EntityTypes::Static;

			break;
		case 1:
		
			entity->Tag = Entity::EntityTypes::StairTop;

			break;
		case 2:
			
			entity->Tag = Entity::EntityTypes::StairBottom;

			break;
		case 3:
			
			entity->Tag = Entity::EntityTypes::Stair;

			break;
		case 4: entity->Tag = Entity::EntityTypes::Grass;
			break;
		case 5: entity->Tag = Entity::EntityTypes::Wall;
			break;
		}
		
		mQuadTree->insertEntity(entity);

	}
	f.close();

#pragma endregion
	
}


bool GameMap::isContain(RECT rect1, RECT rect2)
{
	if (rect1.left > rect2.right || rect1.right < rect2.left || rect1.top > rect2.bottom || rect1.bottom < rect2.top)
	{
		return false;
	}

	return true;
}

void GameMap::Update(float dt)
{

	for (size_t i = 0; i < mListObjects.size(); i++)
	{
	
			if (!isContain(mListObjects[i]->GetBound(), mCamera->GetBound()) && mListObjects[i]->Tag == Entity::EntityTypes::Enemy)
			{
				//mListObjects[i]->SetActive(true);
				mListObjects[i]->SetActive(false);
			}
			mListObjects[i]->Update(dt);
		

			
		
	}
	
}
void GameMap::Draw()
{
	RECT rect;
	D3DXVECTOR2 trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2 - mCamera->GetPosition().x,
		GameGlobal::GetHeight() / 2 - mCamera->GetPosition().y);
 #pragma region DRAW TILESET
	for (int rowIndex = 0; rowIndex <mrowCount; rowIndex++)
	{
		
		for (int columIndex = 0; columIndex < mcolumnCount; columIndex++)
		{
			//mMap->SetSourceRect()
			rect.left =( matrixTile[rowIndex][columIndex]) * FrameWidth;
			rect.right = rect.left +FrameWidth;
			rect.top = 0;
			rect.bottom = rect.top + FrameHeight;
			D3DXVECTOR3 position((columIndex)*FrameWidth+FrameWidth/2, (rowIndex)*FrameHeight+FrameHeight/2, 0);

		//	mMap->SetSourceRect(rect);
			if (mCamera != NULL)
			{
				RECT objRECT;
				objRECT.left = position.x - FrameWidth / 2;
				objRECT.top = position.y - FrameHeight / 2;
				objRECT.right = objRECT.left + FrameWidth;
				objRECT.bottom = objRECT.top + FrameHeight;

				//neu nam ngoai camera thi khong Draw
				if (isContain(objRECT, mCamera->GetBound()) == false)
					continue;
			}
			mTileMap->SetHeight(FrameHeight);
			mTileMap->SetWidth(FrameWidth);

			mTileMap->Draw(position,rect,D3DXVECTOR2(),trans);

		}
	}
 #pragma endregion

#pragma region DRAW BRICK
	
	for (size_t i = 0; i < mListObjects.size(); i++)
	{
		if (isContain(mListObjects[i]->GetBound(), mCamera->GetBound()))
		{
			mListObjects[i]->Draw(mListObjects[i]->GetPosition(), RECT(), D3DXVECTOR2(), trans);

		}
		//mListBricks[i]->Draw(pos);
	}

#pragma endregion
}



void GameMap::SetCamera(Camera * camera)
{
	this->mCamera = camera;
}

RECT GameMap::GetWorldMapBound()
{
	
		RECT bound;
		bound.left = bound.top = 0;
		bound.right = GetWidth() * FrameWidth;
		bound.bottom = GetHeight() * FrameHeight;

		return bound;
	
}

bool GameMap::IsBoundLeft()
{
	return (mCamera->GetBound().left == 0);
}

bool GameMap::IsBoundRight()
{
	return (mCamera->GetBound().right == this->GetWidth());
}

bool GameMap::IsBoundTop()
{
	return (mCamera->GetBound().top == 0);
}

bool GameMap::IsBoundBottom()
{
	return (mCamera->GetBound().bottom == this->GetHeight());
}

GameMap::~GameMap()
{
	for (int i = 0; i < mrowCount; i++)
	{
		delete[]	matrixTile[i];
	}
	delete[]matrixTile;
	delete mTileMap;
	delete mCamera;
	for (size_t i = 0; i < mListObjects.size(); i++)
	{
		if (mListObjects[i])
			delete mListObjects[i];
	}
	mListObjects.clear();
	delete mQuadTree;
}



int GameMap::GetHeight()
{
	return (mrowCount)*FrameHeight;
}

int GameMap::GetWidth()
{
	return mcolumnCount * FrameWidth;
}

std::vector<GameObject*> GameMap::GetListObject()
{
	return mListObjects;
}
QuadTree * GameMap::GetQuadTree()
{
	return mQuadTree;
}