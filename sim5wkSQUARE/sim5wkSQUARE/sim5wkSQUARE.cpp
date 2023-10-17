#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#include <windows.h>



//기존
POINT startPoint = { 0 };
POINT endPoint = { 0 };
int isMouseLButtonPressed = 0;


// 윈도우의 이벤트를 처리하는 Callback 함수
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{

	case WM_PAINT:
	{
		HDC hdc = GetDC(hwnd);

		if (isMouseLButtonPressed)
		{
			// 핑크 사각형 만들기
			HBRUSH pinkBrush = CreateSolidBrush(RGB(255, 0, 255));
			RECT pinkRect;
			pinkRect.left = startPoint.x;
			pinkRect.top = startPoint.y;
			pinkRect.right = endPoint.x;
			pinkRect.bottom = endPoint.y;
			FillRect(hdc, &pinkRect, pinkBrush);
			DeleteObject(pinkBrush);
		}

		// 사각형의 크기 표시
		MoveToEx(hdc, startPoint.x, startPoint.y, NULL);
		LineTo(hdc, endPoint.x, startPoint.y); // 상단 가로선
		LineTo(hdc, endPoint.x, endPoint.y);   // 우측 세로선
		LineTo(hdc, startPoint.x, endPoint.y);   // 하단 가로선
		LineTo(hdc, startPoint.x, startPoint.y); // 좌측 세로선

		ReleaseDC(hwnd, hdc);
	}
	break;
	
	//마우스 클릭 했을 때
	case WM_LBUTTONDOWN:
	{
		startPoint.x = LOWORD(lParam);
		startPoint.y = HIWORD(lParam);
		isMouseLButtonPressed = 1;
	}
	break;

	//마우스 클릭 해제했을 때
	case WM_LBUTTONUP:
	{
		// 이전에 그린거 없애기
		HDC hdc = GetDC(hwnd);
		RECT rect;
		GetClientRect(hwnd, &rect);
		HBRUSH hBrush = CreateSolidBrush(GetSysColor(COLOR_WINDOW));
		FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1)); // 사각형 채우기
		DeleteObject(hBrush);
		ReleaseDC(hwnd, hdc);

		endPoint.x = LOWORD(lParam);
		endPoint.y = HIWORD(lParam);

		// 핑크색 사각형 나타남
		
		hdc = GetDC(hwnd);
		HBRUSH pinkBrush = CreateSolidBrush(RGB(255, 0, 255));
		RECT pinkRect;
		pinkRect.left = startPoint.x;
		pinkRect.top = startPoint.y;
		pinkRect.right = endPoint.x;
		pinkRect.bottom = endPoint.y;
		FillRect(hdc, &pinkRect, pinkBrush);
		DeleteObject(pinkBrush);
		ReleaseDC(hwnd, hdc);

		isMouseLButtonPressed = 0;
	}
	break;

	//마우스가 움직일때
	case WM_MOUSEMOVE:
	{
		// 마우스 이동 중
		if (isMouseLButtonPressed)
		{
			endPoint.x = LOWORD(lParam);
			endPoint.y = HIWORD(lParam);

			// WM_PAINT 메시지를 유발하여 사각형 표시
			InvalidateRect(hwnd, NULL, TRUE);
		}
	}
	break;

	// 리소스 정리
	case WM_DESTROY:

		//새로추가
	

	//기존
		PostQuitMessage(0);
		break;



	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return S_OK;
}
#ifdef UNICODE
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
#else
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR pCmdLine, _In_ int nCmdShow)
#endif
{
	/* 윈도우 클래스 선언.*/
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(wc));	// 모두 0으로 초기화.

	// 윈도우 클래스 값 설정
	wc.hInstance = hInstance;
	wc.lpszClassName = TEXT("Computer Software");
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_CROSS);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;

	// 윈도우 클래스 등록.
	if (RegisterClass(&wc) == 0)
	{
		MessageBox(NULL, L"RegisterClass failed!", L"Error", MB_ICONERROR);
		exit(-1);	//예외
	}

	// Window viewport 영역 조정
	RECT rect = { 150, 100, 800, 600 };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	// 윈도우 생성
	HWND hwnd = CreateWindow(
		wc.lpszClassName,
		TEXT("201807020 sim"),
		WS_OVERLAPPEDWINDOW,
		0, 0,
		width, height,
		NULL, NULL,
		hInstance,
		NULL
	);

	// 오류 검사
	if (hwnd == NULL)
	{
		MessageBox(NULL, L"CreateWindow failed!", L"Error", MB_ICONERROR);
		exit(-1);
	}

	// 윈도우 창
	ShowWindow(hwnd, SW_SHOW); // 윈도우 창 활성화
	UpdateWindow(hwnd); // 위 코드와 같이 사용

	// 메시지 처리 루프
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		// 메시지 처리
		if (GetMessage(&msg, hwnd, 0, 0))
		{

			// 메시지 해석
			TranslateMessage(&msg);
			// 메시지를 처리해야할 곳에 전달
			DispatchMessage(&msg);

		}
	}

	//종료 메세지 전달
	return (int)msg.wParam;

}