#include <Windows.h>

#include "Timing/Timing.h"
#include "Windows/Windows.h"

int WINAPI WinMain(const HINSTANCE i_hInstance, const HINSTANCE i_hprevInstance, const PSTR i_cmdLine, const int i_showCmd)
{
	const int topx = 150;
	const int topy = 20;
	const int windowWidth = 1200;
	const int windowHeight = 800;
	Engine::Windows::WindowData myWindow(i_hInstance, topx, topy, windowWidth, windowHeight);

	ShowWindow(myWindow.WindowHandle() , i_showCmd);
	UpdateWindow(myWindow.WindowHandle());
	
	Engine::Timing::Timing* timer = Engine::Timing::Timing::GetTimer();
	timer->Initialize();

	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//game loop
		}
	}

	return (int)msg.wParam;
}