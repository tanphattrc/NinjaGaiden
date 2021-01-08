#include "Sprite.h"
#include "GameGlobal.h"

#include <fstream>
#include <iostream>
#include "Camera.h"
#include "../GameDefine/GameDefine.h"
#include "..//GameComponents/QuadTree.h"
#include "../GameObjects/Entity.h"
#include "../GameObjects/StaticGameObject/Butterfly.h"
#include "../GameObjects/StaticGameObject/BirdBrown.h"
#include "../GameObjects/DynamicGameObject/Enemy/Swordman.h"
#include "../GameObjects/DynamicGameObject/Enemy/Panther.h"
#include "../GameObjects/DynamicGameObject/Enemy/Eagle.h"
#include "../GameObjects/DynamicGameObject/Enemy/Goblin.h"
#include "../GameObjects/DynamicGameObject/Enemy/Brute.h"
#include "../GameObjects/Item/BlueMana.h"
#include  "../GameObjects/Item/BlueBonus.h"
#include  "../GameObjects/Item/Fire.h"
#include  "../GameObjects/Item/RedBonus.h"
#include  "../GameObjects/Item/RedHP.h"
#include  "../GameObjects/Item/RedMana.h"
#include  "../GameObjects/Item/ThrowingStar.h"
#include  "../GameObjects/Item/TimeFreeze.h"
#include  "../GameObjects/Item/WindmillStar.h"
#include "../GameObjects/DynamicGameObject/Boss/Boss.h"
#include "../GameObjects/DynamicGameObject/Enemy/Canoneer.h"
#include "../GameObjects/DynamicGameObject/Enemy/Runner.h"

using namespace std;
class GameMap
{
public: 
	GameMap(int level);
	int GetHeight();
	int GetWidth();
	void Draw();
	/*bool drawEffect;
	int TimeDrawEffect;*/
	void Update(float dt);
	void SetCamera(Camera *camera);
	RECT GetWorldMapBound();
	bool IsBoundLeft(); //kiem tra luc nay Camera o vi bien ben trai so voi WorldMap
	bool IsBoundRight(); // kiem tra xem co o vi tri bien ben phai worldmap khong
	bool IsBoundTop(); // kiem tra xem co o vi tri bien ben trai worldmap khong
	bool IsBoundBottom(); // kiem tra xem co o vi tri bien ben phai worldmap khong
	~GameMap();

	//std::vector<Entity*> GetListObject();

	std::vector<GameObject*> GetListObject();

	QuadTree* GetQuadTree();
private:
	void LoadMap(int level);
	int mrowCount, mcolumnCount, mtotalTile;
	bool isContain(RECT rect1, RECT rect2);

	int **matrixTile;
	Sprite * mTileMap;
	Camera *mCamera;
	QuadTree *mQuadTree;
	std::vector<GameObject*> mListObjects;

	//std::vector<Entity*> mListObjects;
	
//	LPD3DXSPRITE                    mSpriteHandler;
	//Sprite                          *mSpriteBricks;


};