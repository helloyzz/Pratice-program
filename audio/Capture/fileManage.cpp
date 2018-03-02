#include "fileManage.h"

fileManage::fileManage() :useVolume(NULL), realizePath(NULL) {
}
fileManage::~fileManage() {
	if(useVolume!=NULL) delete[] useVolume;
	if(realizePath!=NULL) delete[] realizePath;
}

UINT fileManage::makeVolume() {
	WCHAR volumePathName[MAX_PATH+1];	
	UINT len = 0;

	if(getVolume(volumePathName, -1)) {
		len = wcslen(volumePathName);
		useVolume = new WCHAR[len+2];
		useVolume[len] = L'\0';
		wmemcpy(useVolume, volumePathName, len);
		useVolume[len] = L'\\';
		useVolume[len+1] = L'\0';
	}
	return len;
}
UINT fileManage::makeVolume(const UINT num) {
	WCHAR volumePathName[MAX_PATH+1];	
	UINT len = 0;

	if(getVolume(volumePathName, num)) {
		len = wcslen(volumePathName);
		useVolume = new WCHAR[len+2];
		useVolume[len] = L'\0';
		wmemcpy(useVolume, volumePathName, len);
		useVolume[len] = L'\\';
		useVolume[len+1] = L'\0';
	}
	return len;
}
UINT fileManage::getVolume(WCHAR* volumePathName, UINT num) const {
	HANDLE findHandle = NULL;
	DWORD charCount = MAX_PATH+1;
	WCHAR volumeName[MAX_PATH+1];
	WCHAR deviceName[MAX_PATH+1];
	DWORD index = 0;
	UINT result = 0;
	UINT count = 0;

	findHandle = FindFirstVolume(volumeName, ARRAYSIZE(volumeName));
	if(INVALID_HANDLE_VALUE==findHandle) return 0;
	while(TRUE) {
		index = wcslen(volumeName)-1;
		volumeName[index] = L'\0';
		result = QueryDosDevice(&volumeName[4], deviceName, ARRAYSIZE(deviceName));
		volumeName[index] = L'\\';

		if(ERROR_INSUFFICIENT_BUFFER==result || 0==result) {
			result = 0;
			break;
		}
		result = retrieveDevName(deviceName);
		if(!result) {
			size_t temp = wcslen(volumePathName);
			if(volumePathName[temp]==L'\0') result=1;
			break;
		}
		result = GetVolumePathNamesForVolumeName(volumeName, volumePathName, charCount, &charCount);
		if(result) {
			if(count++==num) {
				size_t temp = wcslen(volumePathName);
				if(volumePathName[temp]==L'\0') result=1;
				break;
			}
			result = FindNextVolume(findHandle, volumeName, ARRAYSIZE(volumeName));
		}
	}

	FindVolumeClose(findHandle);
	findHandle = INVALID_HANDLE_VALUE;
	return result;
}
BOOL fileManage::retrieveDevName(WCHAR* deviceName) const {
	WCHAR tem = L'0';
	UINT index = 0;
	WCHAR bvalue[5] = {L'O',L'L',L'U',L'M',L'E'};
	WCHAR svalue[5] = {L'o',L'l',L'u',L'm',L'e'};
	int len = 5;
	short count = 0;
	BOOL label = FALSE;

	while(tem!=L'\0') {			
		tem = deviceName[index++];
		if(tem==L'V' || tem==L'v') {
			//volume
			for(int i=0; i<5; i++){
				if(svalue[i]==deviceName[index+i] || bvalue[i]==deviceName[index+i]) {
					count++;
				} else {
					count = 0;
					break;
				}
			}
			if(count==len) {
				label=TRUE;
				break;
			}
		}
	}
	return label;
}

//second parameter must be an effective address
//third parameter is start copy position
UINT fileManage::copyString(const WCHAR* src, WCHAR* dest, UINT pos) const {
	DWORD len = wcslen(src);
	if(len<=0 || dest==NULL || pos<0) return 0;
	for(UINT i=0; i<len; i++, pos++) {
		dest[pos] = src[i];
	}
	return pos;
}
UINT fileManage::randomFileName() {
	DWORD val = 0;
	UINT len = 0;
	DWORD time = GetTickCount();
	WCHAR temp[12];
	UINT index = 0;
	while(time!=0) {
		val = time%10;
		temp[index++] = (WCHAR)(val+48);
		len++;
		time = time/10;
	}
	index--;
	for(UINT i=0; i<len; i++, index--) {
		fileName[i] = temp[index];
	}
	fileName[len] = L'\0';
	return len;
}
//create directory
void fileManage::makeDir(WCHAR* dirPath, const UINT vlen, const UINT plen) const {
	int pos = 0;
	int len = (vlen+plen+1)<<1;
	WCHAR* makePath = new WCHAR[len];
	pos = copyString(useVolume, makePath, pos);
	WCHAR* temp = dirPath;
	for(UINT i=0; i<plen; i++) {
		makePath[pos++] = (*temp++);
		if(*temp==L'\\' || *temp==L'\0') {
			makePath[pos] = L'\0';
			CreateDirectory(makePath, NULL);
		}
	}
	delete[] makePath;
}
void fileManage::makeFilePath(WCHAR* dirPath, WCHAR* suffix) const {
	UINT pos = 0;
	pos = copyString(useVolume, realizePath, pos);
	pos = copyString(dirPath, realizePath, pos);
	if(realizePath[pos-1]!=L'\\') realizePath[pos++] = L'\\';
	realizePath[pos] = L'\0';
	pos = copyString(fileName, realizePath, pos);
	pos = copyString(suffix, realizePath, pos);
	realizePath[pos] = L'\0';
}
WCHAR* fileManage::getUsePath(WCHAR* dirPath, WCHAR* suffix) {
	if(useVolume!=NULL || realizePath!=NULL) {
		delete[] useVolume;
		delete[] realizePath;
	}
	int vlen = makeVolume();
	int plen = wcslen(dirPath);
	makeDir(dirPath, vlen, plen);
	if(dirPath[plen-1]!=L'\\') {
		plen++;
	}
	int flen = randomFileName();
	int slen = wcslen(suffix);
	int len = (vlen+plen+flen+slen)<<1;
	realizePath = new WCHAR[len];
	makeFilePath(dirPath, suffix);

	return realizePath;
}
WCHAR* fileManage::getUsePath(const UINT num, WCHAR* dirPath, WCHAR* suffix) {
	if(useVolume!=NULL || realizePath!=NULL) {
		delete[] useVolume;
		delete[] realizePath;
	}
	int vlen = makeVolume(num);
	int plen = wcslen(dirPath);
	makeDir(dirPath, vlen, plen);
	if(dirPath[plen-1]!=L'\\') {
		plen++;
	}
	int flen = randomFileName();
	int slen = wcslen(suffix);
	int len = vlen+plen+flen+slen;
	realizePath = new WCHAR[len];
	makeFilePath(dirPath, suffix);

	return realizePath;
}
