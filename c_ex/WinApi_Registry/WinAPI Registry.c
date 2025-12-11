#include <stdio.h>
#include <string.h>
#include <Windows.h>

//VOID EnumerateRegistryValues(HKEY hKeyParent, LPCWSTR subKeyPath) {
//    HKEY hKey;
//    if (RegOpenKeyExW(hKeyParent, subKeyPath, 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
//        DWORD dwMaxValueNameLen;
//        DWORD dwMaxValueDataLen;
//        // Get key information to determine buffer sizes
//        if (RegQueryInfoKeyW(hKey, NULL, NULL, NULL, NULL, NULL, NULL,
//            NULL, &dwMaxValueNameLen, &dwMaxValueDataLen,
//            NULL, NULL) == ERROR_SUCCESS) {
//
//            // Adjust for null terminators
//            dwMaxValueNameLen++;
//            dwMaxValueDataLen++;
//
//            LPWSTR lpValueName;
//            LPWSTR lpValueData;
//
//
//            if (RegEnumValueW(hKey, 1, &lpValueName, dwMaxValueNameLen,
//                NULL, NULL, &lpValueData, dwMaxValueDataLen) == ERROR_SUCCESS) {
//                printf("%s", lpValueName);
//            }
//        }
//    }
//    RegCloseKey(hKey);
//}

//VOID GetSecondRegistryValue(HKEY hKeyParent, LPCSTR subKeyPath) {
//    HKEY hKey;
//    if (RegOpenKeyExW(HKEY_CURRENT_USER, subKeyPath, 0, KEY_READ, &hKey) != ERROR_SUCCESS)
//        return;
//
//    DWORD maxNameLen = 0, maxDataLen = 0;
//    if (RegQueryInfoKeyW(hKey, NULL, NULL, NULL, NULL, NULL, NULL,
//        NULL, &maxNameLen, &maxDataLen, NULL, NULL) != ERROR_SUCCESS) {
//        RegCloseKey(hKey);
//        return;
//    }
//
//    maxNameLen++;           // for null
//    LPWSTR nameBuf = (LPWSTR)LocalAlloc(LPTR, maxNameLen * sizeof(WCHAR));
//    LPBYTE dataBuf = (LPBYTE)LocalAlloc(LPTR, maxDataLen);
//    if (!nameBuf || !dataBuf) {
//        if (nameBuf) LocalFree(nameBuf);
//        if (dataBuf) LocalFree(dataBuf);
//        RegCloseKey(hKey);
//        return;
//    }
//
//    DWORD nameLen = maxNameLen;
//    DWORD dataLen = maxDataLen;
//    DWORD type;
//
//    // index 1 == “second value”
//    if (RegEnumValueW(hKey, 1, nameBuf, &nameLen,
//        NULL, &type, dataBuf, &dataLen) == ERROR_SUCCESS) {
//        wprintf(L"%s\n", nameBuf);
//    }
//
//    LocalFree(nameBuf);
//    LocalFree(dataBuf);
//    RegCloseKey(hKey);
//}
INT main(VOID) {

    HKEY hHiveKey = HKEY_CURRENT_USER;
    LPCWSTR lpwcSubKey = L"WinAPI Registry";
    HKEY hkey;

    if (RegOpenKeyExW(hHiveKey, lpwcSubKey, 0, KEY_READ, &hkey) == ERROR_SUCCESS) {

        DWORD dwMaxValueNameLen;
        DWORD dwMaxValueDataLen;
        // Get key information to determine buffer sizes
        if (RegQueryInfoKeyW(hkey, NULL, NULL, NULL, NULL, NULL, NULL,
            NULL, &dwMaxValueNameLen, &dwMaxValueDataLen,
            NULL, NULL) == ERROR_SUCCESS) {

            // Adjust for null terminators
            dwMaxValueNameLen++;
            dwMaxValueDataLen++;


            LPWSTR nameBuf = (LPWSTR)malloc( dwMaxValueNameLen * sizeof(WCHAR));
            LPWSTR dataBuf = (LPWSTR)malloc( dwMaxValueDataLen * sizeof(WCHAR));


                if (RegEnumValueW(hkey, 0, nameBuf, &dwMaxValueNameLen,
                NULL, NULL, dataBuf, &dwMaxValueDataLen) == ERROR_SUCCESS) {
                wprintf(L"%s", nameBuf);
                wprintf(L"%Ts", dataBuf);
            }
        }
        RegCloseKey(hkey);
    }

    else {
        printf("bad");
    }
    //GetSecondRegistryValue(HKEY_CURRENT_USER, lpcSubKey);
	return 0;
}