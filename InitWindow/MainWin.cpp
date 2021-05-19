#include <windows.h>

// �����ھ��
HWND ghMainWnd = 0;


bool InitWindowsApp(HINSTANCE instanceHandle, int show);

// ��Ϣѭ��
int Run();


// ���ڹ���
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
	// �����������ڵĽṹ��
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW; // ��߷����仯���»���
	wc.lpfnWndProc = WndProc; // �������ڹ��̺���
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = instanceHandle;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // ���ڹ�����������ɫ
	wc.lpszMenuName = 0;
	wc.lpszClassName = L"BasicWndClass"; // ������ǰ�ṹ��ʱ���ô�����


	// ��windows��ΪWNDCLASSע��һ��ʵ��
	if (!RegisterClass(&wc))
	{
		MessageBox(0, L"RegisterClass FAILED", 0, 0);
		return false;
	}

	ghMainWnd = CreateWindow(
		L"BasicWndClass", // ע��ʵ��������
		L"Win32Basic", // ���ڱ���
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

	// ��ʾ���ڣ�����
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
//			TranslateMessage(&msg); // ����ת��
//			DispatchMessage(&msg); // ��Ϣ����
//		}
//	}
//
//	return (int)msg.wParam;
//}

// ��Ϸ��û���յ���ϢҲҪ����
// һ�ָ�������Ϣѭ��
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
			// û���յ���Ϣʱ������Ϸ�߼�����򶯻�
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
		PostQuitMessage(0); // ����WM_QUIT
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam); // Ĭ�ϴ��ڹ���
}
