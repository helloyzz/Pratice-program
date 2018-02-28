#include "enumDevice.h"

enumDevice::enumDevice() {
}
enumDevice::~enumDevice() {
	releaseInDevContainer();
	releaseOutDevContainer();
}

UINT enumDevice::addDevToContainer(const GUID category, std::vector<wchar_t*>* vec) {
	IEnumMoniker* pEnumMoniker = NULL;
	IMoniker* pMoniker = NULL;
	UINT count = 0;

	if(S_OK==createMonEnum(category, &pEnumMoniker)) {
		while(S_OK==bindStartMoniker(pEnumMoniker, &pMoniker)) {
			BSTR pName = NULL;
			if(S_OK==getMonikerName(pMoniker, &pName)) {
				UINT len = wcslen((wchar_t*)pName);
				wchar_t* moniker = new wchar_t[len+1];
				moniker[len] = NULL;
				wmemcpy(moniker, pName, len);
				vec->push_back(moniker);
				count++;
			}
			safeRelease(&pMoniker);
		}
	}
	safeRelease(&pEnumMoniker);
	return count;
}
//initialize containers
BOOL enumDevice::initDevContainer() {
	BOOL res = FALSE;
	UINT icount = addDevToContainer(CLSID_AudioInputDeviceCategory, &inDevContainer);
	UINT ocount = addDevToContainer(CLSID_AudioRendererCategory, &outDevContainer);
	if(icount>0 && ocount>0) res = TRUE;
	return res;
}
//release input devices container
void enumDevice::releaseInDevContainer() {
	std::vector<wchar_t*>::iterator iter;
	for(iter=inDevContainer.begin(); iter!=inDevContainer.end(); iter++) {
		delete[] (*iter);
	}
	inDevContainer.clear();
}
//release output devices container
void enumDevice::releaseOutDevContainer() {
	std::vector<wchar_t*>::iterator iter;
	for(iter=outDevContainer.begin(); iter!=outDevContainer.end(); iter++) {
		delete[] (*iter);
	}
	outDevContainer.clear();
}

//get input device end element
WCHAR* enumDevice::getInDevEnd() {
	if(inDevContainer.empty()) return NULL;
	std::vector<wchar_t*>::iterator iter = inDevContainer.end()-1;
	return (*iter);
}
//get out device end element
WCHAR* enumDevice::getOutDevEnd() {
	if(outDevContainer.empty()) return NULL;
	std::vector<wchar_t*>::iterator iter = outDevContainer.end()-1;
	return (*iter);
}
//get input device start element
WCHAR* enumDevice::getInDevStart() {
	if(inDevContainer.empty()) return NULL;
	std::vector<wchar_t*>::iterator iter = inDevContainer.begin();
	return (*iter);
}
//get out device start element
WCHAR* enumDevice::getOutDevStart() {
	if(outDevContainer.empty()) return NULL;
	std::vector<wchar_t*>::iterator iter = outDevContainer.begin();
	return (*iter);
}
//get device name by position
WCHAR* enumDevice::getInPos(int pos) {
	std::vector<wchar_t*>::iterator iter = inDevContainer.begin();
	while(pos--) {
		if(iter==inDevContainer.end()) {
			iter--;
			break;
		}
		iter++;
	}
	return (*iter);
}

WCHAR* enumDevice::getOutPos(int pos) {
	std::vector<wchar_t*>::iterator iter = outDevContainer.begin();
	return NULL;
}
