#include "SceneStartGame.h"

SceneStartGame::SceneStartGame()
{
	
	LoadContent();
}

void SceneStartGame::Update(float dt)
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
	if (IsKeyDown(DIK_F1))
	{
		SceneManager::GetInstance()->ReplaceScene(new SceneHelpGame());
		return;
	}
	if (IsKeyDown(DIK_DOWNARROW))
	{
		GameGlobal::ContinueGame = true;
		Option = true;
	}
	if (IsKeyDown(DIK_UPARROW))
	{
		GameGlobal::ContinueGame = false;
		Option = false;
	}
}

void SceneStartGame::LoadContent()
{
	SpriteStartGame= new Sprite("Resources/StartGame.png");
	Option = false;
	Start = new Sprite("Resources/Start.png");
	Continue = new Sprite("Resources/Continue.png");
}

void SceneStartGame::Draw()
{
	SpriteStartGame->Draw(D3DXVECTOR3(GameGlobal::GetWidth() / 2, GameGlobal::GetHeight() / 2, 0));
	if (Option)
	{
		Continue->Draw( D3DXVECTOR3(GameGlobal::GetWidth() / 2, GameGlobal::GetHeight() / 2+20, 0));
	}
	else
	{
		Start->Draw(D3DXVECTOR3(GameGlobal::GetWidth() / 2, GameGlobal::GetHeight() / 2, 0));
	}
}

void SceneStartGame::OnKeyDown(int keyCode)
{
}

void SceneStartGame::OnKeyUp(int keyCode)
{
}

int SceneStartGame::IsKeyDown(int KeyCode)
{
	return (GameGlobal::GetCurrentKeyState()[KeyCode] & 0x80) > 0;
}
