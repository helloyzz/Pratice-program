#include "wavCapture.h"

wavCapture::wavCapture()
	: audioManage(), pDevice(NULL), pInfTee(NULL),
	pWavDest(NULL), pRender(NULL), pWriter(NULL), 
	pSink(NULL), pControl(NULL){
}
wavCapture::~wavCapture() {
	safeRelease(&pDevice);
	safeRelease(&pInfTee);
	safeRelease(&pWavDest);
	safeRelease(&pRender);
	safeRelease(&pWriter);
	safeRelease(&pSink);
	safeRelease(&pControl);
}

// if flag > 0 capture audio throw render else if flag == 0 not throw render
HRESULT wavCapture::initCapture(WCHAR* filePath, const BSTR deviceName) {
	HRESULT hr = S_FALSE;

	if(filePath && deviceName && 
		!registerWavFilter() && 
		!createInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, &pGraph) && 
		!addCategoryByName(CLSID_AudioInputDeviceCategory, &pDevice, deviceName) && 
		!addFilterByCLSID(CLSID_InfTee, &pInfTee, NULL) && 
		!addFilterByCLSID(CLSID_WavDest, &pWavDest, NULL) && 
		!addFilterByCLSID(CLSID_DSoundRender, &pRender, NULL) && 
		!addFilterByCLSID(CLSID_FileWriter, &pWriter, NULL) && 
		!pWriter->QueryInterface(IID_IFileSinkFilter, (void**)&pSink) && 
		!pSink->SetFileName(filePath, NULL) && 
		!pGraph->QueryInterface(IID_IMediaControl, (void**)&pControl) && 
		!connectFilters(pDevice, pWavDest) && 
		!connectFilters(pWavDest, pWriter)) {
		hr = S_OK;
	}
	return hr;
}
HRESULT wavCapture::startCapture() {
	return pControl->Run();
}
HRESULT wavCapture::pauseCapture() {
	return pControl->Pause();
}
HRESULT wavCapture::stopCapture() {
	unRegisterWavFilter();
	return pControl->Stop();
}
