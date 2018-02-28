#include "audioManage.h"

audioManage::audioManage() {}
audioManage::~audioManage() {}

//add a filter by Default of device category
HRESULT audioManage::addCategoryByDefault(const GUID category, IFilterGraph* pGraph, IBaseFilter** pBaseFilter) {
	HRESULT hr = -1;
	IEnumMoniker* pEnumMoniker = NULL;
	IMoniker* pMoniker = NULL;

	NOTEMPTYRET(pGraph);
	hr = createMonEnum(category, &pEnumMoniker);
	if(S_OK==hr) {
		hr = bindEndMoniker(pEnumMoniker, &pMoniker);
		if(S_OK==hr) {
			hr = pMoniker->BindToObject(NULL, NULL, IID_IBaseFilter, (void**)pBaseFilter);
			if(S_OK==hr) {	
				hr = pGraph->AddFilter(*pBaseFilter, NULL);
				(*pBaseFilter)->AddRef();
			}
			safeRelease(&pMoniker);
		}
		safeRelease(&pEnumMoniker);
	}
	return hr;
}
//add a filter by Name of device category
HRESULT audioManage::addCategoryByName(const GUID category, IFilterGraph* pGraph, 
									  IBaseFilter** pBaseFilter, const BSTR mName) {
	HRESULT hr = -1;
	IEnumMoniker* pEnumMoniker = NULL;
	IMoniker* pMoniker = NULL;
	size_t mLen = wcslen((wchar_t*)mName);
	size_t pLen = 0;

	NOTEMPTYRET(pGraph);
	if(S_OK==createMonEnum(category, &pEnumMoniker)) {
		while(S_OK==bindStartMoniker(pEnumMoniker, &pMoniker)) {
		  BSTR pName = NULL;
		  if(S_OK==getMonikerName(pMoniker, &pName)) {
			  pLen = wcslen((wchar_t*)pName);
			  if(mLen==pLen && !wmemcmp(mName, pName, mLen)) {
				  if(S_OK==pMoniker->BindToObject(NULL, NULL, IID_IBaseFilter, (void**)pBaseFilter)) {
					  if(S_OK==pGraph->AddFilter(*pBaseFilter, NULL)) {
						  (*pBaseFilter)->AddRef();
						  hr = S_OK;
						  break;
					  }
				  }
			  }
		  }
		  safeRelease(&pMoniker);
		}
	}
	safeRelease(&pEnumMoniker);
	return hr;
}
//add a filter by CLSID to graph
HRESULT audioManage::addFilterByCLSID(IFilterGraph* pGraph, CLSID clsid, IBaseFilter** ppF, LPCWSTR wasName) {
	HRESULT hr = -1;
	*ppF = NULL;
	IBaseFilter* pFilter = NULL;

	NOTEMPTYRET(pGraph);
	hr = createInstance(clsid, NULL, CLSCTX_INPROC_SERVER, &pFilter);
	if(S_OK==hr) {
		hr = pGraph->AddFilter(pFilter, wasName);
		if(S_OK==hr) {
			*ppF = pFilter;
			(*ppF)->AddRef();
		}
	}
	safeRelease(&pFilter);
	return hr;
}
//create a filter by Default of device category
HRESULT audioManage::createCategoryByDefault(const GUID category, IBaseFilter** pBaseFilter) {
	HRESULT hr = -1;
	IEnumMoniker* pEnumMoniker = NULL;
	IMoniker* pMoniker = NULL;

	hr = createMonEnum(category, &pEnumMoniker);
	if(S_OK==hr) {
		hr = bindEndMoniker(pEnumMoniker, &pMoniker);
		if(S_OK==hr) {
			hr = pMoniker->BindToObject(NULL, NULL, IID_IBaseFilter, (void**)pBaseFilter);
			safeRelease(&pMoniker);
		}
		safeRelease(&pEnumMoniker);
	}
	return hr;
}
//create a filter by Name of device category
HRESULT audioManage::createCategoryByName(const GUID category, IBaseFilter** pBaseFilter, const BSTR mName) {
	HRESULT hr = -1;
	IEnumMoniker* pEnumMoniker = NULL;
	IMoniker* pMoniker = NULL;
	size_t mLen = wcslen((wchar_t*)mName);
	size_t pLen = 0;

	if(S_OK==createMonEnum(category, &pEnumMoniker)) {
		while(S_OK==bindStartMoniker(pEnumMoniker, &pMoniker)) {
			BSTR pName = NULL;
			if(S_OK==getMonikerName(pMoniker, &pName)) {
				pLen = wcslen((wchar_t*)pName);
				if(mLen==pLen && !wmemcmp(mName, pName, mLen)) {
					if(S_OK==pMoniker->BindToObject(NULL, NULL, IID_IBaseFilter, (void**)pBaseFilter)) {
						hr = S_OK;
						break;
					}
				}
			}
			safeRelease(&pMoniker);
		}
	}
	safeRelease(&pEnumMoniker);
	return hr;
}
//create and return a filter
HRESULT audioManage::createFilterByCLSID(const CLSID clsid, IBaseFilter** ppF) {
	HRESULT hr = -1;
	IBaseFilter* pFilter = NULL;
	*ppF = NULL;

	hr = createInstance(clsid, NULL, CLSCTX_INPROC_SERVER, &pFilter);
	if(S_OK==hr) {
		(*ppF) = pFilter;
		(*ppF)->AddRef();
	}
	safeRelease(&pFilter);
	return hr;
}
//get a pins
HRESULT audioManage::getPin(IBaseFilter* pFilter, const PIN_DIRECTION pinDir, IPin** pInt) {
	HRESULT hr = -1;
	IEnumPins* pEnum = NULL;
	IPin* pPin = NULL;
	ULONG pFetched;

	NOTEMPTYRET(pFilter);
	if(S_OK==pFilter->EnumPins(&pEnum)) {
		while(S_OK==pEnum->Next(1, &pPin, &pFetched)) {
			PIN_DIRECTION pinDirect;
			if(S_OK==(pPin->QueryDirection(&pinDirect)) && pinDirect==pinDir) {
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
HRESULT audioManage::connectFilters(IGraphBuilder* pGraph, IBaseFilter* pSrc, IBaseFilter* pDest) {
	HRESULT hr = -1;
	IPin* pIn = NULL;
	IPin* pOut = NULL;

	NOTEMPTYRET(pGraph);
	hr = getPin(pSrc, PINDIR_OUTPUT, &pOut);
	if(S_OK==hr) {
		hr = getPin(pDest, PINDIR_INPUT, &pIn);
		if(S_OK==hr) {
			hr = findUnconnectPin(pIn);
			if(S_OK==hr) {
				hr = pGraph->Connect(pOut, pIn);
			}
			safeRelease(&pIn);
		}
		safeRelease(&pOut);
	}
	return hr;
}
//find a unconnected pin
BOOL audioManage::findUnconnectPin(IPin* pPin) {
	HRESULT hr = -1;
	IPin* pTem = NULL;

	NOTEMPTYRET(pPin);
	if(S_OK!=(hr=pPin->ConnectedTo(&pTem))) {
		hr = S_OK;
	}
	safeRelease(&pTem);
	return hr;
}
//dynamic load file
template<typename TYPE>
BOOL audioManage::dynamicLoad(HINSTANCE* hinstLib, const LPCWSTR dllName, const LPCSTR funName, TYPE* procAdd) {
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
HRESULT audioManage::registerWavFilter() {
	HRESULT hr = -1;
	HINSTANCE hinstLib = NULL;
	LPCWSTR dllName = L"WavDest.dll";
	LPCSTR funName = "DllRegisterServer";
	DLLREG procAdd = NULL;

	if(dynamicLoad(&hinstLib, dllName, funName, &procAdd)) {
		hr = (procAdd)();
		FreeLibrary(hinstLib);
	}
	return hr;
}
//unregister a filter
HRESULT audioManage::unRegisterWavFilter() {
	HRESULT hr = -1;
	HINSTANCE hinstLib = NULL;
	LPCWSTR dllName = L"WavDest.dll";
	LPCSTR funName = "DllUnregisterServer";
	DLLREG procAdd = NULL;

	if(dynamicLoad(&hinstLib, dllName, funName, &procAdd)) {
		hr = (procAdd)();
		FreeLibrary(hinstLib);
	}
	return hr;
}

//enumerate pins
void audioManage::enumPins(IBaseFilter* pFilter) {
	IEnumPins* pEnum = NULL;
	IPin* pPin = NULL;
	ULONG pFetched;

	NOTEMPTYNRET(pFilter);
	if(S_OK==pFilter->EnumPins(&pEnum)) {
		while(S_OK==pEnum->Next(1, &pPin, &pFetched)) {
			PIN_INFO pinInfo;
			if(S_OK==pPin->QueryPinInfo(&pinInfo)) {}
			safeRelease(&pPin);
		}
	}
	safeRelease(&pEnum);
}
//enumerate filters
void audioManage::enumFilters(IFilterGraph* pGraph) {
	IEnumFilters* pEnum = NULL;
	IBaseFilter* pFilter = NULL;
	ULONG pFetched;

	NOTEMPTYNRET(pGraph);
	if(S_OK==pGraph->EnumFilters(&pEnum)) {
		while(S_OK==pEnum->Next(1, &pFilter, &pFetched))
		{
			FILTER_INFO filterInfo;
			if (S_OK==pFilter->QueryFilterInfo(&filterInfo)) {}
			safeRelease(&pFilter);
		}
	}
	safeRelease(&pEnum);
}