#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>
#include <iostream>
#include <sstream>
#include <dinput.h>
#include <windowsx.h>
#include "GameComponents\GameGlobal.h"
#include "GameComponents\GameTime.h"
#include "GameComponents\Game.h"
#include "GameControllers\SceneManager.h"

using namespace std;

//#define WIN_NAME "Game DirectX"
//#define WIN_TITLE "Game DirectX"
//#define FPS 60
//#define KEYBOARD_BUFFERD_SIZE 1024



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int cmdShow)
{

	Game *game = new Game(hInstance);
	game->initWindow(cmdShow);

	return 0;
}

