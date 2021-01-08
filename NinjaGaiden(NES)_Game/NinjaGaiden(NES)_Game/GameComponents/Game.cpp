#include "Game.h"
#include "GameGlobal.h"
#include "../GameControllers/SceneManager.h"
#include "../Scenes/SceneGame.h"
#include"../Scenes/SceneStartGame.h"

Game::Game(int fps)
{
	mFPS = fps;
	/*mBackground = CreateSurfaceFromFile(GameGlobal::GetCurrentDevice(), "Resources/background.jpg");
	GameGlobal::GetCurrentDevice()->StretchRect(mBackground, NULL, mBackBuffer, NULL, D3DTEXF_NONE);*/
	SceneManager::GetInstance()->ReplaceScene(new SceneStartGame());



	InitLoop();
}

Game::Game(HINSTANCE hInstance)
{
	mHInstance = hInstance;


}

Game::~Game()
{

}

int Game::IsKeyDown(int KeyCode)
{
	return (mKeyStates[KeyCode] & 0x80) > 0;
}

void Game::Update(float dt)
{
	ProcessKeyBoard();

	ProcessInput(GameGlobal::GetCurrentDevice(), dt);
	SceneManager::GetInstance()->GetCurrentScene()->Update(dt);

	Render();
}

int Game::InitKeyboard()
{
	HRESULT
		hr = DirectInput8Create
		(
			GetModuleHandle(NULL),
			DIRECTINPUT_VERSION,
			IID_IDirectInput8, (VOID**)&mDirectInput, NULL
		);

	// TO-DO: put in exception handling
	if (FAILED(hr) == true)
		return 0;

	hr = mDirectInput->CreateDevice(GUID_SysKeyboard, &mKeyBoard, NULL);
	
	// TO-DO: put in exception handling
	if (FAILED(hr) == true)
		return 0;

	hr = mKeyBoard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr) == true)
		return 0;

	hr = mKeyBoard->SetCooperativeLevel(GameGlobal::getCurrentHWND(), DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(hr) == true)
		return 0;

	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFERD_SIZE;

	hr = mKeyBoard->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	if (FAILED(hr) == true)
		return 0;
	GameGlobal::SetCurrentDirectInput(mDirectInput);
	GameGlobal::SetCurrentKeyBoard(mKeyBoard);
	
	hr = mKeyBoard->Acquire();
	if (FAILED(hr) == true)
	{
		/*	switch (hr)
			{
			case DIERR_INVALIDPARAM: MessageBox(GameGlobal::getCurrentHWND(), "Acquire FAILED : Invalid parameter ", "InitializeKeyboard()", MB_OK); break;
			case DIERR_NOTINITIALIZED: MessageBox(GameGlobal::getCurrentHWND(), "Acquire FAILED : The object has not been initialized", "InitializeKeyboard()", MB_OK); break;
			case DIERR_OTHERAPPHASPRIO: MessageBox(GameGlobal::getCurrentHWND(), "Acquire FAILED : Access Denied", "InitializeKeyboard()", MB_OK); break;

			default: MessageBox(GameGlobal::getCurrentHWND(), "Acquire FAILED : Unknow Error", "InitializeKeyboard()", MB_OK);
			}*/
		return 0;
	}


	return 1;
}




void Game::ProcessKeyBoard()
{
	HRESULT hr = GameGlobal::GetCurrentKeyBoard()->GetDeviceState(sizeof(mKeyStates), (LPVOID)&mKeyStates);
	if (hr != S_OK)
	{
		hr = mKeyBoard->Acquire();
		mKeyBoard->GetDeviceState(sizeof(mKeyStates), (LPVOID)&mKeyStates);
	}
	// Collect all key states first
	GameGlobal::GetCurrentKeyBoard()->GetDeviceState(sizeof(mKeyStates), mKeyStates);

	if (IsKeyDown(DIK_ESCAPE))
	{
		PostMessage(GameGlobal::getCurrentHWND(), WM_QUIT, 0, 0);
	}

	// Collect all buffered events
	DWORD dwElements = KEYBOARD_BUFFERD_SIZE;
	hr = GameGlobal::GetCurrentKeyBoard()->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), mKeyEvents, &dwElements, 0);
	//	GameGlobal::SetCurrentKeyBoard(G_KeyBoard);
		// Scan through all data, check if the key is pressed or released
	for (int i = 0; i < 256; i++)
	{
		pressKey[i] = false;
	}
	for (DWORD i = 0; i < dwElements; i++)
	{
		int KeyCode = mKeyEvents[i].dwOfs;
		int KeyState = mKeyEvents[i].dwData;
		if ((KeyState & 0x80) > 0)
		{
			pressKey[KeyCode] = true;
		}
	}
}



