#include <windows.h>
#include <stdio.h>

VOID HandleError(DWORD indwError) {
    
    LPWSTR lpsMessage;

    FormatMessageW(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        indwError,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPWSTR)&lpsMessage,
        0,
        NULL
    );
    MessageBoxW(
        NULL, 
        lpsMessage, 
        L"Error", 
        MB_OK | 
        MB_ICONERROR
    );
}

VOID OpenCalc() {

    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    CONST WCHAR csCALC_PATH[] = L"C:\\Windows\\System32\\calc.exe";

    si.cb = sizeof(si);

    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));
    
    if (CreateProcessW(
        NULL,
        csCALC_PATH,
        NULL,
        NULL,
        TRUE,
        0,
        NULL,
        NULL,
        &si,
        &pi
    )) {

        WaitForSingleObject(pi.hProcess, INFINITE);

        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    else {
        HandleError(GetLastError());
    }
}

VOID CreateREADME() {
    LPCWSTR lpsFileName;

    lpsFileName = L"README.txt";

    HANDLE lala= CreateFile(
        lpsFileName,
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        CREATE_NEW,
        FILE_ATTRIBUTE_TEMPORARY,
        NULL
    );
    if (lala == INVALID_HANDLE_VALUE) {
        HandleError(GetLastError());
    }
}

INT WINAPI wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ INT nCmdShow
){
    BOOL bFKeyHeldDown;

    bFKeyHeldDown = 0;

    while (TRUE){
        if (GetAsyncKeyState(VK_ESCAPE)) {
            break;
        }
        if (GetAsyncKeyState(0x4D)) {
            if (!MessageBoxW(
                NULL, 
                L"Hello!", 
                L"basic_WinAPI", 
                MB_OK
            )) {
                HandleError(GetLastError());
            }
        }
        if (GetAsyncKeyState(0x43)) {
            OpenCalc();
        }
        if ((GetAsyncKeyState(0x46) & 0x8000) && (bFKeyHeldDown == 0)) {
            bFKeyHeldDown = 1;
            CreateREADME();
        }
        else if (GetAsyncKeyState(0x46) == 0) {
            bFKeyHeldDown = 0;
        }
    }
    return 0;
}