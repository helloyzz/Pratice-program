#ifndef _COMMON_FUN_
#define _COMMON_FUN_

#include "baseIndex.h"


static inline void initCom() {
	HWND hwnd = NULL;
	HRESULT hr = CoInitialize(NULL);
	if(S_OK!=hr) {
		MessageBox(hwnd, INITCOMERRORTEXT, INITCOMPROMPT, MB_OK);
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
	HRESULT hr = S_FALSE;

	if(!CoCreateInstance(clsid, pUnkOuter, context, IID_PPV_ARGS(pType))) {
		(*pType)->AddRef();
		hr = S_OK;
	}
	return hr;
}
//create Moniker enumerate
static inline HRESULT createMonEnum(const GUID category, IEnumMoniker** ppE) {
	HRESULT hr = S_FALSE;
	ICreateDevEnum* pDevEnum = NULL;
	IEnumMoniker* pEnumMoniker = NULL;

	if(!createInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER, &pDevEnum)) {
		if(!pDevEnum->CreateClassEnumerator(category, &pEnumMoniker, 0)) {
			(*ppE) = pEnumMoniker;
			(*ppE)->AddRef();
			hr = S_OK;
		}
	}
	safeRelease(&pEnumMoniker);
	safeRelease(&pDevEnum);
	return hr;
}
//binding the last moniker
static inline HRESULT bindEndMoniker(IEnumMoniker* pEnumMoniker, IMoniker** ppM) {
	HRESULT hr = S_FALSE;
	IMoniker* pMoniker = NULL;
	ULONG pFetched;

	while(pEnumMoniker && !pEnumMoniker->Next(1, &pMoniker, &pFetched)) {
		(*ppM) = pMoniker;
		safeRelease(&pMoniker);
	}
	if((*ppM)) {
		(*ppM)->AddRef();
		hr = S_OK;
	}
	return hr;
}
//binding the first moniker
static inline HRESULT bindStartMoniker(IEnumMoniker* pEnumMoniker, IMoniker** ppM) {
	HRESULT hr = S_FALSE;
	IMoniker* pMoniker = NULL;
	ULONG pFetched;

	if(pEnumMoniker && !pEnumMoniker->Next(1, &pMoniker, &pFetched)) {
		(*ppM) = pMoniker;
		(*ppM)->AddRef();
		hr = S_OK;
	}
	safeRelease(&pMoniker);
	return hr;
}
//get moniker name
static inline HRESULT getMonikerName(IMoniker* pMoniker, BSTR* pName) {
	HRESULT hr = S_FALSE;
	IPropertyBag* pProp = NULL;
	VARIANT varName;
	VariantInit(&varName);

	if(pMoniker && !pMoniker->BindToStorage(NULL, NULL, IID_IPropertyBag, (void**)&pProp)) {
		if(!pProp->Read(FRIENDLYNAME, &varName, 0)) {
			(*pName)=varName.bstrVal;
			hr = S_OK;
		}
	}
	VariantClear(&varName);
	safeRelease(&pProp);
	return hr;
}

#endif