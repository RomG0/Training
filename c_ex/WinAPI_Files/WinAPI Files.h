#pragma once

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <Windows.h>


VOID WriteToFile(HANDLE hFile);

BOOL CheckFileExists(LPCWSTR szPath);

BOOL CheckForbiddenPath(LPWSTR szPath);

VOID CreateSubdirectories(LPCWSTR szPath);

BOOL CheckForbiddenFileType(LPWSTR szPath);

VOID PrintFile(HANDLE hFile, DWORD dwCharCount);