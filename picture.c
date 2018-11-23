#include <windows.h> 

const char * my_classname = "simple_window_class"; // This is just a label for Windows to use. It's not displayed anywhere. 

HBITMAP my_picture; // We will store a handle to the bitmap (picture) here. 

// This is the function that handles drawing things on the screen, pushing buttons, etc. 
LRESULT CALLBACK MyWndProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) { 
	switch (uMsg) { 
	case WM_CREATE: 
		// Window is being created. Let's load our picture now. 
		my_picture = (HBITMAP) LoadImage (NULL, "IMG_6788.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE); 
		if (!my_picture) { 
			// If LoadImage () returned NULL, it means there's an error. 
			MessageBox (NULL, "Error loading picture file. ", NULL, 0); 
		} 
		break; 
	case WM_PAINT: 
		// It's time to draw the window! We'll put the code here in braces, just so it has its own scope. 
		{ 
			// Drawing something actually has a lot of parts to it. We need all these variables to keep track of things: 
			PAINTSTRUCT ps; 
			HDC hdc; 
			BITMAP bitmap; 
			HDC hdcMem; 
			HGDIOBJ oldBitmap; 
			RECT clientArea; 
			// Start drawing (BeginPaint ()), create some memory for drawing in (CreateCompatibleDC ()), and select our picture (SelectObject ()): 
			hdc = BeginPaint (hWnd, &ps); 
			hdcMem = CreateCompatibleDC (hdc); 
			oldBitmap = SelectObject (hdcMem, my_picture); 
			// Check how large the window client (drawing) area is: 
			GetClientRect (hWnd, &clientArea); 
			// Set up the type of pixel stretching we want: 
			SetStretchBltMode (hdc, HALFTONE); 
			SetBrushOrgEx (hdc, 0, 0, NULL); 
			// Copy the pixels from our picture to the screen memory: 
			GetObject (my_picture, sizeof (bitmap), &bitmap); 
			StretchBlt (hdc, 0, 0, clientArea.right - clientArea.left, clientArea.bottom - clientArea.top, hdcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY); 
			// Put things back to how there were before we started touching them: 
			SelectObject (hdcMem, oldBitmap); 
			DeleteDC (hdcMem); 
			EndPaint (hWnd, &ps); 
		} 
		break; 
	case WM_SIZE: 
		// The window size changed. Let's just tell it to redraw the picture (because the picture size also changed as a result). 
		InvalidateRect (hWnd, NULL, TRUE); 
		break; 
	case WM_DESTROY: 
		// Window is being destroyed. Let's delete the picture from memory - so that other programs can use more RAM after we're done. 
		DeleteObject (my_picture); 
		// And let's exit the message loop now, from inside main (). 
		PostQuitMessage (0); 
		break; 
	default: 
	return DefWindowProc (hWnd, uMsg, wParam, lParam); 
	} 
	return 0; 
} 

// This is the main function - it's entered when the program starts. 
int main (int argc, char * argv []) { 
	WNDCLASSEX wc; 
	HWND hWnd; 
	MSG msg; 
	HINSTANCE hInstance = GetModuleHandle (NULL); 
	// 1. Register window class: 
	wc.cbSize = sizeof (WNDCLASSEX); 
	wc.style = 0; 
	wc.lpfnWndProc = MyWndProc; // Give it the memory address of the function that handles drawing things on the screen, pushing buttons, etc. 
	wc.cbClsExtra = 0; 
	wc.cbWndExtra = 0; 
	wc.hInstance = hInstance; 
	wc.hIcon = LoadIcon (NULL, IDI_APPLICATION); 
	wc.hIconSm = wc.hIcon; 
	wc.hCursor = LoadCursor (NULL, IDC_ARROW); 
	wc.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1); 
	wc.lpszMenuName = NULL; 
	wc.lpszClassName = my_classname; 
	if (!RegisterClassEx (&wc)) { 
		// If RegisterClassEx () returns NULL, it means there's an error. Display an error message. 
		MessageBox (NULL, "Failed to register window class. ", NULL, MB_ICONEXCLAMATION | MB_OK); 
		return 1; 
	} 
	// 2. Create and show the window: 
	hWnd = CreateWindowEx (WS_EX_CLIENTEDGE, 
		my_classname, 
		"Window Title - you can change this", 
		WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT, // X position of window on the screen 
		CW_USEDEFAULT, // Y position of window on the screen 
		600, // Window width 
		400, // Window height 
		NULL, NULL, hInstance, NULL // Other parameters, such as menus; not using any of those right now 
	); 
	if (!hWnd) { 
		// If CreateWindowEx () returns NULL, that also means there's an error. 
		MessageBox (NULL, "Failed to create a window. ", NULL, MB_ICONEXCLAMATION | MB_OK); 
		return 1; 
	} 
	ShowWindow (hWnd, SW_SHOWDEFAULT); 
	UpdateWindow (hWnd); 
	// 3. The message loop - needed for checking for button clicks, etc.: 
	while (GetMessage (&msg, NULL, 0, 0)) { 
		TranslateMessage (&msg); 
		DispatchMessage (&msg); 
	} 
	return msg.wParam; 
} 