void Game::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta)
{
	HRESULT hr = GameGlobal::GetCurrentKeyBoard()->GetDeviceState(sizeof(mKeyStates), (LPVOID)&mKeyStates);
	if (hr != S_OK)
	{
		hr = GameGlobal::GetCurrentKeyBoard()->Acquire();
		GameGlobal::GetCurrentKeyBoard()->GetDeviceState(sizeof(mKeyStates), (LPVOID)&mKeyStates);
	}

	
	GameGlobal::SetCurrentKeyState(mKeyStates);
	GameGlobal::SetCurrentKeyPress(pressKey);
	

}



void Game::Render()
{
	auto device = GameGlobal::GetCurrentDevice();
	auto scene = SceneManager::GetInstance()->GetCurrentScene();
	device->Clear(0, NULL, D3DCLEAR_TARGET, scene->GetBackcolor(), 0.0f, 0);

	{
		device->BeginScene();

		//bat dau ve
		GameGlobal::GetCurrentSpriteHandler()->Begin(D3DXSPRITE_ALPHABLEND);

		//draw here
		scene->Draw();

		//ket thuc ve
		GameGlobal::GetCurrentSpriteHandler()->End();

		device->EndScene();
	}

	device->Present(0, 0, 0, 0);
}

int Game::initWindow(int cmdShow)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;

	wc.hInstance = mHInstance;

	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;

	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WIN_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	//WS_OVERLAPPEDWINDOW <=> WS_EX_TOPMOST | WS_POPUP | WS_VISIBLE
	HWND hWnd = CreateWindow(
		WIN_NAME,
		WIN_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		GameGlobal::GetWidth(),
		GameGlobal::GetHeight(),
		NULL,
		NULL,
		mHInstance,
		NULL);

	GameGlobal::SetCurrentHINSTACE(mHInstance);
	GameGlobal::SetCurrentHWND(hWnd);

	ShowWindow(hWnd, cmdShow);
	UpdateWindow(hWnd);

	if (InitDevice() && InitKeyboard() )
	{
		Game *game = new Game(60);
	}

	return 0;

}

int Game::InitDevice()
{
	mD3d = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = GameGlobal::GetWidth();
	d3dpp.BackBufferHeight = GameGlobal::GetHeight();

	HRESULT dvresult = mD3d->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		GameGlobal::getCurrentHWND(),
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&mDevice);
	GameGlobal::SetCurrentDevice(mDevice);

	D3DXCreateSprite(GameGlobal::GetCurrentDevice(), &mSpriteHandler);
	GameGlobal::SetCurrentSpriteHandler(mSpriteHandler);

	return 1;
}



LRESULT Game::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	/*
su dung cac event cua window
*/
	switch (message)
	{
	case WM_DESTROY:
		GameGlobal::isGameRunning = false;
		PostQuitMessage(0);
		break;


		/*case WM_LBUTTONDOWN:
			SceneManager::GetInstance()->GetCurrentScene()->OnMouseDown((float)GET_X_LPARAM(lParam),
																		(float)GET_Y_LPARAM(lParam));
			break;*/

			//case WM_KEYDOWN:
			//	SceneManager::GetInstance()->GetCurrentScene()->OnKeyDown(wParam);
			//	break;

			//case WM_KEYUP:
			//	SceneManager::GetInstance()->GetCurrentScene()->OnKeyUp(wParam);
			//	break;



	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

void Game::InitLoop()
{
	MSG msg;

	float tickPerFrame = 1.0f / mFPS, delta = 0;

	while (GameGlobal::isGameRunning)
	{
		GameTime::GetInstance()->StartCounter();

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		delta += GameTime::GetInstance()->GetCouter();

		if (delta >= tickPerFrame)
		{
			Update((delta));
			delta = 0;
		}
		else
		{
			Sleep(tickPerFrame - delta);
			delta = tickPerFrame;
		}
	}
}