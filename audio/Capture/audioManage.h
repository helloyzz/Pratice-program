#ifndef _AUDIO_MANAGE_
#define _AUDIO_MANAGE_

#include "commonFun.h"

class audioManage {
protected:
	audioManage();
	~audioManage();
	//add a filter by Name of device category
	HRESULT addCategoryByName(const GUID category, IBaseFilter** pBaseFilter, const BSTR mName) const;
	//add a filter by CLSID to graph
	HRESULT addFilterByCLSID(CLSID clsid, IBaseFilter** ppF, LPCWSTR wasName) const;
	//create a filter by Name of device category
	HRESULT createCategoryByName(const GUID category, IBaseFilter** pBaseFilter, const BSTR mName) const;
	//create and return a filter
	HRESULT createFilterByCLSID(const CLSID clsid, IBaseFilter** ppF) const;
	//get a pins
	HRESULT getPin(IBaseFilter* pFilter, const PIN_DIRECTION pinDir, IPin** pInt) const;
	//connect two filters
	HRESULT connectFilters(IBaseFilter* pSrc, IBaseFilter* pDest) const;
	//find a unconnected pin
	BOOL findUnconnectPin(IPin* pPin) const;
	//dynamic load
	template<typename TYPE>
	BOOL dynamicLoad(HINSTANCE* hinstLib, const LPCWSTR dllName, const LPCSTR funName, TYPE* procAdd) const;
	//register a filter
	HRESULT registerWavFilter() const;
	//unregister a filter
	HRESULT unRegisterWavFilter() const;
protected:
	IGraphBuilder* pGraph;
};

#endif