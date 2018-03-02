#ifndef _FILE_MANAGE_
#define _FILE_MANAGE_

#include "baseIndex.h"

class fileManage {
public:
	fileManage();
	~fileManage();

	WCHAR* getUsePath(const UINT num, WCHAR* dirPath, WCHAR* suffix);
	WCHAR* getUsePath(WCHAR* dirPath, WCHAR* suffix);
private:
	UINT makeVolume();
	UINT makeVolume(const UINT num);
	UINT getVolume(WCHAR* volumePathName, UINT num) const;
	BOOL retrieveDevName(WCHAR* deviceName) const;

	UINT randomFileName();
	UINT copyString(const WCHAR* src, WCHAR* dest, UINT pos) const;
	void makeFilePath(WCHAR* dirPath, WCHAR* suffix) const;
	void makeDir(WCHAR* dirPath, const UINT vlen, const UINT plen) const;
private:
	WCHAR* useVolume;
	WCHAR fileName[15];
	WCHAR* realizePath;
};

#endif 