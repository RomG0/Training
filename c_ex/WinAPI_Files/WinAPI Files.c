#include "WinAPI Files.h"


BOOL CheckFileExists(LPCWSTR szPath) {
	if (GetFileAttributesW(szPath) == INVALID_FILE_ATTRIBUTES) { return FALSE; }
	return TRUE;
}

VOID CreateSubdirectories(LPCWSTR szPath) {

	WCHAR szFolder[MAX_PATH];
	LPWSTR szEnd;
	ZeroMemory(szFolder, MAX_PATH * sizeof(WCHAR));

	szEnd = wcschr(szPath, L'\\');

	while (szEnd != NULL)
	{
		wcsncpy_s(szFolder, MAX_PATH, szPath, szEnd - szPath + 1);
		if (!CreateDirectoryW(szFolder, NULL))
		{
			DWORD err = GetLastError();

			if (err != ERROR_ALREADY_EXISTS)
			{
				printf("\nInvalid Subdirectory Path");
			}
		}
		szEnd = wcschr(++szEnd, L'\\');
	}
}

VOID WriteToFile(HANDLE hFile) {
	DWORD dwBytesWritten;
	WCHAR wcInput;
	WCHAR dwActualCharCounter;
	dwActualCharCounter = 0;
	printf("\nInputing to File, terminate by inputing EOF");
	wcInput = _getwch();
	while (wcInput != L'\x1a') {
		//printf("%lc", wcInput);

		/*BOOL success = */WriteFile(hFile, &wcInput, sizeof(wcInput), &dwBytesWritten, NULL);

		// DEBUGGING STUFF
		// 
		//if (!success || byteswritten != sizeof(wcInput)) {
		//	printf("\nWrite failed: %u bytes", byteswritten);
		//	DWORD errorCode = GetLastError();
		//	printf("\nError code: %u", errorCode);
		//	return;
		//}
		dwActualCharCounter++;
		wcInput = _getwch();
	}

	PrintFile(hFile, dwActualCharCounter);
}

BOOL CheckForbiddenPath(LPWSTR szPath) {
	LPCWSTR cszForbiddenPath = L"C:\\Exercise1_not_here\\hi\\";
	SIZE_T ForbiddenPathLen;
	ForbiddenPathLen = wcslen(cszForbiddenPath);
	if (wcsncmp(szPath,cszForbiddenPath ,ForbiddenPathLen) == 0) {
		return 1;
	}
	return 0;
}

BOOL CheckForbiddenFileType(LPWSTR szPath) {
	LPCWSTR cszForbiddenFileType = L".exe";
	SIZE_T ForbiddenTypeLen;
	SIZE_T PathLen;
	PathLen = wcslen(szPath);
	ForbiddenTypeLen = wcslen(cszForbiddenFileType);
	if (wcsncmp(szPath + PathLen - 4, L".exe", ForbiddenTypeLen) == 0) {
		return 1;
	}
	return 0;
}

VOID PrintFile(HANDLE hFile, DWORD dwCharCount) {

	BOOL bSuccess;
	DWORD dwErrorCode;
	DWORD dwBytesRead;
	LPWSTR szBuffer = (LPWSTR)malloc((dwCharCount + 1) * sizeof(WCHAR));

	SetFilePointer(hFile, 0, NULL, FILE_BEGIN);

	bSuccess = ReadFile(hFile, szBuffer, (dwCharCount + 1) * sizeof(WCHAR), &dwBytesRead, NULL);
	if (!bSuccess) {
		dwErrorCode = GetLastError();
		printf("\nError code: %u", dwErrorCode);
	}
	szBuffer[dwCharCount] = NULL;
	printf("\nYou wrote:");
	wprintf(L"\n%ls", szBuffer);
	CloseHandle(hFile);
	free(szBuffer);
}

INT main()
{
	HANDLE hFile;
	WCHAR szPath[MAX_PATH];
	SIZE_T sizeLen;
	CHAR cChoise;

	while (TRUE) {

		printf("\nInput path to file (to quit out of the program input EXIT): ");
		fgetws(szPath, sizeof(szPath) / 2, stdin);
		sizeLen = wcslen(szPath);
		if (sizeLen > 0 && szPath[sizeLen - 1] == '\n') {
			szPath[sizeLen - 1] = NULL;
		}

		//LPCWSTR szPath = L"C:\\Users\\user\\Desktop\\rom-temp\\test1.txt";

		if (wcscmp(szPath, L"EXIT") == 0) { return 0; }

		if (CheckForbiddenPath(szPath)) {
			printf("\nForbidden File Path");
			continue;
		}

		if (CheckForbiddenFileType(szPath)) {
			printf("\nForbidden File Type");
			continue;
		}


		if (CheckFileExists(szPath)) {
			printf("\nFile exists. Would you like to overwrite it? (Enter Y if yes, otherwise enter any other key) ");
			cChoise = _getche();
			if (cChoise == 'Y') {
				printf("\nOverwriting...");
				DeleteFileW(szPath);
				hFile = CreateFileW(szPath, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
				WriteToFile(hFile);
			}
		}
		else {
			CreateSubdirectories(szPath);
			hFile = CreateFileW(szPath, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			if (hFile == INVALID_HANDLE_VALUE) { printf("\nInvalid file Path"); }
			printf("\nCreating file");
			WriteToFile(hFile);
		}


	}
	return 0;
}