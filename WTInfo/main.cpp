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
using std::ostringstream;
using std::istringstream;
using std::stringstream;

#include <string>
using std::wstring;
using std::getline;

#include <memory>
using std::unique_ptr;

#include <windows.h>
#define NOWTFUNCTIONS
#include <WinTab.h>

typedef UINT (WINAPI *WTInfo_Type)(UINT,UINT,LPVOID);
const UINT WTInfoW_Ordinal = 1020u;
WTInfo_Type WTInfoW = nullptr;


int main()
{
	HMODULE wintabModule;
	UINT block_size;
	Indent indent(0);
	unique_ptr<char[]> block;
	
	// configure debug parameters
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_CHECK_ALWAYS_DF|/*_CRTDBG_CHECK_CRT_DF|*/_CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN,_CRTDBG_MODE_DEBUG/*|_CRTDBG_MODE_WNDW*/);
	_CrtSetReportMode(_CRT_ERROR,_CRTDBG_MODE_DEBUG/*|_CRTDBG_MODE_WNDW*/);
	_CrtSetReportMode(_CRT_ASSERT,_CRTDBG_MODE_DEBUG/*|_CRTDBG_MODE_WNDW*/);

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
	UINT nDevices,nCursors,nContexts,nExtensions,nManagers;
	WTInfoW(WTI_INTERFACE,IFC_NDEVICES,&nDevices);
	WTInfoW(WTI_INTERFACE,IFC_NCURSORS,&nCursors);
	WTInfoW(WTI_INTERFACE,IFC_NCONTEXTS,&nContexts);
	WTInfoW(WTI_INTERFACE,IFC_NEXTENSIONS,&nExtensions);
	WTInfoW(WTI_INTERFACE,IFC_NMANAGERS,&nManagers);
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
	cw1=15,cw2=40,cw3=6;
	wcout << indent << left << setw(c1) << L"Category/Index" << L"Description" << L"\n\n";
	wcout << indent << left << setw(c1) << L"WTI_INTERFACE" << L"Contains global interface identification and capability information." << L"\n";
	++indent;
	wcout << indent << left << setw(cw1) << L"Index" << right << setw(cw2) << L"Value" << Indent(cw3) << L"Description" << L"\n\n";
	block_size = WTInfoW(WTI_INTERFACE,IFC_WINTABID,nullptr);
	block = unique_ptr<char[]>(new char[block_size]);
	WTInfoW(WTI_INTERFACE,IFC_WINTABID,block.get());
	wcout << indent << left << setw(cw1) << L"IFC_WINTABID" << right << setw(cw2) << (wchar_t*)block.get() << Indent(cw3) << L"Returns a copy of the null-terminated tablet hardware identifica­tion string in the user buffer. This string should include make, model, and revi­sion information in user-readable format." << L"\n";
	wcout << indent << left << setw(cw1) << L"IFC_NDEVICES" << right << setw(cw2) << nDevices << Indent(cw3) << L"Returns the number of devices supported." << L"\n";
	wcout << indent << left << setw(cw1) << L"IFC_NCURSORS" << right << setw(cw2) << nCursors << Indent(cw3) << L"Returns the total number of cursor types supported." << L"\n";
	wcout << indent << left << setw(cw1) << L"IFC_NCONTEXTS" << right << setw(cw2) << nContexts << Indent(cw3) << L"Returns the number of contexts supported." << L"\n";
	wcout << indent << left << setw(cw1) << L"IFC_NEXTENSIONS" << right << setw(cw2) << nExtensions << Indent(cw3) << L"Returns the number of extension data items supported." << L"\n";
	wcout << indent << left << setw(cw1) << L"IFC_NMANAGERS" << right << setw(cw2) << nManagers << Indent(cw3) << L"Returns the number of manager handles supported." << L"\n";
	--indent;
	wcout << indent << left << setw(c1) << L"WTI_STATUS" << L"Contains current interface resource usage statistics." << L"\n";
	wcout << indent << left << setw(c1) << L"WTI_DEFCONTEXT" << L"Contains the current default digitizing logical context." << L"\n";
	wcout << indent << left << setw(c1) << L"WTI_DEFSYSCTX" << L"Contains the current default system logical context." << L"\n";
	wcout << indent << left << setw(c1) << L"WTI_DEVICES" << L"Each contains capability and status information for a device." << L"\n";
	wcout << indent << left << setw(c1) << L"WTI_CURSORS" << L"Each contains capability and status information for a cursor type." << L"\n";
	wcout << indent << left << setw(c1) << L"WTI_EXTENSIONS" << L"Each contains descriptive information and defaults for an extension." << L"\n";
	wcout << indent << left << setw(c1) << L"WTI_DDCTXS" << L"Each contains the current default digitizing logical context for the corre­sponding device." << L"\n";
	wcout << indent << left << setw(c1) << L"WTI_DSCTXS" << L"Each contains the current default system logical context for the correspond­ing device." << L"\n";

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
