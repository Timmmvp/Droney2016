/**
 *	Game helper methods
 */

// Include often but read only once
#pragma once

// Defines

// Global variables

// Includes
#include <windows.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>

/**
 * Load the game area
 * @param nError				The return errorcode (0 = none)
 * @param sName					Name of the gamefile
 * @param nWidth				Return the width
 * @param nHeight				Return the height
 * @return						NULL if error, otherwise pointer to the gamedata[][]
 */
BYTE* GameLoadArea(BYTE& nError, const char* sName, UINT16& nWidth, UINT16& nHeight);
