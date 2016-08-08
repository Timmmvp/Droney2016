// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently

// Include often but read only once
#pragma once

// Windows specific includes
//#define _WIN32_WINNT ?				// Init to the older platform you wish to support (only if needed)
#include <SDKDDKVer.h>					// Defines the highest available Windows platform
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// Defines
#define GAMEAREA_NAME					"gamearea1.txt"
#define GAMEAREA_BLOCKSIZE				16
#define GAMEAREA_GRASS					' '
#define GAMEAREA_STONE					'X'
#define GAMEAREA_HOME					'H'
#define GAMEAREA_DROP0					'@'
#define GAMEAREA_DROP1					'$'
#define GAMEAREA_WATER					'~'
#define GAMEAREA_TREES					'*'
#define GAMEMODE_MENU					0
#define GAMEMODE_GAME					1
#define GAMEMODE_PAUZE					2

// Types
struct LOCATION
{
	UINT16 x;
	UINT16 y;
};

// Global variables
extern HINSTANCE hCurrentInstance;		// current instance
extern HWND hGamewindowWnd;				// the gamewindow
extern BYTE* pGamearea;					// the gamearea
extern UINT16 nGameareaW, nGameareaH;	// gamearea width and height
extern LOCATION oDroneLoc;				// current drone location on the map
extern LOCATION oHomeLoc;				// homebase location on the map
extern UINT16 nTargetCount;				// number of targets in the area
extern UINT16 nTargetsFound;			// number of targets found
extern LOCATION* pTargetLoc;			// target locations
extern BYTE nGameMode;					// modi of the game: 0 = maindialog, 1 = game, 2 = pauze
extern UINT16 nGameTimer;				// running timer

/**
* Update the targetcount
*/
void SetTargetCount();

/**
* Update the gamewindow
*/
void UpdateGamewindow();
