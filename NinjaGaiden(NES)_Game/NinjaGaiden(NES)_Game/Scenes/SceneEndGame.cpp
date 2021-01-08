#include "SceneEndGame.h"

SceneEndGame::SceneEndGame()
{
	LoadContent();
}

void SceneEndGame::Update(float dt)
{
}

void SceneEndGame::LoadContent()
{

	SpriteEndGame = new Sprite("Resources/EndGame.png");
}

void SceneEndGame::Draw()
{
	SpriteEndGame->Draw(D3DXVECTOR3(GameGlobal::GetWidth() / 2, GameGlobal::GetHeight() / 2, 0));
}

void SceneEndGame::OnKeyDown(int keyCode)
{
}

void SceneEndGame::OnKeyUp(int keyCode)
{
}

int SceneEndGame::IsKeyDown(int KeyCode)
{
	return 0;
}
