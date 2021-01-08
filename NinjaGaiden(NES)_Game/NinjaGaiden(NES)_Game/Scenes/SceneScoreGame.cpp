#include "SceneEndGame.h"
#include "SceneScoreGame.h"
SceneScoreGame::SceneScoreGame(int Score)
{
	LoadContent();
	arial = new Font(GameGlobal::GetCurrentDevice(), 30, GameGlobal::GetWidth(), GameGlobal::GetHeight());
	FindHighScore();
	CurrentSocre = Score;
	timeChangeScene = 0;
}

void SceneScoreGame::Update(float dt)
{
	timeChangeScene += dt;
	if (timeChangeScene >= 5)
	{
		SceneManager::GetInstance()->ReplaceScene(new SceneEndGame());
	}
}

void SceneScoreGame::LoadContent()
{

	SpriteNinja = new Sprite("Resources/ninja.png");
	SpriteHighScore = new Sprite("Resources/HighScore.jpg");
}

void SceneScoreGame::Draw()
{
	SpriteNinja->Draw(D3DXVECTOR3(GameGlobal::GetWidth() / 2-30, GameGlobal::GetHeight() / 2+20, 0));
	SpriteHighScore->Draw(D3DXVECTOR3(GameGlobal::GetWidth() / 2-30, GameGlobal::GetHeight() / 4+20, 0));
	arial->onLost();
	arial->render(CurrentSocre, GameGlobal::GetWidth()/2, GameGlobal::GetHeight()/2);
	//arial->render("HighScore: ", GameGlobal::GetWidth()/2 - 100, GameGlobal::GetHeight() / 5);

	arial->render(HighScore, GameGlobal::GetWidth() / 2+35, GameGlobal::GetHeight() / 5+20);
}

void SceneScoreGame::OnKeyDown(int keyCode)
{
}

void SceneScoreGame::OnKeyUp(int keyCode)
{
}

int SceneScoreGame::IsKeyDown(int KeyCode)
{
	return 0;
}

int SceneScoreGame::FindHighScore()
{
	fstream f_score;
	f_score.open("Resources/Score.txt");
	int temp;
	while (!f_score.fail())
	{
		f_score >> temp;
		if (HighScore < temp)
		{
			HighScore = temp;

		}
	}
	f_score.close();
	return HighScore;
}
