#ifndef _AUDIO_CAPTURE_
#define _AUDIO_CAPTURE_
/*
an audio capture project base on windows platform,
use DirectShow API.
*/
#include "audioManage.h"

class wavCapture :public audioManage{
public:
	wavCapture();
	~wavCapture();

	//wav capture
	HRESULT initCapture(WCHAR* filePath, const BSTR deviceName, UINT type);
	void startCapture();
	void pauseCapture();
	void stopCapture();
private:
	IGraphBuilder* pGraph;
	IBaseFilter* pDevice;
	IBaseFilter* pInfTee;
	IBaseFilter* pWavDest;
	IBaseFilter* pRender;
	IBaseFilter* pWriter;
	IFileSinkFilter* pSink;
	IMediaControl* pControl;
};

#endif