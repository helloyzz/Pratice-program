#include "audioRender.h"

audioRender::audioRender(): audioManage(), pDevice(NULL), pReader(NULL),
							pControl(NULL), pEvent(NULL), pSource(NULL) {
}
audioRender::~audioRender() {
	safeRelease(&pReader);
	safeRelease(&pDevice);
	safeRelease(&pSource);
	safeRelease(&pEvent);
	safeRelease(&pControl);
}

HRESULT audioRender::initRender(WCHAR* filePath, const BSTR deviceName) {
	HRESULT hr = S_FALSE;

	if(filePath && deviceName && 
		!createInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, &pGraph) && 
		!addCategoryByName(CLSID_AudioRendererCategory, &pDevice, deviceName) && 
		!addFilterByCLSID(CLSID_AsyncReader, &pReader, NULL) && 
		!pReader->QueryInterface(IID_IFileSourceFilter, (void**)&pSource) && 
		!pSource->Load(filePath, NULL) && 
		!pGraph->QueryInterface(IID_IMediaControl, (void**)&pControl) && 
		!pGraph->QueryInterface(IID_IMediaEvent, (void**)&pEvent) && 
		!connectFilters(pReader, pDevice)) {
		hr = S_OK;
	}
	return hr;
}
HRESULT audioRender::startRender() {
	return pControl->Run();
}
HRESULT audioRender::pauseRender() {
	return pControl->Pause();
}
HRESULT audioRender::stopRender() {
	return pControl->Stop();
}