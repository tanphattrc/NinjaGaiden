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

class SceneEndGame : public Scene
{
public:
	SceneEndGame();

	void Update(float dt);
	void LoadContent();
	void Draw();

	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);

	int IsKeyDown(int KeyCode);

protected:
	Sprite *SpriteEndGame;

	
};

