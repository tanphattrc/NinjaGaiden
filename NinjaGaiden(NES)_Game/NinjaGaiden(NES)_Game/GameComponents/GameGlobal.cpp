#include "GameGlobal.h"


HINSTANCE GameGlobal::mHInstance = NULL;
HWND GameGlobal::mHwnd = NULL;
LPD3DXSPRITE GameGlobal::mSpriteHandler = NULL;
int GameGlobal::mWidth = 260;
int GameGlobal::mHeight = 232;
LPDIRECT3DDEVICE9 GameGlobal::mDevice = nullptr;
bool GameGlobal::isGameRunning = true;

LPDIRECTINPUT8 GameGlobal::mDirectInput = nullptr;
LPDIRECTINPUTDEVICE8 GameGlobal::mKeyBoard = NULL;

BYTE GameGlobal::mKeyStates[256];
bool GameGlobal::mKeyPress[256];
bool GameGlobal::Pause = true;
bool GameGlobal::ContinueGame = false;
GameGlobal::GameGlobal()
{

}


GameGlobal::~GameGlobal()
{

}

void GameGlobal::SetCurrentDevice(LPDIRECT3DDEVICE9 device)
{
	mDevice = device;
}

LPDIRECT3DDEVICE9 GameGlobal::GetCurrentDevice()
{
	return mDevice;
}


HINSTANCE GameGlobal::GetCurrentHINSTACE()
{
	return mHInstance;
}

HWND GameGlobal::getCurrentHWND()
{
	return mHwnd;
}

void GameGlobal::SetCurrentHINSTACE(HINSTANCE hInstance)
{
	mHInstance = hInstance;
}

void GameGlobal::SetCurrentHWND(HWND hWnd)
{
	mHwnd = hWnd;
}

void GameGlobal::SetCurrentSpriteHandler(LPD3DXSPRITE spriteHandler)
{
	mSpriteHandler = spriteHandler;
}

LPD3DXSPRITE GameGlobal::GetCurrentSpriteHandler()
{
	return mSpriteHandler;
}

void GameGlobal::SetWidth(int width)
{
	mWidth = width;
}

int GameGlobal::GetWidth()
{
	return mWidth;
}

void GameGlobal::SetHeight(int height)
{
	mHeight = height;
}

int GameGlobal::GetHeight()
{
	return mHeight;
}

void GameGlobal::SetCurrentKeyBoard(LPDIRECTINPUTDEVICE8 keyboard)
{
	mKeyBoard = keyboard;
}



void GameGlobal::SetCurrentDirectInput(LPDIRECTINPUT8 dinput)
{
	mDirectInput = dinput;
}

LPDIRECTINPUTDEVICE8 GameGlobal::GetCurrentKeyBoard()
{
	return mKeyBoard;
}



LPDIRECTINPUT8 GameGlobal::GetCurrentDirectInput()
{
	return mDirectInput;
}



void GameGlobal::SetCurrentKeyState(BYTE keyStates[256])
{
	for (int i = 0; i < 256; i++)
	{
		mKeyStates[i] = keyStates[i];
	}
}

void GameGlobal::SetCurrentKeyPress(bool Keyspress[256])
{
	for (int i = 0; i < 256; i++)
	{
		mKeyPress[i] = Keyspress[i];
	}
}

bool * GameGlobal::getCurrentKeypress()
{
	return mKeyPress;
}

//bool * GameGlobal::getCurrentKeypress()
//{
//	return mKeyPress;
//}

BYTE* GameGlobal::GetCurrentKeyState()
{
	return mKeyStates;
}




