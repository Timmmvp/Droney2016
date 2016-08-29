/**
 * The main dialog
 */

#include "stdafx.h"
#include "drony2016.h"
#include "maindialog.h"
#include "GameRules.h"

/**
 * Message handler for the main dialog
 * @param hDlg					Dialog identifier
 * @param nMessage				Message identifier
 * @param wParam				Word-type parameter
 * @param lParam				Long-type parameter
 * @return						The message (subtree) processed the message
 */
INT_PTR CALLBACK MaindialogProc(HWND hDlg, UINT nMessage, WPARAM wParam, LPARAM lParam)
{
	// Suppress compiler warning of unused parameters
	UNREFERENCED_PARAMETER(lParam);

	// Handle each message
	switch (nMessage)
	{
		// Create the window objects
		case WM_INITDIALOG:
		{
			HWND hParent;
			RECT oNewRect, oDlgRect, oParentRect;

			// Get the owner window and dialog box rectangles
			if ((hParent = GetParent(hDlg)) == NULL)
			{
				hParent = GetDesktopWindow();
			};
			GetWindowRect(hParent, &oParentRect);
			GetWindowRect(hDlg, &oDlgRect);
			CopyRect(&oNewRect, &oParentRect);

			// Offset the owner and dialog box rectangles so that right and bottom 
			// values represent the width and height, and then offset the owner again 
			// to discard space taken up by the dialog box
			OffsetRect(&oDlgRect, -oDlgRect.left, -oDlgRect.top);
			OffsetRect(&oNewRect, -oNewRect.left, -oNewRect.top);
			OffsetRect(&oNewRect, -oDlgRect.right, -oDlgRect.bottom);

			// The new position is the sum of half the remaining space and the owner's 
			// original position. 
			SetWindowPos(hDlg,
				HWND_TOP,
				oParentRect.left + (oNewRect.right / 2),
				oParentRect.top + (oNewRect.bottom / 2),
				0, 0,          // Ignores size arguments. 
				SWP_NOSIZE);

			return (INT_PTR)TRUE;
		};

		// Catch the commands
		case WM_COMMAND:
		{
			int nId = LOWORD(wParam);

			// Start the game
			if (nId == IDOK)
			{
				InitNewGameRule();

				// Switch the game on
				UpdateGamewindow();
				SetTargetCount();
				ResetRule();
				nGameMode = GAMEMODE_GAME;

				// Close the dialog
				EndDialog(hDlg, nId);

				return (INT_PTR)TRUE;
			};

			// Exit the game
			if (nId == IDABORT)
			{
				// Destroy parent window
				DestroyWindow(GetParent(hDlg));

				return (INT_PTR)TRUE;
			};

			break;
		};

		// Check system keys
		case WM_KEYDOWN:
		{
			switch (wParam)
			{
				// ESC
				case VK_ESCAPE:
					// Destroy parent window
					DestroyWindow(GetParent(hDlg));

					return (INT_PTR)TRUE;
			};

			break;
		};
	};
	return (INT_PTR)FALSE;
};
