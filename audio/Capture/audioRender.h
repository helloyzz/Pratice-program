#ifndef _AUDIO_RENDER_
#define _AUDIO_RENDER_

#include "audioManage.h"

class audioRender :public audioManage {
public:
	audioRender();
	~audioRender();

	HRESULT initRender(WCHAR* filePath, const BSTR deviceName);
	HRESULT startRender();
	HRESULT pauseRender();
	HRESULT stopRender();
private:
	IBaseFilter* pDevice;
	IBaseFilter* pReader;
	IFileSourceFilter* pSource;
	IMediaControl* pControl;
	IMediaEvent* pEvent;
};

#endif