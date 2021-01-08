#include "SceneGameOver.h"

SceneGameOver::SceneGameOver(int _level)
{
	level = _level;
	LoadContent();
	GameGlobal::ContinueGame = false;
}

void SceneGameOver::Update(float dt)
{
	if (IsKeyDown(DIK_SPACE))
	{
		if (level == 3)
		{
			level = 2;
		}

		SceneManager::GetInstance()->ReplaceScene(new SceneGame(level));
		return;
	}
	if (IsKeyDown(DIK_ESCAPE))
	{
		GameGlobal::isGameRunning = false;
	}
}

void SceneGameOver::LoadContent()
{
	SpriteGameOver = new Sprite("Resources/GameOver.png");
}

void SceneGameOver::Draw()
{
	SpriteGameOver->Draw(D3DXVECTOR3(GameGlobal::GetWidth() / 2, GameGlobal::GetHeight() / 2, 0));
}

void SceneGameOver::OnKeyDown(int keyCode)
{
}

void SceneGameOver::OnKeyUp(int keyCode)
{
}

int SceneGameOver::IsKeyDown(int KeyCode)
{
	return (GameGlobal::GetCurrentKeyState()[KeyCode] & 0x80) > 0;
}
