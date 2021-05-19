#include <windows.h>

// 主窗口句柄
HWND ghMainWnd = 0;


bool InitWindowsApp(HINSTANCE instanceHandle, int show);

// 消息循环
int Run();


// 窗口过程
LRESULT CALLBACK
WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


int WINAPI
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow)
{
	if (!InitWindowsApp(hInstance, nCmdShow))
		return 0;

	return Run();
}

bool InitWindowsApp(HINSTANCE instanceHandle, int show)
{
	// 用于描述窗口的结构体
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW; // 宽高发生变化重新绘制
	wc.lpfnWndProc = WndProc; // 关联窗口过程函数
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = instanceHandle;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // 窗口工作区背景颜色
	wc.lpszMenuName = 0;
	wc.lpszClassName = L"BasicWndClass"; // 关联当前结构体时利用此属性


	// 在windows中为WNDCLASS注册一个实例
	if (!RegisterClass(&wc))
	{
		MessageBox(0, L"RegisterClass FAILED", 0, 0);
		return false;
	}

	ghMainWnd = CreateWindow(
		L"BasicWndClass", // 注册实例的名字
		L"Win32Basic", // 窗口标题
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		0,
		0,
		instanceHandle,
		0);

	if (ghMainWnd == 0)
	{
		MessageBox(0, L"CreateWindow FAILED", 0, 0);
		return false;
	}

	// 显示窗口，更新
	ShowWindow(ghMainWnd, show);
	UpdateWindow(ghMainWnd);

	return true;
}

//int Run()
//{
//	MSG msg = { 0 };
//
//	BOOL bRet = 1;
//	while ((bRet = GetMessage(&msg, 0, 0, 0)) != 0)
//	{
//		if (bRet == -1)
//		{
//			MessageBox(0, L"GetMessage FAILED", L"Error", MB_OK);
//			break;
//		}
//		else
//		{
//			TranslateMessage(&msg); // 按键转换
//			DispatchMessage(&msg); // 消息分派
//		}
//	}
//
//	return (int)msg.wParam;
//}

// 游戏中没有收到消息也要更新
// 一种更灵活的消息循环
int Run()
{
	MSG msg = { 0 };

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// 没有收到消息时启用游戏逻辑代码或动画
		}
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK
WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch ( msg )
	{
	case WM_LBUTTONDOWN:
		MessageBox(0, L"Hello, World", L"Hello", MB_OK);
		return 0;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			DestroyWindow(ghMainWnd);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0); // 发出WM_QUIT
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam); // 默认窗口过程
}
