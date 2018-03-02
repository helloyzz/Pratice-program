#include "audioManage.h"

audioManage::audioManage(): pGraph(NULL) {}
audioManage::~audioManage() {
	safeRelease(&pGraph);
}

//add a filter by Name of device category
HRESULT audioManage::addCategoryByName(const GUID category, IBaseFilter** pBaseFilter, const BSTR mName) const {
	HRESULT hr = S_FALSE;
	IEnumMoniker* pEnumMoniker = NULL;
	IMoniker* pMoniker = NULL;
	size_t mLen = wcslen((wchar_t*)mName);
	size_t pLen = 0;
	BSTR pName = NULL;

	if(pGraph && !createMonEnum(category, &pEnumMoniker)) {
		while(!bindStartMoniker(pEnumMoniker, &pMoniker) && !getMonikerName(pMoniker, &pName)) {
			pLen = wcslen((wchar_t*)pName);
			if(mLen==pLen && !wmemcmp(mName, pName, mLen) && 
				!pMoniker->BindToObject(NULL, NULL, IID_IBaseFilter, (void**)pBaseFilter) && 
				!pGraph->AddFilter(*pBaseFilter, NULL)) {
				(*pBaseFilter)->AddRef();
				hr = S_OK;
				break;
			}
			pName = NULL;
			safeRelease(&pMoniker);
		}
	}
	safeRelease(&pEnumMoniker);
	return hr;
}
//add a filter by CLSID to graph
HRESULT audioManage::addFilterByCLSID(CLSID clsid, IBaseFilter** ppF, LPCWSTR wasName) const {
	HRESULT hr = S_FALSE;
	IBaseFilter* pFilter = NULL;

	if(pGraph && !createInstance(clsid, NULL, CLSCTX_INPROC_SERVER, &pFilter) && !pGraph->AddFilter(pFilter, wasName)) {
		*ppF = pFilter;
		(*ppF)->AddRef();
		hr = S_OK;
	}
	safeRelease(&pFilter);
	return hr;
}
//create a filter by Name of device category
HRESULT audioManage::createCategoryByName(const GUID category, IBaseFilter** pBaseFilter, const BSTR mName) const {
	HRESULT hr = S_FALSE;
	IEnumMoniker* pEnumMoniker = NULL;
	IMoniker* pMoniker = NULL;
	size_t mLen = wcslen((wchar_t*)mName);
	size_t pLen = 0;
	BSTR pName = NULL;

	if(!createMonEnum(category, &pEnumMoniker)) {
		while(!bindStartMoniker(pEnumMoniker, &pMoniker) && !getMonikerName(pMoniker, &pName)) {
			pLen = wcslen((wchar_t*)pName);
			if(mLen==pLen && !wmemcmp(mName, pName, mLen) && 
				!pMoniker->BindToObject(NULL, NULL, IID_IBaseFilter, (void**)pBaseFilter)) {
				hr = S_OK;
				break;
			}
			pName = NULL;
			safeRelease(&pMoniker);
		}
	}
	safeRelease(&pEnumMoniker);
	return hr;
}
//create and return a filter
HRESULT audioManage::createFilterByCLSID(const CLSID clsid, IBaseFilter** ppF) const {
	HRESULT hr = S_FALSE;
	IBaseFilter* pFilter = NULL;

	if(!createInstance(clsid, NULL, CLSCTX_INPROC_SERVER, &pFilter)) {
		(*ppF) = pFilter;
		(*ppF)->AddRef();
		hr = S_OK;
	}
	safeRelease(&pFilter);
	return hr;
}
//get a pins
HRESULT audioManage::getPin(IBaseFilter* pFilter, const PIN_DIRECTION pinDir, IPin** pInt) const {
	HRESULT hr = S_FALSE;
	IEnumPins* pEnum = NULL;
	IPin* pPin = NULL;
	ULONG pFetched;
	PIN_DIRECTION pinDirect;

	if(pFilter && !pFilter->EnumPins(&pEnum)) {
		while(!pEnum->Next(1, &pPin, &pFetched)) {
			if(!pPin->QueryDirection(&pinDirect) && pinDirect==pinDir) {
				*pInt = pPin;
				hr = S_OK;
				break;
			}
			safeRelease(&pPin);
		}
	}
	safeRelease(&pEnum);
	return hr;
}
//connect two filters
HRESULT audioManage::connectFilters(IBaseFilter* pSrc, IBaseFilter* pDest) const {
	HRESULT hr = S_FALSE;
	IPin* pIn = NULL;
	IPin* pOut = NULL;

	if(pGraph && !getPin(pSrc, PINDIR_OUTPUT, &pOut)) {
		if(!getPin(pDest, PINDIR_INPUT, &pIn) && !findUnconnectPin(pIn)) {
			hr = pGraph->Connect(pOut, pIn);
		}
	}
	safeRelease(&pIn);
	safeRelease(&pOut);
	return hr;
}
//find a unconnected pin
BOOL audioManage::findUnconnectPin(IPin* pPin) const {
	HRESULT hr = S_FALSE;
	IPin* pTem = NULL;

	if(pPin && pPin->ConnectedTo(&pTem)) {
		hr = S_OK;
	}
	safeRelease(&pTem);
	return hr;
}
//dynamic load file
template<typename TYPE>
BOOL audioManage::dynamicLoad(HINSTANCE* hinstLib, const LPCWSTR dllName, const LPCSTR funName, TYPE* procAdd) const {
	BOOL result = FALSE;

	(*hinstLib) = LoadLibrary(dllName);
	if(NULL!=(*hinstLib)) {
		(*procAdd) = (TYPE)GetProcAddress((*hinstLib), funName);
		if(NULL!=procAdd) {
			result = TRUE;
		}
	}
	return result;
}
//register a filter
HRESULT audioManage::registerWavFilter() const {
	HRESULT hr = S_FALSE;
	HINSTANCE hinstLib = NULL;
	DLLREG procAdd = NULL;

	if(dynamicLoad(&hinstLib, WAVDLLNAME, DLLFUNNAME, &procAdd)) {
		hr = (procAdd)();
		FreeLibrary(hinstLib);
	}
	return hr;
}
//unregister a filter
HRESULT audioManage::unRegisterWavFilter() const {
	HRESULT hr = S_FALSE;
	HINSTANCE hinstLib = NULL;
	DLLREG procAdd = NULL;

	if(dynamicLoad(&hinstLib, WAVDLLNAME, DLLFUNNAME, &procAdd)) {
		hr = (procAdd)();
		FreeLibrary(hinstLib);
	}
	return hr;
}

