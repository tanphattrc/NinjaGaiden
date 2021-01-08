#pragma once
#ifndef __GAME_GLOBAL__
#define __GAME_GLOBAL__
#include <d3dx9.h>
#include <d3d9.h>
#include <Windows.h>
#include <dinput.h>






class GameGlobal
{
public:
	GameGlobal();
	~GameGlobal();

	static HINSTANCE GetCurrentHINSTACE();
	static HWND getCurrentHWND();

	static void SetCurrentHINSTACE(HINSTANCE hInstance);
	static void SetCurrentHWND(HWND hWnd);

	static void SetCurrentSpriteHandler(LPD3DXSPRITE spriteHandler);
	static LPD3DXSPRITE GetCurrentSpriteHandler();

	static void SetCurrentDevice(LPDIRECT3DDEVICE9 device);
	static LPDIRECT3DDEVICE9 GetCurrentDevice();

	static void SetWidth(int width);
	static int GetWidth();

	static void SetHeight(int height);
	static int GetHeight();

	static LPDIRECT3DSURFACE9 backSurface;
	// direct input
	//static int Init_DirectInput(HWND);
	// static int Init_Keyboard(HWND);
	//static void Poll_Keyboard();
	// static int Key_Down(int);
	// static void Kill_Keyboard();
 //   static void Poll_Mouse();
	//static int Init_Mouse(HWND);
	//static int Mouse_Button(int);
	//static int Mouse_X();
	//static int Mouse_Y();
	//static void Kill_Mouse();

	static bool isGameRunning; //trang thai xem game co dang chay khong

	// Direct Input
	static  void SetCurrentKeyBoard(LPDIRECTINPUTDEVICE8 keyboard);
	
	static void SetCurrentDirectInput(LPDIRECTINPUT8 dinput);

	static LPDIRECTINPUTDEVICE8  GetCurrentKeyBoard();
	
	static LPDIRECTINPUT8  GetCurrentDirectInput();
	static bool Pause;

	static void SetCurrentKeyState(BYTE keyStates[256]);
	static void SetCurrentKeyPress(bool Keyspress[256]);
	static bool* getCurrentKeypress();
	static BYTE* GetCurrentKeyState();
	static bool ContinueGame;

private:
	static HINSTANCE mHInstance; //hInstance của windows hiện tại
	static HWND mHwnd; // hwnd hiện tại
	static LPD3DXSPRITE mSpriteHandler; //spriteHanlder hiện tại
	static int mWidth, mHeight; //size của cửa sổ
	static LPDIRECT3DDEVICE9 mDevice; //device directX hiện tại
	static LPDIRECTINPUT8				mDirectInput;		// The DirectInput object         
	static LPDIRECTINPUTDEVICE8			mKeyBoard;			// The keyboard device 
	

	static BYTE  mKeyStates[256]; // DirectInput keyboard state buffer 
	static  bool mKeyPress[256];
	
};

#endif

