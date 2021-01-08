#pragma once

#include <math.h>
#include <vector>
#include <d3dx9.h>
#include <d3d9.h>

#include "../GameComponents/Scene.h"
#include "../GameComponents/Sprite.h"
#include  "../GameComponents/Sound.h"
#include "../GameComponents/GameGlobal.h"
#include "../GameControllers/SceneManager.h"
#include "SceneGame.h"
#include "../GameUI/Font.h"
#include "SceneEndGame.h"
class SceneScoreGame : public Scene
{
public:
	SceneScoreGame(int Score);

	void Update(float dt);
	void LoadContent();
	void Draw();

	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);

	int IsKeyDown(int KeyCode);
	int FindHighScore();
	
protected:
	Sprite *SpriteNinja;
	Sprite *SpriteHighScore;
	Font *arial;
	int HighScore;
	int CurrentSocre;
	float timeChangeScene;


};

