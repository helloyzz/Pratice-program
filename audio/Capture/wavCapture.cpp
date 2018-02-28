#include "wavCapture.h"

wavCapture::wavCapture()
	: pGraph(NULL), pDevice(NULL), pInfTee(NULL),
	pWavDest(NULL), pRender(NULL), pWriter(NULL), 
	pSink(NULL), pControl(NULL){
}
wavCapture::~wavCapture() {
	safeRelease(&pGraph);
	safeRelease(&pDevice);
	safeRelease(&pInfTee);
	safeRelease(&pWavDest);
	safeRelease(&pRender);
	safeRelease(&pWriter);
	safeRelease(&pSink);
	safeRelease(&pControl);
}

// if flag > 0 capture audio throw render else if flag == 0 not throw render
HRESULT wavCapture::initCapture(WCHAR* filePath, const BSTR deviceName, UINT type) {
	HRESULT hr = -1;

	if(filePath==NULL || deviceName==NULL) return hr;
	//init instance
	registerWavFilter();
	hr = createInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, &pGraph);
	if(hr!=S_OK) return hr;
	hr = addCategoryByName(CLSID_AudioInputDeviceCategory, pGraph, &pDevice, deviceName);
	if(hr!=S_OK) return hr;
	hr = addFilterByCLSID(pGraph, CLSID_InfTee, &pInfTee, NULL);
	if(hr!=S_OK) return hr;
	hr = addFilterByCLSID(pGraph, CLSID_WavDest, &pWavDest, NULL);
	if(hr!=S_OK) return hr;
	hr = addFilterByCLSID(pGraph, CLSID_DSoundRender, &pRender, NULL);
	if(hr!=S_OK) return hr;
	hr = addFilterByCLSID(pGraph, CLSID_FileWriter, &pWriter, NULL);
	if(hr!=S_OK) return hr;
	//init interface
	hr = pWriter->QueryInterface(IID_IFileSinkFilter, (void**)&pSink);
	if(hr!=S_OK) return hr;
	hr = pSink->SetFileName(filePath, NULL);
	if(hr!=S_OK) return hr;
	hr = pGraph->QueryInterface(IID_IMediaControl, (void**)&pControl);
	if(hr!=S_OK) return hr;
	//connect filters
	if(type) {
		hr = connectFilters(pGraph, pDevice, pInfTee);
		if(hr!=S_OK) return hr;
		hr = connectFilters(pGraph, pInfTee, pWavDest);
		if(hr!=S_OK) return hr;
		hr = connectFilters(pGraph, pInfTee, pRender);
		if(hr!=S_OK) return hr;
		hr = connectFilters(pGraph, pWavDest, pWriter);
	} else {
		hr = connectFilters(pGraph, pDevice, pWavDest);
		if(hr!=S_OK) return hr;
		hr = connectFilters(pGraph, pWavDest, pWriter);
	}
	return hr;
}
void wavCapture::startCapture() {
	pControl->Run();
}
void wavCapture::pauseCapture() {
	pControl->Pause();
}
void wavCapture::stopCapture() {
	pControl->Stop();
	unRegisterWavFilter();
}
