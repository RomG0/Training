#pragma once

#include <stdio.h>
#include <string.h>
#include <Windows.h>

VOID XorCipher(LPWSTR inData, LPWSTR inKey);

VOID CreateRegKeyAndValue(HKEY inHiveKey, LPCWSTR inSubKey);

VOID PrintDecryptedPCName(HKEY inHiveKey, LPCWSTR inSubKey);