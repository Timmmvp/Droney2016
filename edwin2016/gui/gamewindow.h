/**
 * The gamewindow
 */

// Include often but read only once
#pragma once

// Defines
#define IDT_GAMETIMER			1

// Global variables

// Include all the gui parts
#include "..\resource\resource.h"
#include "maindialog.h"
#include "scoredialog.h"

/**
 * Register the gamewindow class
 * @param hInstance				The identifier of this process
 * @return						Implies the reistration was OK
 */
ATOM RegisterGamewindowClass(HINSTANCE hInstance);

/**
 * Create and show the gamewindow
 * @param hInstance				The identifier of this process
 * @param nCmdShow				The show-modus to be used for the gamewindow
 * @return						Implies the creation went successful
 */
BOOL InitGamewindowInstance(HINSTANCE hInstance, int nCmdShow);

/**
 * Message handler for the gamewindow
 * @param hWnd					Window identifier
 * @param nMessage				Message identifier
 * @param wParam				Word-type parameter
 * @param lParam				Long-type parameter
 * @return						The message (subtree) processed the message
 */
LRESULT CALLBACK GamewindowProc(HWND hWnd, UINT nMessage, WPARAM wParam, LPARAM lParam);

/**
* Check allowed move
* @param x						The new location x
* @param y						The new location y
* @return						Implies the move is allowed
*/
BOOL CheckMove(UINT16 x, UINT16 y);

/**
 * Apply the sign on the current drone location
 */
void ApplyLocation();

