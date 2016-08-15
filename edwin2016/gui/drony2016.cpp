/** 
 *	Entry point for the application
 */

#include "stdafx.h"
#include "drony2016.h"

// Global variables
HINSTANCE hCurrentInstance;		// current instance
HWND hGamewindowWnd;			// the gamewindow
BYTE* pGamearea;				// the gamearea
UINT16 nGameareaW, nGameareaH;	// gamearea width and height
LOCATION oDroneLoc;				// current drone location on the map
LOCATION oHomeLoc;				// homebase location on the map
UINT16 nTargetCount;			// number of targets in the area
UINT16 nTargetsFound;			// number of targets found
UINT16 nEnergyCount;			// number of energy targets in the area
UINT16 nEnergyFound;		// number of energy targets found
LOCATION* pTargetLoc;			// target locations
LOCATION* pEnergyTargetLoc;		// energy target locations
BYTE nGameMode;					// modi of the game: 0 = maindialog, 1 = game, 2 = pauze
UINT16 nGameTimer;				// running timer

/**
 * The Windows main() method
 * @param hInstance				Windows system identifier for this program
 * @param hPrevInstance			Windows system identifier for the calling program
 * @param sCmdLine				The commandline used to call this program
 * @param nCmdShow				The show-modus to be used for the gamewindow
 * @return						The program finishing status 
 */
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR sCmdLine, _In_ int nCmdShow)
{
	BYTE nError;					// return error (0 = none)
	BOOL bHomeFound = FALSE;		// status of homebase search
	UINT16 x, y;					// position counter
	WCHAR sText[250];				// text formatting buffer
	HACCEL hAccelTable = NULL;
	MSG oMessage;

	// Suppress compiler warning of unused parameters
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(sCmdLine);

	// Store the current instance
	hCurrentInstance = hInstance;

	// Init the shorcut keys (accelerators)
	hAccelTable = LoadAccelerators(hCurrentInstance, MAKEINTRESOURCE(IDR_ACCELERATOR));

	// Load and init the gamearea
	pGamearea = GameLoadArea(nError, GAMEAREA_NAME, nGameareaW, nGameareaH);
	if (nError > 0)
	{
		wsprintf(sText, _T("The gamearea could not be loaded!\n(error %d, ln %d, col %d)"), nError, nGameareaH + 1, nGameareaW + 1);
		MessageBox(NULL, sText, _T("Loading..."), MB_OK | MB_ICONERROR);

		// Free gamearea memory
		free(pGamearea);
		return FALSE;
	};
	
	// Count and check gamearea
	bHomeFound = FALSE;
	nTargetCount = 0;
	for (y = 0; y < nGameareaH; y++)
		for (x = 0; x < nGameareaW; x++)
		{
			// Position is homebase?
			if (!bHomeFound && pGamearea[x + nGameareaW * y] == GAMEAREA_HOME)
			{
				bHomeFound = TRUE;
				oHomeLoc.x = x; oHomeLoc.y = y;
			};

			// Position is target (counting only)?
			if (pGamearea[FROM_2D_TO_1D(x, y)] == GAMEAREA_DROP0)
			{
				nTargetCount++;
			};

			if (pGamearea[FROM_2D_TO_1D(x, y)] == GAMEAREA_ENERGY)
			{
				nEnergyCount++;
			};
		};

	if (!bHomeFound)
	{
		wsprintf(sText, _T("The homebase is not found!"));
		MessageBox(NULL, sText, _T("Loading..."), MB_OK | MB_ICONERROR);

		// Free gamearea memory
		free(pGamearea);
		return FALSE;
	};

	pTargetLoc = (LOCATION*)malloc(sizeof(LOCATION) * nTargetCount);
	nTargetCount = 0;
	for (y = 0; y < nGameareaH; y++)
		for (x = 0; x < nGameareaW; x++)
		{
			// Position is target?
			if (pGamearea[FROM_2D_TO_1D(x, y)] == GAMEAREA_DROP0)
			{
				pTargetLoc[nTargetCount].x = x;
				pTargetLoc[nTargetCount].y = y;
				nTargetCount++;
			};
		};

	pEnergyTargetLoc = (LOCATION*)malloc(sizeof(LOCATION) * nEnergyCount);
	nEnergyCount = 0;
	for (y = 0; y < nGameareaH; y++)
		for (x = 0; x < nGameareaW; x++)
		{
			// Position is target?
			if (pGamearea[FROM_2D_TO_1D(x, y)] == GAMEAREA_ENERGY)
			{
				pEnergyTargetLoc[nEnergyCount].x = x;
				pEnergyTargetLoc[nEnergyCount].y = y;
				nEnergyCount++;
			};
		};

	// Minimal game init
	oDroneLoc = oHomeLoc;
	nGameMode = 0;
	
	// Show game info
	//wsprintf(sText, _T("Gamearea size: %d x %d\nHome: %d x %d\nTarget count: %d"), nGameareaW, nGameareaH, oHomeLoc.x, oHomeLoc.y, nTargetCount);
	//MessageBox(NULL, sText, _T("Gamearea loaded"), MB_OK | MB_ICONINFORMATION);

	// Register, init and show the gamewindow
	RegisterGamewindowClass(hCurrentInstance);
	if (!InitGamewindowInstance(hCurrentInstance, nCmdShow))
	{
		// Free memory
		free(pGamearea);
		free(pTargetLoc);
		return FALSE;
	};

	// Main message loop
	while (GetMessage(&oMessage, NULL, 0, 0))
	{
		if (!TranslateAccelerator(oMessage.hwnd, hAccelTable, &oMessage))
		{
			TranslateMessage(&oMessage);
			DispatchMessage(&oMessage);
		}
	}

	// Free memory
	free(pGamearea);
	free(pTargetLoc);

	return (int)oMessage.wParam;
};
