#ifndef _FILE_MANAGE_
#define _FILE_MANAGE_

#include "fileIndex.h"

class fileManage {
public:
	fileManage();
	~fileManage();

	WCHAR* getUsePath(UINT num, WCHAR* dirPath, WCHAR* suffix);
	WCHAR* getUsePath(WCHAR* dirPath, WCHAR* suffix);
private:
	UINT makeVolume();
	UINT makeVolume(UINT num);
	UINT getVolume(WCHAR* volumePathName, UINT num);
	BOOL retrieveDevName(WCHAR* deviceName);

	UINT randomFileName();
	UINT copyString(const WCHAR* src, WCHAR* dest, UINT pos);
	void makeFilePath(WCHAR* dirPath, WCHAR* suffix);
	void makeDir(WCHAR* dirPath, UINT vlen, UINT plen);
private:
	WCHAR* useVolume;
	WCHAR fileName[12];
	WCHAR* realizePath;
};

#endif 