#ifndef _AUDIO_RENDER_
#define _AUDIO_RENDER_

#include "audioManage.h"

class audioRender :public audioManage {
public:
	audioRender();
	~audioRender();

	HRESULT initRender(WCHAR* filePath, const BSTR deviceName);
	void startRender();
	void pauseRender();
	void stopRender();
private:
	IGraphBuilder* pGraph;
	IBaseFilter* pReader;
	IBaseFilter* pDevice;
	IFileSourceFilter* pSource;
	IMediaControl* pControl;
	IMediaEvent* pEvent;
};

#endif