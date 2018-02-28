#include "audioRender.h"

audioRender::audioRender(): pGraph(NULL), pDevice(NULL), pReader(NULL),
							pControl(NULL), pEvent(NULL), pSource(NULL) {
}
audioRender::~audioRender() {
	safeRelease(&pGraph);
	safeRelease(&pReader);
	safeRelease(&pDevice);
	safeRelease(&pSource);
	safeRelease(&pEvent);
	safeRelease(&pControl);
}

HRESULT audioRender::initRender(WCHAR* filePath, const BSTR deviceName) {
	HRESULT hr = -1;

	if(filePath==NULL || deviceName==NULL) return hr;
	hr = createInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, &pGraph);
	if(S_OK!=hr) return hr;
	hr = addCategoryByName(CLSID_AudioRendererCategory, pGraph, &pDevice, deviceName);
	if(S_OK!=hr) return hr;
	hr = addFilterByCLSID(pGraph, CLSID_AsyncReader, &pReader, NULL);
	if(S_OK!=hr) return hr;
	hr = pReader->QueryInterface(IID_IFileSourceFilter, (void**)&pSource);
	if(S_OK!=hr) return hr;
	hr = pSource->Load(filePath, NULL);
	if(S_OK!=hr) return hr;
	
	hr = pGraph->QueryInterface(IID_IMediaControl, (void**)&pControl);
	if(S_OK!=hr) return hr;
	hr = pGraph->QueryInterface(IID_IMediaEvent, (void**)&pEvent);
	if(S_OK!=hr) return hr;

	hr = connectFilters(pGraph, pReader, pDevice);
	return hr;
}
void audioRender::startRender() {
	pControl->Run();
}
void audioRender::pauseRender() {
	pControl->Pause();
}
void audioRender::stopRender() {
	pControl->Stop();
}