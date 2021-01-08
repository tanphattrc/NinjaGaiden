#ifndef __GAME__
#define __GAME__
#include <d3dx9.h>
#include <d3d9.h>
#include <Windows.h>
#include <dinput.h>
#include "../GameDefine/GameDefine.h"
#include "GameTime.h"
//#include "../Utils.h"



class Game
{
public:
	Game(int fps = 60);
	Game(HINSTANCE hInstance);
	int initWindow(int cmdShow);



	~Game();

protected:

	LPDIRECT3DSURFACE9       mBackground,
		mBackBuffer;
	LPDIRECTINPUT8				mDirectInput;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8		mKeyBoard;			// The keyboard device 

	LPDIRECT3D9             mDirect3D9;
	LPD3DXSPRITE            mSpriteHandler;
	PDIRECT3D9              mD3d;
	LPDIRECT3DDEVICE9       mDevice;
	HINSTANCE               mHInstance;
	int                     mCmdShow;

	//
	int                     mWidth,
		mHeight;
	static int              mIsDone;
	float                   mFPS;
	//Init
	int InitDevice();

	//khoi tao vong lap cho game
	static	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void InitLoop();

	//ham dung de ve sau khi update
	void Render();
	//direct input
	int InitKeyboard();
	

	void ProcessKeyBoard();
	
	virtual void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta);


	//virtual void OnKeyUp(int KeyCode);
	//virtual void OnKeyDown(int KeyCode);

	int IsKeyDown(int KeyCode);
	//ham update cua game
	void Update(float dt);

	BYTE  mKeyStates[256]; // DirectInput keyboard state buffer 
	bool pressKey[256];
	

	DIDEVICEOBJECTDATA mKeyEvents[KEYBOARD_BUFFERD_SIZE]; // Buffered keyboard data
};

#endif