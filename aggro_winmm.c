// Sometimes, a directsoundcreate call will pull winmm from system32
// which breaks a lot of cdda wrappers that rely on local winmm being used.
// this will just load our local copy in memory before anyone else can.

#include <Windows.h>

__declspec(dllexport) void dropkick(){}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    HMODULE hWinmm;
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        // Unload if it's already loaded...
        if(GetModuleHandleA("winmm.dll")){
            FreeLibrary(GetModuleHandleA("winmm.dll"));
        }        
        LoadLibraryA("./winmm.dll");
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}