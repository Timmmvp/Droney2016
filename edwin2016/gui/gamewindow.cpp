/**
* The gamewindow
*/

#include "stdafx.h"
#include "gamewindow.h"
#include "GameRules.h"

// Global variables

// Local variables
HBITMAP hGameareaGrass;			// bitmap grass
HBITMAP hGameareaStone;			// bitmap stone
HBITMAP hGameareaHome;			// bitmap homebase
HBITMAP hGameareaDrop0;			// bitmap target normal
HBITMAP hGameareaDrop1;			// bitmap target visited
HBITMAP hGameareaWater;			// bitmap water
HBITMAP hGameareaTrees;			// bitmap trees
HBITMAP hGameareaDrone;			// bitmap drone
HBITMAP hGameareaEnergy;		// bitmap energy
HWND hChildTitle;				// game title
HWND hChildAuthor;				// game author
HWND hChildTime;				// game time status
HWND hChildTargets;				// game target status
HWND hChildHighscore;			// game highscore
HWND hChildHighscoreTime;		// game highscore time
HWND hChildHighscoreName;		// game highscore name
HWND hChildCopyright;			// game copyright

/**
 * Register the gamewindow class
 * @param hInstance				The identifier of this process
 * @return						Implies the reistration was OK
 */
ATOM RegisterGamewindowClass(HINSTANCE hInstance)
{
	WNDCLASSEXW oWinClass;

	oWinClass.cbSize = sizeof(WNDCLASSEX);

	oWinClass.style				= 0;
	oWinClass.lpfnWndProc		= GamewindowProc;
	oWinClass.cbClsExtra		= 0;
	oWinClass.cbWndExtra		= 0;
	oWinClass.hInstance			= hInstance;
	oWinClass.hIcon				= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));
	oWinClass.hCursor			= LoadCursor(nullptr, IDC_ARROW);
	oWinClass.hbrBackground		= CreateSolidBrush(RGB(180, 180, 180));
	oWinClass.lpszMenuName		= nullptr;
	oWinClass.lpszClassName		= _T("gamewindow");
	oWinClass.hIconSm			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));

	return RegisterClassExW(&oWinClass);
};

/**
 * Create and show the gamewindow
 * @param hInstance				The identifier of this process
 * @param nCmdShow				The show-modus to be used for the gamewindow
 * @return						Implies the creation went successful 
 */
BOOL InitGamewindowInstance(HINSTANCE hInstance, int nCmdShow)
{
	hGamewindowWnd = CreateWindowW(_T("gamewindow"), _T("Drony 2016"), WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, 640, 440, nullptr, nullptr, hInstance, nullptr);
	if (!hGamewindowWnd)
	{
		return FALSE;
	};

	// Mark window for show and do show it
	ShowWindow(hGamewindowWnd, nCmdShow);
	UpdateWindow(hGamewindowWnd);

	// Show the main dialog
	DialogBox(hCurrentInstance, MAKEINTRESOURCE(IDD_MAINDIALOG), hGamewindowWnd, (DLGPROC)MaindialogProc);

	return TRUE;
};

/**
 * Message handler for the gamewindow
 * @param hWnd					Window identifier
 * @param nMessage				Message identifier
 * @param wParam				Word-type parameter
 * @param lParam				Long-type parameter
 * @return						The message (subtree) processed the message
 */
