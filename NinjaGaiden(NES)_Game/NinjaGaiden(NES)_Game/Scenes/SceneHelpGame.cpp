#include "SceneHelpGame.h"
#include "SceneStartGame.h"
SceneHelpGame::SceneHelpGame()
{
	LoadContent();
}

void SceneHelpGame::Update(float dt)
{
	if (IsKeyDown(DIK_SPACE))
	{
		SceneManager::GetInstance()->ReplaceScene(new SceneGame());
		return;
	}
	if (IsKeyDown(DIK_ESCAPE))
	{
		GameGlobal::isGameRunning = false;
	}
	if (IsKeyDown(DIK_BACKSPACE))
	{
		SceneManager::GetInstance()->ReplaceScene(new SceneStartGame());
		return;
	}
}

void SceneHelpGame::LoadContent()
{
	SpriteHelpGame = new Sprite("Resources/HelpGame.png");
	
}

void SceneHelpGame::Draw()
{
	SpriteHelpGame->Draw(D3DXVECTOR3(GameGlobal::GetWidth() / 2, GameGlobal::GetHeight() / 2, 0));
}

void SceneHelpGame::OnKeyDown(int keyCode)
{
}

void SceneHelpGame::OnKeyUp(int keyCode)
{
}

int SceneHelpGame::IsKeyDown(int KeyCode)
{
	return (GameGlobal::GetCurrentKeyState()[KeyCode] & 0x80) > 0;
}
