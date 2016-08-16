#include "stdafx.h"
#include "drony2016.h"
#include "gamewindow.h"
#include "crashdialog.h"
#include "maindialog.h"
#include "timedialog.h"

#define DELAY		15
#define BONUS		10

void ResetRule()
{
	ResetTargetPoints();
	ResetEnergyPoints();
}

void WarningSound()
{
	Beep(750, 50);
}

void ScoreSound()
{
	Beep(1500, 50);
}

void CrashSound()
{
	Beep(400, 50);
}

void MarkTargetFoundRule()
{
	nTargetsFound++;
	pGamearea[FROM_2D_TO_1D(oDroneLoc.x, oDroneLoc.y)] = GAMEAREA_DROP1;
	ScoreSound();
}

void DroneAtHomeRule()
{
	Beep(2000, 50);
	Beep(1500, 50);
	Beep(2000, 50);
	nGameMode = GAMEMODE_MENU;
	
	// Show the score dialog
	DialogBox(hCurrentInstance, MAKEINTRESOURCE(IDD_SCOREDIALOG), hGamewindowWnd, (DLGPROC)ScoredialogProc);
	SetHighscore();
	// Show the main dialog
	DialogBox(hCurrentInstance, MAKEINTRESOURCE(IDD_MAINDIALOG), hGamewindowWnd, (DLGPROC)MaindialogProc);
}

void OutOfTimeRule()
{
	// Show the score dialog
	DialogBox(hCurrentInstance, MAKEINTRESOURCE(IDD_TIMEDIALOG), hGamewindowWnd, (DLGPROC)TimedialogProc);
	SetHighscore();
	// Show the main dialog
	DialogBox(hCurrentInstance, MAKEINTRESOURCE(IDD_MAINDIALOG), hGamewindowWnd, (DLGPROC)MaindialogProc);
}

void DelayOnTreeHitRule()
{
	if (nGameTimer <= DELAY)
	{
		OutOfTimeRule();

	}
	nGameTimer -= DELAY;
	WarningSound();
}

void RockCrashRule()
{
	CrashSound();
	nGameMode = GAMEMODE_MENU;

	// Show the score dialog
	DialogBox(hCurrentInstance, MAKEINTRESOURCE(IDD_CRASHDIALOG), hGamewindowWnd, (DLGPROC)CrashdialogProc);

	// Show the main dialog
	DialogBox(hCurrentInstance, MAKEINTRESOURCE(IDD_MAINDIALOG), hGamewindowWnd, (DLGPROC)MaindialogProc);
}

void EnergyTargetRule()
{
	nGameTimer += BONUS;
	Beep(2000, 50);
	pGamearea[FROM_2D_TO_1D(oDroneLoc.x, oDroneLoc.y)] = GAMEAREA_GRASS;
}

