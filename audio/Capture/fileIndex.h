#ifndef _INDEX_
#define _INDEX_
/*
global file
*/
#include <cwchar>
#include <vector>
#include <dshow.h>
#include <windows.h>

#pragma comment (lib, "strmiids.lib")
#define NOTEMPTYRET(Clazz)	if(NULL==Clazz) return hr;
#define NOTEMPTYNRET(Clazz)	if(NULL==Clazz) return;
typedef HRESULT (__stdcall *DLLREG)();

//{3C78B8E2-6C4D-11d1-ADE2-0000F8754B99}
static const GUID CLSID_WavDest =
{ 0x3c78b8e2, 0x6c4d, 0x11d1, { 0xad, 0xe2, 0x0, 0x0, 0xf8, 0x75, 0x4b, 0x99 } };

#endif