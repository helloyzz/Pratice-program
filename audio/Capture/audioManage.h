#ifndef _AUDIO_MANAGE_
#define _AUDIO_MANAGE_

#include "commonFun.h"

class audioManage {
protected:
	audioManage();
	virtual ~audioManage();
	//add a filter by Default of device category
	HRESULT addCategoryByDefault(const GUID category, IFilterGraph* pGraph, IBaseFilter** pBaseFilter);
	//add a filter by Name of device category
	HRESULT addCategoryByName(const GUID category, IFilterGraph* pGraph, 
		IBaseFilter** pBaseFilter, const BSTR mName);
	//add a filter by CLSID to graph
	HRESULT addFilterByCLSID(IFilterGraph* pGraph, CLSID clsid, IBaseFilter** ppF, LPCWSTR wasName);
	//create a filter by Default of device category
	HRESULT createCategoryByDefault(const GUID category, IBaseFilter** pBaseFilter);
	//create a filter by Name of device category
	HRESULT createCategoryByName(const GUID category, IBaseFilter** pBaseFilter, const BSTR mName);
	//create and return a filter
	HRESULT createFilterByCLSID(const CLSID clsid, IBaseFilter** ppF);
	//get a pins
	HRESULT getPin(IBaseFilter* pFilter, const PIN_DIRECTION pinDir, IPin** pInt);
	//connect two filters
	HRESULT connectFilters(IGraphBuilder* pGraph, IBaseFilter* pSrc, IBaseFilter* pDest);
	//find a unconnected pin
	BOOL findUnconnectPin(IPin* pPin);
	//dynamic load
	template<typename TYPE>
	BOOL dynamicLoad(HINSTANCE* hinstLib, const LPCWSTR dllName, const LPCSTR funName, TYPE* procAdd);
	//register a filter
	HRESULT registerWavFilter();
	//unregister a filter
	HRESULT unRegisterWavFilter();
	//enumerate pins
	void enumPins(IBaseFilter* pFilter);
	//enumerate filters
	void enumFilters(IFilterGraph* pGraph);
};

#endif