#ifndef _ENUM_DEVICE_
#define _ENUM_DEVICE_

#include "commonFun.h"

class enumDevice {
public:
	enumDevice();
	~enumDevice();

	//initialize containers
	BOOL initDevContainer();
	//get input device end element
	WCHAR* getInDevEnd() const;
	//get out device end element
	WCHAR* getOutDevEnd() const;
	//get input device start element
	WCHAR* getInDevStart() const;
	//get out device start element
	WCHAR* getOutDevStart() const;
	//get device name by position
	WCHAR* getInPos(int pos) const;
	WCHAR* getOutPos(int pos) const;
private:
	//add devices to container
	UINT addDevToContainer(GUID category, std::vector<wchar_t*>* vec);
	//release input devices container
	void releaseInDevContainer();
	//release output devices container
	void releaseOutDevContainer();
private:
	std::vector<wchar_t*> inDevContainer;
	std::vector<wchar_t*> outDevContainer;
};

#endif