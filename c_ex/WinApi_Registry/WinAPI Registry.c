#include "WinAPI Registry.h"

VOID XorCipher(LPWSTR inData, LPWSTR inKey) {
    SIZE_T ulDataLen = wcslen(inData);
    SIZE_T ulKeyLen = wcslen(inKey);

    for (SIZE_T i = 0; i < ulDataLen; i++) {
        inData[i] = inData[i] ^ inKey[i % ulKeyLen];

    }
}

VOID CreateRegKeyAndValue(HKEY inHiveKey, LPCWSTR inSubKey) { 
    HKEY hKey;
    WCHAR lpwPCName[MAX_COMPUTERNAME_LENGTH + 1];

    LPCWSTR lpcwValueName = L"LALALA";
    DWORD length = MAX_COMPUTERNAME_LENGTH + 1;

    GetComputerNameExW(ComputerNameDnsHostname, lpwPCName, &length);

    XorCipher(lpwPCName, lpcwValueName);

    DWORD datasizebytes = ((DWORD)wcslen(lpwPCName) + 1) * sizeof(WCHAR);
    
    RegCreateKeyExW(inHiveKey, inSubKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_SET_VALUE | KEY_READ, NULL, &hKey, NULL);
    RegSetValueExW(hKey, lpcwValueName, 0, REG_SZ, (const BYTE*)lpwPCName, datasizebytes);
    RegCloseKey(hKey);

    return;
}

VOID PrintDecryptedPCName(HKEY inHiveKey, LPCWSTR inSubKey) {
  
    HKEY hKey;

    DWORD dwMaxValueNameLen;
    DWORD dwMaxValueDataLen;

    LONG lStatus;
    lStatus = RegOpenKeyExW(inHiveKey, inSubKey, 0, KEY_READ, &hKey);
    if (lStatus == ERROR_SUCCESS) {

        if (RegQueryInfoKeyW(hKey, NULL, NULL, NULL, NULL, NULL, NULL,
            NULL, &dwMaxValueNameLen, &dwMaxValueDataLen,
            NULL, NULL) == ERROR_SUCCESS) {

            dwMaxValueNameLen++;
            dwMaxValueDataLen++;

            LPWSTR nameBuf = (LPWSTR)malloc(dwMaxValueNameLen * sizeof(WCHAR));
            LPWSTR dataBuf = (LPWSTR)malloc(dwMaxValueDataLen * sizeof(WCHAR));

            if (RegEnumValueW(hKey, 0, nameBuf, &dwMaxValueNameLen,
                NULL, NULL, dataBuf, &dwMaxValueDataLen) == ERROR_SUCCESS) {

                XorCipher(dataBuf, nameBuf);
                wprintf(L"The decrypted reg value data is: %ls", dataBuf);

            }

            free(nameBuf);         
            free(dataBuf);
        }

        RegCloseKey(hKey); 
        RegDeleteTreeW(inHiveKey, inSubKey);

    }
    else if (lStatus == ERROR_FILE_NOT_FOUND){
        printf("Registry Key not found, creating new key and value");
        CreateRegKeyAndValue(inHiveKey, inSubKey);
    }

}

INT main(VOID) {
    HKEY hHiveKey = HKEY_CURRENT_USER;
    LPCWSTR lpwcSubKey = L"WinAPI Registry";

    PrintDecryptedPCName(hHiveKey, lpwcSubKey);

	return 0;
}