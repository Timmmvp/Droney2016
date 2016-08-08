/**
 *	Game helper methods
 */

#include "gamelib.h"

// Global variables

// Local variables

/**
 * Load the game area
 * @param nError				The return errorcode (0 = none)
 * @param sName					Name of the gamefile
 * @param nWidth				Return the width
 * @param nHeight				Return the height
 * @return						NULL if error, otherwise pointer to the gamedata[][]
 */
BYTE* GameLoadArea(BYTE& nError, const char* sName, UINT16& nWidth, UINT16& nHeight)
{
	BYTE* pFiledata = NULL;
	BYTE nByte;
	FILE* pFile;
	UINT16 nFileSize, nPos, nLine;

	// No error found yet
	nError = 0;

	// Determine the file length
	if (fopen_s(&pFile, sName, "r") != 0)
	{
		nError = 1;
		return NULL;
	};
	fseek(pFile, 0L, SEEK_END);
	nFileSize = (UINT16)ftell(pFile);

	// Init the filedata memory
	pFiledata = (BYTE*)malloc(nFileSize);
	rewind(pFile);

	// Start reading the file (and strip non textual ascii en check line lengths)
	nWidth = 0;
	nHeight = 0;
	nPos = 0;
	fread(&nByte, sizeof(BYTE), 1, pFile);

	while (nPos < nFileSize)
	{
		// Read a line
		nLine = 0;
		while (nPos + nLine < nFileSize && nByte >= 32)
		{
			pFiledata[nPos + nLine] = nByte;
			nLine++;

			fread(&nByte, sizeof(BYTE), 1, pFile);
		};

		// Just read the first line?
		if (nWidth == 0)
		{
			nWidth = nLine;
		}
		else
		// Check line length
		{
			if (nLine != nWidth)
			{
				free(pFiledata);
				pFiledata = NULL;
				nError = 2;
				return NULL;
			};
		};

		// Line has been read
		nPos += nLine;

		// Skip non textual ascii
		while (nPos < nFileSize && nByte < 32)
		{
			nPos++;

			fread(&nByte, sizeof(BYTE), 1, pFile);
		};

		// One line processed
		nHeight++;
	};

	// Close the file
	fclose(pFile);

	// Update width
	nWidth++;

	return pFiledata;
};
