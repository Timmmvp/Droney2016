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











