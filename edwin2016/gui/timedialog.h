/**
* The time dialog
*/

// Include often but read only once
#pragma once

// Defines

// Global variables

// Include all the gui parts
#include "..\resource\resource.h"

/**
* Message handler for the Crash dialog
* @param hDlg					Dialog identifier
* @param nMessage				Message identifier
* @param wParam				Word-type parameter
* @param lParam				Long-type parameter
* @return						The message (subtree) processed the message
*/
INT_PTR CALLBACK TimedialogProc(HWND hDlg, UINT nMessage, WPARAM wParam, LPARAM lParam);
