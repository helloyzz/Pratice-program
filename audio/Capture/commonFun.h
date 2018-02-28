#ifndef _COMMON_FUN_
#define _COMMON_FUN_

#include "fileIndex.h"

static inline void initCom() {
	HWND hwnd = NULL;
	LPCTSTR text = L"INITIALIZE ERROR";
	LPCTSTR caption = L"PROMPT";
	HRESULT hr = CoInitialize(NULL);
	if(S_OK!=hr) {
		MessageBox(hwnd, text, caption, MB_OK);
	}
}
static inline void releaseCom() {
	CoUninitialize();
}
//safe release filter
template<class Clazz>
static inline void safeRelease(Clazz** p) {
	if(*p) {
		(*p)->Release();
		(*p)=NULL;
	}
}
//create an instance
template<typename TYPE>
static inline HRESULT createInstance(CLSID clsid, LPUNKNOWN pUnkOuter, DWORD context, TYPE** pType) {
	HRESULT hr = -1;
	hr = CoCreateInstance(clsid, pUnkOuter, context, IID_PPV_ARGS(pType));
	if(S_OK==hr) (*pType)->AddRef();
	return hr;
}
//create Moniker enumerate
static inline HRESULT createMonEnum(const GUID category, IEnumMoniker** ppE) {
	HRESULT hr = -1;
	ICreateDevEnum* pDevEnum = NULL;
	IEnumMoniker* pEnumMoniker = NULL;

	hr = createInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER, &pDevEnum);
	if(S_OK==hr) {
		hr = pDevEnum->CreateClassEnumerator(category, &pEnumMoniker, 0);
		if(S_OK==hr) {
			(*ppE) = pEnumMoniker;
			(*ppE)->AddRef();
			safeRelease(&pEnumMoniker);
		}
		safeRelease(&pDevEnum);
	}
	return hr;
}
//binding the last moniker
static inline HRESULT bindEndMoniker(IEnumMoniker* pEnumMoniker, IMoniker** ppM) {
	HRESULT hr = -1;
	IMoniker* pMoniker = NULL;
	ULONG pFetched;

	NOTEMPTYRET(pEnumMoniker);
	while(S_OK==pEnumMoniker->Next(1, &pMoniker, &pFetched)) {
		(*ppM) = pMoniker;
		safeRelease(&pMoniker);
	}
	if((*ppM)!=NULL) {
		hr = S_OK;
		(*ppM)->AddRef();
	}
	return hr;
}
//binding the first moniker
static inline HRESULT bindStartMoniker(IEnumMoniker* pEnumMoniker, IMoniker** ppM) {
	HRESULT hr = -1;
	IMoniker* pMoniker = NULL;
	ULONG pFetched;

	NOTEMPTYRET(pEnumMoniker);
	if(S_OK==(hr=pEnumMoniker->Next(1, &pMoniker, &pFetched))) {
		(*ppM) = pMoniker;
		(*ppM)->AddRef();
		safeRelease(&pMoniker);
	}
	return hr;
}
//get moniker name
static inline HRESULT getMonikerName(IMoniker* pMoniker, BSTR* pName) {
	HRESULT hr = -1;
	IPropertyBag* pProp = NULL;

	NOTEMPTYRET(pMoniker);
	hr = pMoniker->BindToStorage(NULL, NULL, IID_IPropertyBag, (void**)&pProp);
	if(S_OK==hr) {
		VARIANT varName;
		VariantInit(&varName);
		hr = pProp->Read(L"FriendlyName", &varName, 0);
		if(S_OK==hr) {
			(*pName)=varName.bstrVal;
		}
		VariantClear(&varName);
		safeRelease(&pProp);
	}
	return hr;
}

#endif