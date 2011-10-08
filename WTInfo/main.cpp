#include <iostream>
using std::wcout;
using std::wcin;
using std::wcerr;
using std::wclog;
using std::endl;
using std::left;
using std::right;

#include <iomanip>
using std::setw;
using std::setprecision;

#include <sstream>
using std::wostringstream;
using std::wistringstream;
using std::wstringstream;

#include <string>
using std::wstring;
using std::getline;

#include <memory>
using std::unique_ptr;

#include <bitset>
using std::bitset;

#include <windows.h>
#define NOWTFUNCTIONS
#include <WinTab.h>

typedef UINT (WINAPI *WTInfo_Type)(UINT,UINT,LPVOID);
const UINT WTInfoW_Ordinal = 1020u;
WTInfo_Type WTInfoW = nullptr;

#include "error handling.h"
#include "formating.h"

//template<typename T>
//struct LocalDelete
//{
//	void operator()(T *pointer) const
//	{
//		LocalFree(pointer);
//	} // end function operator()
//}; // end struct LocalDelete

int main()
{
	HMODULE wintabModule;
	UINT block_size;
	Indent indent(0);
	unique_ptr<char[]> block;
	
	// configure debug parameters
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_CHECK_ALWAYS_DF|/*_CRTDBG_CHECK_CRT_DF|*/_CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN,_CRTDBG_MODE_DEBUG/*|_CRTDBG_MODE_WNDW*/);
	_CrtSetReportMode(_CRT_ERROR,_CRTDBG_MODE_DEBUG|_CRTDBG_MODE_WNDW);
	_CrtSetReportMode(_CRT_ASSERT,_CRTDBG_MODE_DEBUG|_CRTDBG_MODE_WNDW);

	// load WinTab
	if(wintabModule = LoadLibraryW(L"WinTab32.dll"))
		wcout << L"Module loaded succesfully.\n";
	else
		wcout << Error(L"Could not load module: ") << endl;

	// Get WTInfo address
	if(WTInfoW = (WTInfo_Type)GetProcAddress(wintabModule,(LPSTR)(WTInfoW_Ordinal)))
		wcout << L"Acquired WTInfoW address.\n";
	else
		wcout << Error(L"Could not acquire WTInfoW address: ");

	wcout << L"\n\n";

	// largest category size
	if((block_size = WTInfoW(0,0,nullptr)) != 0)
		wcout << L"Size of largest category: " << block_size << L"B\n";
	else
		wcout << L"There is no data available from WTInfoW" << endl;

	wcout << L"\n";

	// individual category sizes
	UINT nDevices,nCursors,nContexts,nExtensions,nManagers,options,save_size,curContexts,curSysContexts,curPktRate,curManagers;
	WORD specVersion,implVersion;
	DWORD buttonUse,sysBtnUse;
	WTPKT dataMask;
	BOOL globSysPointing;
	WTInfoW(WTI_INTERFACE,IFC_NDEVICES,&nDevices);
	WTInfoW(WTI_INTERFACE,IFC_NCURSORS,&nCursors);
	WTInfoW(WTI_INTERFACE,IFC_NCONTEXTS,&nContexts);
	WTInfoW(WTI_INTERFACE,IFC_NEXTENSIONS,&nExtensions);
	WTInfoW(WTI_INTERFACE,IFC_NMANAGERS,&nManagers);
	WTInfoW(WTI_INTERFACE,IFC_SPECVERSION,&specVersion);
	WTInfoW(WTI_INTERFACE,IFC_IMPLVERSION,&implVersion);
	WTInfoW(WTI_INTERFACE,IFC_CTXSAVESIZE,&save_size);
	WTInfoW(WTI_STATUS,STA_CONTEXTS,&curContexts);
	WTInfoW(WTI_STATUS,STA_SYSCTXS,&curSysContexts);
	WTInfoW(WTI_STATUS,STA_PKTRATE,&curPktRate);
	WTInfoW(WTI_STATUS,STA_MANAGERS,&curManagers);
	WTInfoW(WTI_STATUS,STA_SYSTEM,&globSysPointing);
	WTInfoW(WTI_STATUS,STA_BUTTONUSE,&buttonUse);
	WTInfoW(WTI_STATUS,STA_SYSBTNUSE,&sysBtnUse);
	UINT w1=18,w2=10;
	wcout << indent << left << setw(w1) << L"Category" << right << setw(w2) << L"Size(Bytes)" << L"\n\n";
	wcout << indent << left << setw(w1) << L"WTI_INTERFACE" << right << setw(w2) << WTInfoW(WTI_INTERFACE,0,nullptr) << L"B\n";
	wcout << indent << left << setw(w1) << L"WTI_STATUS" << right << setw(w2) << WTInfoW(WTI_STATUS,0,nullptr) << L"B\n";
	wcout << indent << left << setw(w1) << L"WTI_DEFCONTEXT" << right << setw(w2) << WTInfoW(WTI_DEFCONTEXT,0,nullptr) << L"B\n";
	wcout << indent << left << setw(w1) << L"WTI_DEFSYSCTX" << right << setw(w2) << WTInfoW(WTI_DEFSYSCTX,0,nullptr) << L"B\n";
	UINT cw1=9,cw2=3,cw3=2;
	wcout << indent << left << setw(w1) << L"WTI_DEVICES:" << L"\n";
	++indent;
	for(UINT c = 0 ; c < nDevices ; ++c)
		wcout << indent << left << setw(cw1) << L"device" << right << setw(cw2) << c << Indent(cw3) << setw(w2) << WTInfoW(WTI_DEVICES+c,0,nullptr) << L"B\n";
	--indent;
	wcout << indent << left << setw(w1) << L"WTI_CURSORS:" << L"\n";
	++indent;
	for(UINT c = 0 ; c < nCursors ; ++c)
		wcout << indent << left << setw(cw1) << L"cursor" << right << setw(cw2) << c << Indent(cw3) << setw(w2) << WTInfoW(WTI_CURSORS+c,0,nullptr) << L"B\n";
	--indent;
	wcout << indent << left << setw(w1) << L"WTI_EXTENSIONS:" << L"\n";
	++indent;
	for(UINT c = 0 ; c < nExtensions ; ++c)
		wcout << indent << left << setw(cw1) << L"extension" << right << setw(cw2) << c << Indent(cw3) << setw(w2) << WTInfoW(WTI_EXTENSIONS+c,0,nullptr) << L"B\n";
	--indent;
	wcout << indent << left << setw(w1) << L"WTI_DDCTXS:" << L"\n";
	++indent;
	for(UINT c = 0 ; c < nDevices ; ++c)
		wcout << indent << left << setw(cw1) << L"device" << right << setw(cw2) << c << Indent(cw3) << setw(w2) << WTInfoW(WTI_DDCTXS+c,0,nullptr) << L"B\n";
	--indent;
	wcout << indent << left << setw(w1) << L"WTI_DSCTXS:" << L"\n";
	++indent;
	for(UINT c = 0 ; c < nDevices ; ++c)
		wcout << indent << left << setw(cw1) << L"device" << right << setw(cw2) << c << Indent(cw3) << setw(w2) << WTInfoW(WTI_DSCTXS+c,0,nullptr) << L"B\n";
	--indent;

	wcout << L"\n\n\n\n";

	// actual information
	UINT c1 = 65;
	cw1=20,cw2=35,cw3=6;
	UINT sIndent=27,scw1=25,scw2=7,scw3=6;
	wcout << std::boolalpha;
	wcout << indent << left << setw(c1) << L"Category/Index" << L"Description" << L"\n\n";
	wcout << indent << left << setw(c1) << L"WTI_INTERFACE" << L"Contains global interface identification and capability information." << L"\n";
	++indent;
	wcout << indent << left << setw(cw1) << L"Index" << right << setw(cw2) << L"Value" << Indent(cw3) << L"Description" << L"\n\n";
	block_size = WTInfoW(WTI_INTERFACE,IFC_WINTABID,nullptr);
	block = unique_ptr<char[]>(new char[block_size]);
	WTInfoW(WTI_INTERFACE,IFC_WINTABID,block.get());
	wcout << indent << left << setw(cw1) << L"IFC_WINTABID" << right << setw(cw2) << (wchar_t*)block.get() << Indent(cw3) << L"Returns a copy of the null-terminated tablet hardware identification string in the user buffer. This string should include make, model, and revision information in user-readable format." << L"\n";
	wcout << indent << left << setw(cw1) << L"IFC_SPECVERSION" << right << setw(cw2) << WTVersion(specVersion) << Indent(cw3) << L"Returns the specification version number. The high-order byte contains the major version number; the low-order byte contains the minor version number." << L"\n";
	wcout << indent << left << setw(cw1) << L"IFC_IMPLVERSION" << right << setw(cw2) << WTVersion(implVersion) << Indent(cw3) << L"Returns the implementation version number. The high-order byte contains the major version number; the low-order byte contains the minor version number." << L"\n";
	wcout << indent << left << setw(cw1) << L"IFC_NDEVICES" << right << setw(cw2) << nDevices << Indent(cw3) << L"Returns the number of devices supported." << L"\n";
	wcout << indent << left << setw(cw1) << L"IFC_NCURSORS" << right << setw(cw2) << nCursors << Indent(cw3) << L"Returns the total number of cursor types supported." << L"\n";
	wcout << indent << left << setw(cw1) << L"IFC_NCONTEXTS" << right << setw(cw2) << nContexts << Indent(cw3) << L"Returns the number of contexts supported." << L"\n";
	WTInfoW(WTI_INTERFACE,IFC_CTXOPTIONS,&options);
	wcout << indent << left << setw(cw1) << L"IFC_CTXOPTIONS" << right << setw(cw2) << bitset<32>(options) << Indent(cw3) << L"Returns flags indicating which context options are supported." << L"\n";
	wcout << WTCOptions(options,sIndent,scw1,scw2,scw3);
	wcout << indent << left << setw(cw1) << L"IFC_CTXSAVESIZE" << right << setw(cw2) << save_size << Indent(cw3) << L"Returns the size of the save information returned from WTSave." << L"\n";
	wcout << indent << left << setw(cw1) << L"IFC_NEXTENSIONS" << right << setw(cw2) << nExtensions << Indent(cw3) << L"Returns the number of extension data items supported." << L"\n";
	wcout << indent << left << setw(cw1) << L"IFC_NMANAGERS" << right << setw(cw2) << nManagers << Indent(cw3) << L"Returns the number of manager handles supported." << L"\n";
	--indent;
	wcout << indent << left << setw(c1) << L"WTI_STATUS" << L"Contains current interface resource usage statistics." << L"\n";
	++indent;
	wcout << indent << left << setw(cw1) << L"Index" << right << setw(cw2) << L"Value" << Indent(cw3) << L"Description" << L"\n\n";
	wcout << indent << left << setw(cw1) << L"STA_CONTEXTS" << right << setw(cw2) << curContexts << Indent(cw3) << L"Returns the number of contexts currently open." << L"\n";
	wcout << indent << left << setw(cw1) << L"STA_SYSCTXS" << right << setw(cw2) << curSysContexts << Indent(cw3) << L"Returns the number of system contexts currently open." << L"\n";
	wcout << indent << left << setw(cw1) << L"STA_PKTRATE" << right << setw(cw2) << curPktRate << Indent(cw3) << L"Returns the maximum packet report rate currently being re­ceived by any context, in Hertz." << L"\n";
	WTInfoW(WTI_STATUS,STA_PKTDATA,&dataMask);
	wcout << indent << left << setw(cw1) << L"STA_PKTDATA" << right << setw(cw2) << bitset<32>(dataMask) << Indent(cw3) << L"Returns a mask indicating which packet data items are re­quested by at least one context." << L"\n";
	wcout << WTDataMask(dataMask,sIndent,scw1,scw2,scw3,specVersion);
	wcout << indent << left << setw(cw1) << L"STA_MANAGERS" << right << setw(cw2) << curManagers << Indent(cw3) << L"Returns the number of manager handles currently open." << L"\n";
	wcout << indent << left << setw(cw1) << L"STA_SYSTEM" << right << setw(cw2) << globSysPointing << Indent(cw3) << L"Returns a non-zero value if system pointing is available to the whole screen; zero otherwise." << L"\n";
	wcout << indent << left << setw(cw1) << L"STA_BUTTONUSE" << right << setw(cw2) << bitset<32>(buttonUse) << Indent(cw3) << L"Returns a button mask indicating the logical buttons whose events are requested by at least one context." << L"\n";
	wcout << indent << left << setw(cw1) << L"STA_SYSBTNUSE" << right << setw(cw2) << bitset<32>(sysBtnUse) << Indent(cw3) << L"Returns a button mask indicating which logical buttons are as­signed a system button function by the current cursor's system button map." << L"\n";
	--indent;
	wcout << indent << left << setw(c1) << L"WTI_DEFCONTEXT" << L"Contains the current default digitizing logical context." << L"\n";
	++indent;
	ExtLogContext context(indent,cw1,cw2,cw3,specVersion,sIndent,scw1,scw2,scw3);
	WTInfoW(WTI_DEFCONTEXT,0,&context);
	wcout << context;
	--indent;
	wcout << indent << left << setw(c1) << L"WTI_DEFSYSCTX" << L"Contains the current default system logical context." << L"\n";
	++indent;
	WTInfoW(WTI_DEFSYSCTX,0,&context);
	wcout << context;
	--indent;
	UINT sw1=9,sw2=3,sc3=2;
	wcout << indent << left << setw(c1) << L"WTI_DEVICES" << L"Each contains capability and status information for a device." << L"\n";
	++indent;
	for(UINT c = 0 ; c < nDevices ; ++c)
	{
		wcout << indent << left << setw(sw1) << L"device" << right << setw(sw2) << c << L"\n";
		++indent;
		wcout << ExtWTDevice(c,specVersion,indent,cw1-4,cw2,cw3,sIndent,scw1,scw2,scw3);
		--indent;
	} // end for
	--indent;
	wcout << indent << left << setw(c1) << L"WTI_CURSORS" << L"Each contains capability and status information for a cursor type." << L"\n";
	++indent;
	for(UINT c = 0 ; c < nCursors ; ++c)
	{
		wcout << indent << left << setw(sw1) << L"cursor" << right << setw(sw2) << c << L"\n";
		++indent;
		wcout << ExtWTCursor(c,specVersion,indent,cw1-4,cw2,cw3,sIndent,scw1,scw2,scw3);
		--indent;
	} // end for
	--indent;
	wcout << indent << left << setw(c1) << L"WTI_EXTENSIONS" << L"Each contains descriptive information and defaults for an extension." << L"\n";
	++indent;
	for(UINT c = 0 ; c < nExtensions ; ++c)
	{
		wcout << indent << left << setw(sw1) << L"extension" << right << setw(sw2) << c << L"\n";
		++indent;
		wcout << ExtWTExtension(c,specVersion,indent,cw1-4,cw2,cw3,sIndent,scw1,scw2,scw3);
		--indent;
	} // end for
	--indent;
	wcout << indent << left << setw(c1) << L"WTI_DDCTXS" << L"Each contains the current default digitizing logical context for the corresponding device." << L"\n";
	++indent;
	++context.indent;
	context.w1 -= 4;
	for(UINT c = 0 ; c < nDevices ; ++c)
	{
		wcout << indent << left << setw(sw1) << L"device" << right << setw(sw2) << c << L"\n";
		WTInfoW(WTI_DDCTXS+c,0,&context);
		wcout << context;
	} // end for
	--indent;
	wcout << indent << left << setw(c1) << L"WTI_DSCTXS" << L"Each contains the current default system logical context for the corresponding device." << L"\n";
	++indent;
	for(UINT c = 0 ; c < nDevices ; ++c)
	{
		wcout << indent << left << setw(sw1) << L"device" << right << setw(sw2) << c << L"\n";
		WTInfoW(WTI_DSCTXS+c,0,&context);
		wcout << context;
	} // end for
	--indent;

	wcout << L"\n\n\n";

	// unload WinTab
	if(FreeLibrary(wintabModule))
		wcout << L"Module unloaded succesfully.\n";
	else
		wcout << Error(L"Could not unload module: ") << endl;

	wcout << L"\n";

	system("pause");
	return 0;
} // end function main
