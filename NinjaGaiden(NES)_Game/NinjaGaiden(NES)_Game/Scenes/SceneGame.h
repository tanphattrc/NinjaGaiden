#pragma once

#include <math.h>
#include <vector>
#include <d3dx9.h>
#include <d3d9.h>
#include "../GameComponents/Scene.h"
#include "../GameComponents/Sprite.h"
#include "../GameComponents/GameMap.h"
#include "../GameDefine/GameDefine.h"
#include "../GameObjects/DynamicGameObject/Player/Player.h"
#include "../GameUI/GameUI.h"
#include  "../GameComponents/Sound.h"
#include "SceneGameOver.h"

class SceneGame : public Scene
{
public:
    SceneGame(int _level=1);
	~SceneGame();
    void Update(float dt);
    void LoadContent();
    void Draw();

    void OnKeyDown(int keyCode);
    void OnKeyUp(int keyCode);
   
	int IsKeyDown(int KeyCode);
	void SaveGame();
	void LoadSaveGame();
protected:
	D3DXVECTOR2 InitPosPlayer();
	void checkRuleGame();
	int CheckPositionPlayer(); // Kiểm tra xem player có rơi ra khỏi map hay không
	void CheckCameraAndWorldMap();
	//void CheckRuleGame();

	GameMap *mMap;
	Camera *mCamera;
	Player *mPlayer;
	GameUI *gameUI;
	int level;
	vector<Entity*> listObject;
    float mTimeCounter;
	int score;
	fstream f_score;
};