LRESULT CALLBACK GamewindowProc(HWND hWnd, UINT nMessage, WPARAM wParam, LPARAM lParam)
{
	// Handle each message
	switch (nMessage)
	{
		// Create the window objects
		case WM_CREATE:
		{
			HFONT hFont;

			// Preload all bitmaps
			hGameareaEnergy = (HBITMAP)LoadImage(hCurrentInstance, MAKEINTRESOURCE(IDB_GAMEBLOCKS_ENERGY), IMAGE_BITMAP, 0, 0, LR_SHARED);
			hGameareaGrass	= (HBITMAP)LoadImage(hCurrentInstance, MAKEINTRESOURCE(IDB_GAMEBLOCKS_GRASS ), IMAGE_BITMAP, 0, 0, LR_SHARED);
			hGameareaStone	= (HBITMAP)LoadImage(hCurrentInstance, MAKEINTRESOURCE(IDB_GAMEBLOCKS_STONE ), IMAGE_BITMAP, 0, 0, LR_SHARED);
			hGameareaHome	= (HBITMAP)LoadImage(hCurrentInstance, MAKEINTRESOURCE(IDB_GAMEBLOCKS_HOME  ), IMAGE_BITMAP, 0, 0, LR_SHARED);
			hGameareaDrop0	= (HBITMAP)LoadImage(hCurrentInstance, MAKEINTRESOURCE(IDB_GAMEBLOCKS_DROP0 ), IMAGE_BITMAP, 0, 0, LR_SHARED);
			hGameareaDrop1	= (HBITMAP)LoadImage(hCurrentInstance, MAKEINTRESOURCE(IDB_GAMEBLOCKS_DROP1 ), IMAGE_BITMAP, 0, 0, LR_SHARED);
			hGameareaWater	= (HBITMAP)LoadImage(hCurrentInstance, MAKEINTRESOURCE(IDB_GAMEBLOCKS_WATER ), IMAGE_BITMAP, 0, 0, LR_SHARED);
			hGameareaTrees	= (HBITMAP)LoadImage(hCurrentInstance, MAKEINTRESOURCE(IDB_GAMEBLOCKS_TREES ), IMAGE_BITMAP, 0, 0, LR_SHARED);
			hGameareaDrone	= (HBITMAP)LoadImage(hCurrentInstance, MAKEINTRESOURCE(IDB_GAMEBLOCKS_DRONE ), IMAGE_BITMAP, 0, 0, LR_SHARED);
			

			// Status sitebar
			hChildTitle = CreateWindow(_T("STATIC"), _T("Drony 2016"), WS_VISIBLE | WS_CHILD, 430, 30, 200, 50, hWnd, NULL, hCurrentInstance, NULL);
			hFont = CreateFont(35, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
			SendMessage(hChildTitle, WM_SETFONT, WPARAM(hFont), TRUE);

			hChildAuthor = CreateWindow(_T("STATIC"), _T("by Edwin Boer \nEditted by Tim van Putten"), WS_VISIBLE | WS_CHILD, 430, 70, 150, 40, hWnd, NULL, hCurrentInstance, NULL);
			hFont = CreateFont(15, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
			SendMessage(hChildAuthor, WM_SETFONT, WPARAM(hFont), TRUE);

			hChildTime = CreateWindow(_T("STATIC"), _T("Time: 00:00"),       WS_VISIBLE | WS_CHILD, 430, 140, 200, 30, hWnd, NULL, hCurrentInstance, NULL);
			hChildTargets = CreateWindow(_T("STATIC"), _T("Targets: 0 / 0"), WS_VISIBLE | WS_CHILD, 430, 180, 200, 30, hWnd, NULL, hCurrentInstance, NULL);
			hChildHighscore = CreateWindow(_T("STATIC"), _T("High Score"),   WS_VISIBLE | WS_CHILD, 430, 235, 200, 30, hWnd, NULL, hCurrentInstance, NULL);
			hFont = CreateFont(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
			SendMessage(hChildTime, WM_SETFONT, WPARAM(hFont), TRUE);
			SendMessage(hChildTargets, WM_SETFONT, WPARAM(hFont), TRUE);
			SendMessage(hChildHighscore, WM_SETFONT, WPARAM(hFont), TRUE);

			hChildHighscoreTime = CreateWindow(_T("STATIC"), _T("10:00"), WS_VISIBLE | WS_CHILD, 440, 270, 100, 20, hWnd, NULL, hCurrentInstance, NULL);
			hChildHighscoreName = CreateWindow(_T("STATIC"), _T("Edwin"), WS_VISIBLE | WS_CHILD, 440, 290, 100, 20, hWnd, NULL, hCurrentInstance, NULL);
			hFont = CreateFont(15, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
			SendMessage(hChildHighscoreTime, WM_SETFONT, WPARAM(hFont), TRUE);
			SendMessage(hChildHighscoreName, WM_SETFONT, WPARAM(hFont), TRUE);

			hChildCopyright = CreateWindow(_T("STATIC"), _T("(c) 2016 HvA"), WS_VISIBLE | WS_CHILD, 430, 350, 100, 20, hWnd, NULL, hCurrentInstance, NULL);
			hFont = CreateFont(15, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
			SendMessage(hChildCopyright, WM_SETFONT, WPARAM(hFont), TRUE);

			// Start timer in seconds
			nGameMode = GAMEMODE_MENU;
			SetTimer(hWnd, IDT_GAMETIMER, 1000, (TIMERPROC)NULL);

			// Update the target count
			SetTargetCount();

			break; 
		};

		// Redraw the window area
		case WM_PAINT:
		{
			PAINTSTRUCT oPaint;
			HDC hDC, hMemDC;
			
			// Init the in-memory devicecontext
			hDC = BeginPaint(hWnd, &oPaint);
			hMemDC = CreateCompatibleDC(hDC);

			// Build the gamearea
			for (INT32 y = -12; y <= 12; y++)
				for (INT32 x = -12; x <= 12; x++)
				{
					INT32 xx = (INT32)oDroneLoc.x + x;
					INT32 yy = (INT32)oDroneLoc.y + y;

					// Show only in range of the gamearea
					if (0 <= xx && xx < nGameareaW && 0 <= yy && yy < nGameareaH)
					{
						if (x == 0 && y == 0)
						{
							SelectObject(hMemDC, hGameareaDrone);
						}
						else
						{
							switch (pGamearea[xx + nGameareaW * yy])
							{
								case GAMEAREA_GRASS: SelectObject(hMemDC, hGameareaGrass); break;
								default:
								case GAMEAREA_STONE:	SelectObject(hMemDC, hGameareaStone); break;
								case GAMEAREA_HOME:		SelectObject(hMemDC, hGameareaHome);  break;
								case GAMEAREA_DROP0:	SelectObject(hMemDC, hGameareaDrop0); break;
								case GAMEAREA_DROP1:	SelectObject(hMemDC, hGameareaDrop1); break;
								case GAMEAREA_WATER:	SelectObject(hMemDC, hGameareaWater); break;
								case GAMEAREA_TREES:	SelectObject(hMemDC, hGameareaTrees); break;
								case GAMEAREA_ENERGY:	SelectObject(hMemDC, hGameareaEnergy); break;
							};
						};
						BitBlt(hDC, (12 + x) * GAMEAREA_BLOCKSIZE, (12 + y) * GAMEAREA_BLOCKSIZE, GAMEAREA_BLOCKSIZE, GAMEAREA_BLOCKSIZE, hMemDC, 0, 0, SRCCOPY);
					}
					else
					{
						// This area will be the 'old' stone not refreshed blocks, so no action needed
					};
				};

			// Finish the devicecontext
			DeleteDC(hMemDC);
			EndPaint(hWnd, &oPaint);
			break;
		};

		// Check system keys
		case WM_KEYDOWN:
		{
			switch (wParam)
			{
				// ESC
				case VK_ESCAPE:
					nGameMode = GAMEMODE_MENU;

					// Show the main dialog
					DialogBox(hCurrentInstance, MAKEINTRESOURCE(IDD_MAINDIALOG), hWnd, (DLGPROC)MaindialogProc);

					break;

				// Spacebar
				case VK_SPACE:
					nGameMode = GAMEMODE_PAUZE;
					MessageBox(hWnd, _T("Ready to continue?"), _T("Pauze"), MB_OK | MB_ICONQUESTION);
					nGameMode = GAMEMODE_GAME;

					break;

				// Cursor up
				case VK_UP:
					if (oDroneLoc.y > 0 && CheckMove(oDroneLoc.x, oDroneLoc.y - 1))
					{
						oDroneLoc.y--;
						UpdateWindowAfterVisit();
					};
					break;

				// Cursor right
				case VK_RIGHT:
					if (oDroneLoc.x < nGameareaW && CheckMove(oDroneLoc.x + 1, oDroneLoc.y))
					{
						oDroneLoc.x++;
						UpdateWindowAfterVisit();
					};
					break;

				// Cursor down
				case VK_DOWN:
					if (oDroneLoc.y < nGameareaH && CheckMove(oDroneLoc.x, oDroneLoc.y + 1))
					{
						oDroneLoc.y++;
						UpdateWindowAfterVisit();
					};
					break;

				// Cursor left
				case VK_LEFT:
					if (oDroneLoc.x > 0 && CheckMove(oDroneLoc.x - 1, oDroneLoc.y))
					{
						oDroneLoc.x--;
						UpdateWindowAfterVisit();
					};
					break;
			};

			break;
		};

		// Update the timer
		case WM_TIMER:
		{
			WCHAR sText[250];	// text buffer

			switch (wParam)
			{
				case IDT_GAMETIMER:
				{
					// Only update if in game mode
					if (nGameMode == GAMEMODE_GAME)
					{
						nGameTimer--;
						wsprintf(sText, _T("Time: %02d:%02d"), nGameTimer / 60, nGameTimer % 60);
						SetWindowText(hChildTime, sText);
					};

					break;
				};
			};

			return 0;
		};

		// Make sure labels have a transparent background
		case WM_CTLCOLORSTATIC:
		{
			HWND hChild = (HWND)lParam;
			HDC hDC = (HDC)wParam;

			if (hChild == hChildTitle)
			{
				SetTextColor(hDC, RGB(0, 0, 255));
				SetBkMode(hDC, TRANSPARENT);
			};
			if (hChild == hChildAuthor)
			{
				SetTextColor(hDC, RGB(50, 50, 70));
				SetBkMode(hDC, TRANSPARENT);
			};
			if (hChild == hChildTime)
			{
				SetTextColor(hDC, RGB(0, 0, 0));
				SetBkColor(hDC, RGB(180, 180, 180));
			};
			if (hChild == hChildTargets)
			{
				SetTextColor(hDC, RGB(0, 0, 0));
				SetBkColor(hDC, RGB(180, 180, 180));
			};
			if (hChild == hChildHighscore)
			{
				SetTextColor(hDC, RGB(0, 0, 0));
				SetBkColor(hDC, RGB(180, 180, 180));
			};
			if (hChild == hChildHighscoreTime)
			{
				SetTextColor(hDC, RGB(0, 0, 70));
				SetBkColor(hDC, RGB(180, 180, 180));
			};
			if (hChild == hChildHighscoreName)
			{
				SetTextColor(hDC, RGB(0, 0, 70));
				SetBkColor(hDC, RGB(180, 180, 180));
			};
			if (hChild == hChildCopyright)
			{
				SetTextColor(hDC, RGB(50, 50, 70));
				SetBkMode(hDC, TRANSPARENT);
			};

			return (LRESULT)GetStockObject(NULL_BRUSH);
		};

		// The program is closed
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		};

		// Default handling
		default:
		{
			return DefWindowProc(hWnd, nMessage, wParam, lParam);
		};
	};

	return 0;
};

/**
 * Update the targetcount
 */
void SetTargetCount()
{
	WCHAR sText[250];	// text buffer
	//if (pGamearea[FROM_2D_TO_1D(oDroneLoc.x, oDroneLoc.y)] == GAMEAREA_DROP0) GAMEAREA_DROP0 = GAMEAREA_DROP1 && nTargetsFound++;
	// Update the content
	wsprintf(sText, _T("Targets: %d / %d"), nTargetsFound, nTargetCount);
	SetWindowText(hChildTargets, sText);
};

/**
 * Update the gamewindow
 */
void UpdateGamewindow()
{
	RedrawWindow(hGamewindowWnd, NULL, NULL, RDW_INVALIDATE);
};

/**
 * Check allowed move
 * @param x						The new location x
 * @param y						The new location y
 * @return						Implies the move is allowed
 */
BOOL CheckMove(UINT16 x, UINT16 y)
{
	//if (pGamearea[FROM_2D_TO_1D(x, y)] == GAMEAREA_ENERGY) EnergyTargetRule();
	UNREFERENCED_PARAMETER(x); //onderdrukt compiler-foutmeldingen, omdat deze variabelen nu nog niet gebruikt worden
	UNREFERENCED_PARAMETER(y);
	UpdateWindowAfterVisit();
	return TRUE;
}

	/**
	* Check if the game is over (in release build all targets must be found, in debug you can choose a different implementation)
	*/
	BOOL AllTargetsFound() 
	{
		#ifdef _DEBUG
			return nTargetsFound == nTargetCount;
		#else
			return nTargetsFound == nTargetCount;
		#endif
	}


	/**
	 * Apply the sign on the current drone location
	 */
	void ApplyLocation()
	{
		switch (pGamearea[FROM_2D_TO_1D(oDroneLoc.x, oDroneLoc.y)])
		{
		case GAMEAREA_HOME:
			if (AllTargetsFound())
			{
				DroneAtHomeRule();
			}
			break;
		
		case GAMEAREA_DROP0:
			MarkTargetFoundRule();
			break;

		case GAMEAREA_TREES:
			DelayOnTreeHitRule();
			break; 

		case GAMEAREA_STONE:
			RockCrashRule();
			break; 

		case GAMEAREA_ENERGY:
			EnergyTargetRule();
			break;
		};
	};

	void UpdateWindowAfterVisit()
	{
		UpdateGamewindow();
		ApplyLocation();
		SetTargetCount();	
	}