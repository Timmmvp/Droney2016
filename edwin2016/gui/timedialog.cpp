/**
* The new Crash dialog
*/

#include "stdafx.h"
#include "timedialog.h"

// Global variables

// Local variables

/**
* Message handler for the Crash dialog
* @param hDlg					Dialog identifier
* @param nMessage				Message identifier
* @param wParam				Word-type parameter
* @param lParam				Long-type parameter
* @return						The message (subtree) processed the message
*/
INT_PTR CALLBACK TimedialogProc(HWND hDlg, UINT nMessage, WPARAM wParam, LPARAM lParam)
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

		if (nId == IDOK || nId == IDCANCEL)
		{
			EndDialog(hDlg, nId);

			return (INT_PTR)TRUE;
		};
		break;
	};
	};

	return (INT_PTR)FALSE;
};
