#include <iostream>
using std::wcout;
using std::wcin;
using std::endl;
using std::wcerr;
using std::wclog;
using std::left;

#include <windows.h>
#define NOWTFUNCTIONS
#include <WinTab.h>

typedef UINT (WINAPI *WTInfo_Type)(UINT,UINT,LPVOID);
WTInfo_Type WTInfoW = nullptr;


std::wostream &operator << (std::wostream &wout,const AXIS &axis)
{
	wout << L"range: " << axis.axMin << L" - " << axis.axMax << endl;
	wout << std::fixed << L"resolution: " << (axis.axResolution >> 16) + (axis.axResolution & 0xffff)/(float)0x10000;
	switch(axis.axUnits)
	{
	case TU_NONE:
		wout << L"no unit";
		break;
	case TU_INCHES:
		wout << L" per inch";
		break;
	case TU_CENTIMETERS:
		wout << L" per cm";
		break;
	case TU_CIRCLE:
		wout << L" per circle";
		break;
	} // end switch
	wout << endl;
	return wout;
} // end function operator <<

int main()
{
	AXIS x,y,z,npressure,tpressure,rotation[3],orientation[3];
	UINT name_size,temp;
	wchar_t *name;
	UINT devices, extentions, managers, report_rate,cursor_types;

	HMODULE WinTabHandle = LoadLibraryW(L"WinTab32.dll");
	WTInfoW = (WTInfo_Type)GetProcAddress(WinTabHandle,(LPSTR)1020);

	wcout << L"Largest category size in bytes: " << WTInfoW(0,0,nullptr) << endl;
	name_size = WTInfoW(WTI_DEVICES,DVC_NAME,nullptr);
	name = (wchar_t*)new char[name_size];
	WTInfoW(WTI_DEVICES,DVC_NAME,name);
	wcout << L"Device name: " << name << endl;
	delete[] name;
	WTInfoW(WTI_DEVICES,DVC_X,&x);
	WTInfoW(WTI_DEVICES,DVC_Y,&y);
	WTInfoW(WTI_DEVICES,DVC_Z,&z);
	WTInfoW(WTI_DEVICES,DVC_NPRESSURE,&npressure);
	WTInfoW(WTI_DEVICES,DVC_TPRESSURE,&tpressure);
	WTInfoW(WTI_DEVICES,DVC_ORIENTATION,&orientation);
	temp = WTInfoW(WTI_DEVICES,DVC_ROTATION,&rotation);
	wcout << x << y << z << npressure << tpressure
		<< orientation[0] << orientation[1] << orientation[2]
		<< rotation[0] << rotation[1] << rotation[2];
	WTInfoW(WTI_INTERFACE,IFC_NDEVICES,&devices);
	wcout << L"number of devices: " << devices << endl;
	WTInfoW(WTI_INTERFACE,IFC_NEXTENSIONS,&extentions);
	wcout << L"number of extentions: " << extentions << endl;
	WTInfoW(WTI_INTERFACE,IFC_NMANAGERS,&managers);
	wcout << L"number of managers: " << managers << endl;
	WTInfoW(WTI_DEVICES,DVC_PKTRATE,&report_rate);
	wcout << L"report rate: " << report_rate << L"Hz" << endl;
	WTInfoW(WTI_DEVICES,DVC_NCSRTYPES,&cursor_types);
	wcout << L"cursor types: " << cursor_types << endl;

	FreeLibrary(WinTabHandle);
	system("pause");
	return 0;
} // end function main
