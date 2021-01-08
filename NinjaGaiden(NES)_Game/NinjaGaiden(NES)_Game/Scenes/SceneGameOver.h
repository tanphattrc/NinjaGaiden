#pragma once

#include <math.h>
#include <vector>
#include <d3dx9.h>
#include <d3d9.h>

#include "../GameComponents/Scene.h"
#include "../GameComponents/Sprite.h"
#include  "../GameComponents/Sound.h"
#include "../GameControllers/SceneManager.h"
#include "SceneGame.h"
class SceneGameOver : public Scene
{
public:
	SceneGameOver(int _level);

	void Update(float dt);
	void LoadContent();
	void Draw();

	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);

	int IsKeyDown(int KeyCode);

protected:
	Sprite *SpriteGameOver;
	int level;


};

