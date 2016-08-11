#include "stdafx.h"
#include "gamewindow.h"
#include "crashdialog.h"


#define DELAY		15

void WarningSound()
{
	Beep(750, 50);
}

void ScoreSound()
{
	Beep(1500, 50);
}

void MarkTargetFoundRule()
{
	nTargetsFound++;
	pGamearea[FROM_2D_TO_1D(oDroneLoc.x, oDroneLoc.y)] = GAMEAREA_DROP1;
	ScoreSound();
}

void DroneAtHomeRule()
{
	nGameMode = GAMEMODE_MENU;
	
	// Show the score dialog
	DialogBox(hCurrentInstance, MAKEINTRESOURCE(IDD_SCOREDIALOG), hGamewindowWnd, (DLGPROC)ScoredialogProc);

	// Show the main dialog
	DialogBox(hCurrentInstance, MAKEINTRESOURCE(IDD_MAINDIALOG), hGamewindowWnd, (DLGPROC)MaindialogProc);
}

void DelayOnTreeHitRule()
{
	nGameTimer += DELAY;
	WarningSound();
}

void RockCrashRule()
{
	nGameMode = GAMEMODE_MENU;

	// Show the score dialog
	DialogBox(hCurrentInstance, MAKEINTRESOURCE(IDD_CRASHDIALOG), hGamewindowWnd, (DLGPROC)CrashdialogProc);

	// Show the main dialog
	DialogBox(hCurrentInstance, MAKEINTRESOURCE(IDD_MAINDIALOG), hGamewindowWnd, (DLGPROC)MaindialogProc);
}
