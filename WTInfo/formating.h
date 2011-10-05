struct Indent
{
	Indent(unsigned int initial_size)
		:size(initial_size){}

	Indent &operator++()	// is this the postfix or the prefix?
	{
		size += 4;
		return *this;
	} // end function operator++

	Indent &operator--()
	{
		size -= 4;
		return *this;
	} // end function operator--

	//friend std::wostream &operator<<(std::wostream &wout,const Indent &indent);

	unsigned int size;
}; // end class Indent

std::wostream &operator<<(std::wostream &wout, const Indent &indent)
{
	wout << setw(indent.size) << L"";
	return wout;
} // end function operator<<

//std::wostream &operator << (std::wostream &wout,const AXIS &axis)
//{
//	wout << L"range: " << axis.axMin << L" - " << axis.axMax << endl;
//	wout << std::fixed << L"resolution: " << (axis.axResolution >> 16) + (axis.axResolution & 0xffff)/(float)0x10000;
//	switch(axis.axUnits)
//	{
//	case TU_NONE:
//		wout << L"no unit";
//		break;
//	case TU_INCHES:
//		wout << L" per inch";
//		break;
//	case TU_CENTIMETERS:
//		wout << L" per cm";
//		break;
//	case TU_CIRCLE:
//		wout << L" per circle";
//		break;
//	} // end switch
//	wout << endl;
//	return wout;
//} // end function operator <<

struct WTVersion
{
	WTVersion(WORD version)
		:v(version){}

	WORD v;
}; // end struct WTVersion

std::wostream &operator<<(std::wostream &wout, const WTVersion &version)
{
	std::wostringstream wsout;
	wsout << (version.v>>8) << L'.' << left << setw(2) << (version.v&0x00ff);
	wout << wsout.str();
	return wout;
} // end function operator<<

double toFloatingPoint(FIX32 fixPointNumber)
{
	return (fixPointNumber>>16)+double(0x0000ffff&fixPointNumber)/0x00010000;
} // end function toFloatingPoint

struct WTCOptions
{
	WTCOptions(UINT options,Indent indentation,UINT cw1,UINT cw2,UINT cw3)
		:o(options),indent(indentation),w1(cw1),w2(cw2),w3(cw3){}

	UINT o;
	Indent indent;
	UINT w1;
	UINT w2;
	UINT w3;
}; // end struct WTCOptions

std::wostream &operator<<(std::wostream &wout, const WTCOptions &options)
{
	wout << options.indent << left << setw(options.w1) << L"Option" << right << setw(options.w2) << L"Value" << L"\n";
	wout << options.indent << left << setw(options.w1) << L"CXO_SYSTEM" << right << setw(options.w2) << bool(CXO_SYSTEM&options.o)
		<< Indent(options.w3) << L"Specifies that the context is a system cursor context." << L"\n";
	wout << options.indent << left << setw(options.w1) << L"CXO_PEN" << right << setw(options.w2) << bool(CXO_PEN&options.o)
		<< Indent(options.w3) << L"Specifies that the context is a Pen Windows context, if Pen Windows is installed. The context is also a system cursor context; specifying CXO_PEN implies CXO_SYSTEM." << L"\n";
	wout << options.indent << left << setw(options.w1) << L"CXO_MESSAGES" << right << setw(options.w2) << bool(CXO_MESSAGES&options.o)
		<< Indent(options.w3) << L"Specifies that the context returns WT_PACKET messages to its owner." << L"\n";
	wout << options.indent << left << setw(options.w1) << L"CXO_MARGIN" << right << setw(options.w2) << bool(CXO_MARGIN&options.o)
		<< Indent(options.w3) << L"Specifies that the input context on the tablet will have a margin. The margin is an area outside the specified input area where events will be mapped to the edge of the input area. This feature makes it easier to in­put points at the edge of the context." << L"\n";
	wout << options.indent << left << setw(options.w1) << L"CXO_MGNINSIDE" << right << setw(options.w2) << bool(CXO_MGNINSIDE&options.o)
		<< Indent(options.w3) << L"If the CXO_MARGIN bit is on, specifies that the margin will be inside the specified context. Thus, scaling will occur from a context slightly smaller than the specified input context to the output coordinate space." << L"\n";
	wout << options.indent << left << setw(options.w1) << L"CXO_CSRMESSAGES" << right << setw(options.w2) << bool(CXO_CSRMESSAGES&options.o)
		<< Indent(options.w3) << L"Specifies that the context returns WT_CSRCHANGE messages to it owner." << L"\n\n";
	return wout;
} // end function operator<<

struct WTDataMask
{
	WTDataMask(WTPKT mask,Indent indentation,UINT cw1,UINT cw2,UINT cw3,WORD version)
		:m(mask),indent(indentation),w1(cw1),w2(cw2),w3(cw3),iVersion(version){}

	WTPKT m;
	Indent indent;
	UINT w1;
	UINT w2;
	UINT w3;
	WORD iVersion;
}; // end struct WTDataMask

std::wostream &operator<<(std::wostream &wout, const WTDataMask &mask)
{
	wout << mask.indent << left << setw(mask.w1) << L"Flag" << right << setw(mask.w2) << L"Value" << L"\n";
	wout << mask.indent << left << setw(mask.w1) << L"PK_CONTEXT" << right << setw(mask.w2) << bool(PK_CONTEXT&mask.m)
		<< Indent(mask.w3) << L"Specifies the handle of the reporting context." << L"\n";
	wout << mask.indent << left << setw(mask.w1) << L"PK_STATUS" << right << setw(mask.w2) << bool(PK_STATUS&mask.m)
		<< Indent(mask.w3) << L"Specifies status information." << L"\n";
	wout << mask.indent << left << setw(mask.w1) << L"PK_TIME" << right << setw(mask.w2) << bool(PK_TIME&mask.m)
		<< Indent(mask.w3) << L"Specifies the time at which the packet was generated." << L"\n";
	wout << mask.indent << left << setw(mask.w1) << L"PK_CHANGED" << right << setw(mask.w2) << bool(PK_CHANGED&mask.m)
		<< Indent(mask.w3) << L"Specifies which packet data items have changed since the last packet." << L"\n";
	wout << mask.indent << left << setw(mask.w1) << L"PK_SERIAL_NUMBER" << right << setw(mask.w2) << bool(PK_SERIAL_NUMBER&mask.m)
		<< Indent(mask.w3) << L"Specifies the packet serial number." << L"\n";
	wout << mask.indent << left << setw(mask.w1) << L"PK_CURSOR" << right << setw(mask.w2) << bool(PK_CURSOR&mask.m)
		<< Indent(mask.w3) << L"Specifies the cursor that generated the packet." << L"\n";
	wout << mask.indent << left << setw(mask.w1) << L"PK_BUTTONS" << right << setw(mask.w2) << bool(PK_BUTTONS&mask.m)
		<< Indent(mask.w3) << L"Specifies packet button information." << L"\n";
	wout << mask.indent << left << setw(mask.w1) << L"PK_X" << right << setw(mask.w2) << bool(PK_X&mask.m)
		<< Indent(mask.w3) << L"Specify packet x axis data." << L"\n";
	wout << mask.indent << left << setw(mask.w1) << L"PK_Y" << right << setw(mask.w2) << bool(PK_Y&mask.m)
		<< Indent(mask.w3) << L"Specify packet y axis data." << L"\n";
	wout << mask.indent << left << setw(mask.w1) << L"PK_Z" << right << setw(mask.w2) << bool(PK_Z&mask.m)
		<< Indent(mask.w3) << L"Specify packet z axis data." << L"\n";
	wout << mask.indent << left << setw(mask.w1) << L"PK_NORMAL_PRESSURE" << right << setw(mask.w2) << bool(PK_NORMAL_PRESSURE&mask.m)
		<< Indent(mask.w3) << L"Specify tip-button or normal-to-surface pressure data." << L"\n";
	wout << mask.indent << left << setw(mask.w1) << L"PK_TANGENT_PRESSURE" << right << setw(mask.w2) << bool(PK_TANGENT_PRESSURE&mask.m)
		<< Indent(mask.w3) << L"Specify barrel-button or tangent-to-surface pressure data." << L"\n";
	wout << mask.indent << left << setw(mask.w1) << L"PK_ORIENTATION" << right << setw(mask.w2) << bool(PK_ORIENTATION&mask.m)
		<< Indent(mask.w3) << L"Specifies cursor orientation information." << L"\n";
	if(mask.iVersion >= 0x0101)
		wout << mask.indent << left << setw(mask.w1) << L"PK_ROTATION" << right << setw(mask.w2) << bool(PK_ROTATION&mask.m)
			<< Indent(mask.w3) << L"Specifies cursor rotation information." << L"\n";
	wout << L"\n";
	return wout;
} // end function operator<<

struct WTCLocks
{
	WTCLocks(UINT locks,Indent indentation,UINT cw1,UINT cw2,UINT cw3)
		:l(locks),indent(indentation),w1(cw1),w2(cw2),w3(cw3){}

	UINT l;
	Indent indent;
	UINT w1;
	UINT w2;
	UINT w3;
}; // end struct WTCLocks

std::wostream &operator<<(std::wostream &wout, const WTCLocks &locks)
{
	wout << locks.indent << left << setw(locks.w1) << L"Lock" << right << setw(locks.w2) << L"Value" << L"\n";
	wout << locks.indent << left << setw(locks.w1) << L"CXL_INSIZE" << right << setw(locks.w2) << bool(CXL_INSIZE&locks.l)
		<< Indent(locks.w3) << L"Specifies that the context's input size cannot be changed. When this value is not specified, the context's input extents in x, y, and z can be changed. NOTE: The context's origins in x, y, and z can always be changed." << L"\n";
	wout << locks.indent << left << setw(locks.w1) << L"CXL_INASPECT" << right << setw(locks.w2) << bool(CXL_INASPECT&locks.l)
		<< Indent(locks.w3) << L"Specifies that the context's input aspect ratio cannot be changed. When this value is specified, the context's size can be changed, but the ratios among x, y, and z extents will be kept as close to constant as possible." << L"\n";
	wout << locks.indent << left << setw(locks.w1) << L"CXL_MARGIN" << right << setw(locks.w2) << bool(CXL_MARGIN&locks.l)
		<< Indent(locks.w3) << L"Specifies that the context's margin options cannot be changed. This value controls the locking of the CXO_MARGIN and CXO_MGNINSIDE option values." << L"\n";
	wout << locks.indent << left << setw(locks.w1) << L"CXL_SENSITIVITY" << right << setw(locks.w2) << bool(CXL_SENSITIVITY&locks.l)
		<< Indent(locks.w3) << L"Specifies that the context's sensitivity settings for x, y, and z cannot be changed." << L"\n";
	wout << locks.indent << left << setw(locks.w1) << L"CXL_SYSOUT" << right << setw(locks.w2) << bool(CXL_SYSOUT&locks.l)
		<< Indent(locks.w3) << L"If the context is a system cursor context, the value specifies that the sys­tem pointing control variables of the context cannot be changed." << L"\n";
	wout << L"\n";
	return wout;
} // end function operator<<

struct WTCStatus
{
	WTCStatus(UINT status,Indent indentation,UINT cw1,UINT cw2,UINT cw3)
		:s(status),indent(indentation),w1(cw1),w2(cw2),w3(cw3){}

	UINT s;
	Indent indent;
	UINT w1;
	UINT w2;
	UINT w3;
}; // end struct WTCStatus

std::wostream &operator<<(std::wostream &wout, const WTCStatus &status)
{
	wout << status.indent << left << setw(status.w1) << L"Flag" << right << setw(status.w2) << L"Value" << L"\n";
	wout << status.indent << left << setw(status.w1) << L"CXS_DISABLED" << right << setw(status.w2) << bool(CXS_DISABLED&status.s)
		<< Indent(status.w3) << L"Specifies that the context has been disabled using the WTEnable function." << L"\n";
	wout << status.indent << left << setw(status.w1) << L"CXS_OBSCURED" << right << setw(status.w2) << bool(CXS_OBSCURED&status.s)
		<< Indent(status.w3) << L"Specifies that the context is at least partially obscured by an overlapping con­text that is higher in the context overlap order." << L"\n";
	wout << status.indent << left << setw(status.w1) << L"CXS_ONTOP" << right << setw(status.w2) << bool(CXS_ONTOP&status.s)
		<< Indent(status.w3) << L"Specifies that the context is the topmost context in the context overlap order." << L"\n";
	wout << L"\n";
	return wout;
} // end function operator<<

struct ExtLogContext 
{
	ExtLogContext(Indent indentation,UINT cw1,UINT cw2,UINT cw3,WORD version,Indent subIndent,UINT scw1,UINT scw2,UINT scw3)
		:indent(indentation),w1(cw1),w2(cw2),w3(cw3),iVersion(version),sIndent(subIndent),sw1(scw1),sw2(scw2),sw3(scw3){}

	LOGCONTEXTW c;
	Indent indent;
	Indent sIndent;
	UINT w1;
	UINT w2;
	UINT w3;
	UINT sw1;
	UINT sw2;
	UINT sw3;
	WORD iVersion;
}; // end struct ExtLogContext

std::wostream &operator<<(std::wostream &wout, const ExtLogContext &context)
{
	std::wostringstream wsout;
	wout << context.indent << left << setw(context.w1) << L"Index" << right << setw(context.w2) << L"Value" << L"\n";
	wout << context.indent << left << setw(context.w1) << L"CTX_NAME" << right << setw(context.w2) << context.c.lcName
		<< Indent(context.w3) << L"Returns a 40 character array containing the default name. The name may occupy zero to 39 characters; the remainder of the array is padded with zeroes." << L"\n";
	wout << context.indent << left << setw(context.w1) << L"CTX_OPTIONS" << right << setw(context.w2) << bitset<32>(context.c.lcOptions)
		<< Indent(context.w3) << L"Returns option flags. For the default digitizing context, CXO_MARGIN and CXO_MGNINSIDE are allowed. For the default system context, CXO_SYSTEM is required; CXO_PEN, CXO_MARGIN, and CXO_MGNINSIDE are allowed." << L"\n";
	wout << WTCOptions(context.c.lcOptions,context.sIndent,context.sw1,context.sw2,context.sw3);
	wout << context.indent << left << setw(context.w1) << L"CTX_STATUS" << right << setw(context.w2) << bitset<32>(context.c.lcStatus)
		<< Indent(context.w3) << L"Returns zero." << L"\n";
	wout << WTCStatus(context.c.lcStatus,context.sIndent,context.sw1,context.sw2,context.sw3);
	wout << context.indent << left << setw(context.w1) << L"CTX_LOCKS" << right << setw(context.w2) << bitset<32>(context.c.lcLocks)
		<< Indent(context.w3) << L"Returns which attributes of the default context are locked." << L"\n";
	wout << WTCLocks(context.c.lcLocks,context.sIndent,context.sw1,context.sw2,context.sw3);
	wsout << L"0x" << std::hex << std::uppercase << std::setfill(L'0') << setw(2*sizeof(UINT)) << context.c.lcMsgBase;
	wout << context.indent << left << setw(context.w1) << L"CTX_MSGBASE" << right << setw(context.w2) << wsout.str()
		<< Indent(context.w3) << L"Returns the value WT_DEFBASE." << L"\n";
	wout << context.indent << left << setw(context.w1) << L"CTX_DEVICE" << right << setw(context.w2) << (INT)context.c.lcDevice
		<< Indent(context.w3) << L"Returns the default device.  If this value is -1, then it also known as a \"virtual device\"." << L"\n";
	wout << context.indent << left << setw(context.w1) << L"CTX_PKTRATE" << right << setw(context.w2) << context.c.lcPktRate
		<< Indent(context.w3) << L"Returns the default context packet report rate, in Hertz." << L"\n";
	wout << context.indent << left << setw(context.w1) << L"CTX_PKTDATA" << right << setw(context.w2) << bitset<32>(context.c.lcPktData)
		<< Indent(context.w3) << L"Returns which optional data items will be in packets returned from the context. For the default digitizing context, this field must at least indicate buttons, x, and y data." << L"\n";
	wout << WTDataMask(context.c.lcPktData,context.sIndent,context.sw1,context.sw2,context.sw3,context.iVersion);
	wout << context.indent << left << setw(context.w1) << L"CTX_PKTMODE" << right << setw(context.w2) << bitset<32>(context.c.lcPktMode)
		<< Indent(context.w3) << L"Returns whether the packet data items will be returned in absolute or relative mode." << L"\n";
	wout << WTDataMask(context.c.lcPktMode,context.sIndent,context.sw1,context.sw2,context.sw3,context.iVersion);
	wout << context.indent << left << setw(context.w1) << L"CTX_MOVEMASK" << right << setw(context.w2) << bitset<32>(context.c.lcMoveMask)
		<< Indent(context.w3) << L"Returns which packet data items can generate motion events in the context." << L"\n";
	wout << WTDataMask(context.c.lcMoveMask,context.sIndent,context.sw1,context.sw2,context.sw3,context.iVersion);
	wout << context.indent << left << setw(context.w1) << L"CTX_BTNDNMASK" << right << setw(context.w2) << bitset<32>(context.c.lcBtnDnMask)
		<< Indent(context.w3) << L"Returns the buttons for which button press events will be processed in the context. The default context must at least select button press events for one button." << L"\n";
	wout << context.indent << left << setw(context.w1) << L"CTX_BTNUPMASK" << right << setw(context.w2) << bitset<32>(context.c.lcBtnUpMask)
		<< Indent(context.w3) << L"Returns the buttons for which button release events will be processed in the context." << L"\n";
	wout << context.indent << left << setw(context.w1) << L"CTX_INORGX" << right << setw(context.w2) << context.c.lcInOrgX
		<< Indent(context.w3) << L"Returns the origin of the context's input area in the tablet's native coordinates, along the x axis." << L"\n";
	wout << context.indent << left << setw(context.w1) << L"CTX_INORGY" << right << setw(context.w2) << context.c.lcInOrgY
		<< Indent(context.w3) << L"Returns the origin of the context's input area in the tablet's native coordinates, along the y axis." << L"\n";
	wout << context.indent << left << setw(context.w1) << L"CTX_INORGZ" << right << setw(context.w2) << context.c.lcInOrgZ
		<< Indent(context.w3) << L"Returns the origin of the context's input area in the tablet's native coordinates, along the z axis." << L"\n";
	wout << context.indent << left << setw(context.w1) << L"CTX_INEXTX" << right << setw(context.w2) << context.c.lcInExtX
		<< Indent(context.w3) << L"Returns the extent of the context's input area in the tablet's native coordinates, along the x axis." << L"\n";
	wout << context.indent << left << setw(context.w1) << L"CTX_INEXTY" << right << setw(context.w2) << context.c.lcInExtY
		<< Indent(context.w3) << L"Returns the extent of the context's input area in the tablet's native coordinates, along the y axis." << L"\n";
	wout << context.indent << left << setw(context.w1) << L"CTX_INEXTZ" << right << setw(context.w2) << context.c.lcInExtZ
		<< Indent(context.w3) << L"Returns the extent of the context's input area in the tablet's native coordinates, along the z axis." << L"\n";
	wout << context.indent << left << setw(context.w1) << L"CTX_OUTORGX" << right << setw(context.w2) << context.c.lcOutOrgX
		<< Indent(context.w3) << L"Returns the origin of the context's output coordinate space in context output coordinates, along the x axis." << L"\n";
	wout << context.indent << left << setw(context.w1) << L"CTX_OUTORGY" << right << setw(context.w2) << context.c.lcOutOrgY
		<< Indent(context.w3) << L"Returns the origin of the context's output coordinate space in context output coordinates, along the y axis." << L"\n";
	wout << context.indent << left << setw(context.w1) << L"CTX_OUTORGZ" << right << setw(context.w2) << context.c.lcOutOrgZ
		<< Indent(context.w3) << L"Returns the origin of the context's output coordinate space in context output coordinates, along the z axis." << L"\n";
	wout << context.indent << left << setw(context.w1) << L"CTX_OUTEXTX" << right << setw(context.w2) << context.c.lcOutExtX
		<< Indent(context.w3) << L"Returns the extent of the context's output coordinate space in context output coordinates, along the x axis." << L"\n";
	wout << context.indent << left << setw(context.w1) << L"CTX_OUTEXTY" << right << setw(context.w2) << context.c.lcOutExtY
		<< Indent(context.w3) << L"Returns the extent of the context's output coordinate space in context output coordinates, along the y axis." << L"\n";
	wout << context.indent << left << setw(context.w1) << L"CTX_OUTEXTZ" << right << setw(context.w2) << context.c.lcOutExtZ
		<< Indent(context.w3) << L"Returns the extent of the context's output coordinate space in context output coordinates, along the z axis." << L"\n";
	wout << context.indent << left << setw(context.w1) << L"CTX_SENSX" << right << setw(context.w2) << toFloatingPoint(context.c.lcSensX)
		<< Indent(context.w3) << L"Returns the relative-mode sensitivity factor, along the x axis." << L"\n";
	wout << context.indent << left << setw(context.w1) << L"CTX_SENSY" << right << setw(context.w2) << toFloatingPoint(context.c.lcSensY)
		<< Indent(context.w3) << L"Returns the relative-mode sensitivity factor, along the y axis." << L"\n";
	wout << context.indent << left << setw(context.w1) << L"CTX_SENSZ" << right << setw(context.w2) << toFloatingPoint(context.c.lcSensZ)
		<< Indent(context.w3) << L"Returns the relative-mode sensitivity factor, along the z axis." << L"\n";
	wout << context.indent << left << setw(context.w1) << L"CTX_SYSMODE" << right << setw(context.w2) << context.c.lcSysMode
		<< Indent(context.w3) << L"Returns the default system cursor tracking mode." << L"\n";
	wout << context.indent << left << setw(context.w1) << L"CTX_SYSORGX" << right << setw(context.w2) << context.c.lcSysOrgX
		<< Indent(context.w3) << L"Returns 0." << L"\n";
	wout << context.indent << left << setw(context.w1) << L"CTX_SYSORGY" << right << setw(context.w2) << context.c.lcSysOrgY
		<< Indent(context.w3) << L"Returns 0." << L"\n";
	wout << context.indent << left << setw(context.w1) << L"CTX_SYSEXTX" << right << setw(context.w2) << context.c.lcSysExtX
		<< Indent(context.w3) << L"Returns the current screen display size in pixels, in the x direction." << L"\n";
	wout << context.indent << left << setw(context.w1) << L"CTX_SYSEXTY" << right << setw(context.w2) << context.c.lcSysExtY
		<< Indent(context.w3) << L"Returns the current screen display size in pixels, in the y direction." << L"\n";
	wout << context.indent << left << setw(context.w1) << L"CTX_SYSSENSX" << right << setw(context.w2) << toFloatingPoint(context.c.lcSysSensX)
		<< Indent(context.w3) << L"Returns the system cursor relative-mode sensitivity factor, in the x direction." << L"\n";
	wout << context.indent << left << setw(context.w1) << L"CTX_SYSSENSY" << right << setw(context.w2) << toFloatingPoint(context.c.lcSysSensY)
		<< Indent(context.w3) << L"Returns the system cursor relative-mode sensitivity factor, in the y direction." << L"\n";
	wout << L"\n";
	return wout;
} // end function operator<<


struct WTDevice	// this is not a class to export in a library! naming, members, types are lousy!
{
	//enum Capabilities{INTEGRATED,TOUCH,HARDPROX,PHYSID_CURSORS};

	wstring name;
	UINT capabilities;
	unsigned int nCursorTypes;
	unsigned int firstCursor;
	unsigned int reportRate;
	WTPKT packetData;
	WTPKT packetMode;
	WTPKT cursorData;
	int xMargin;
	int yMargin;
	int zMargin;
	AXIS x;
	AXIS y;
	AXIS z;
	AXIS nPressure;
	AXIS tPressure;
	AXIS azimuth;
	AXIS altitude;
	AXIS twist;
	AXIS pitch;
	AXIS roll;
	AXIS yaw;
	wstring plugAndPlayID;

	WORD iVersion;

	WTDevice(unsigned int deviceIndex,WORD version)
	{
		AXIS axes[3];
		unique_ptr<char[]> buffer;
		unsigned int buffer_size;

		iVersion = version;

		buffer_size = WTInfoW(WTI_DEVICES+deviceIndex,DVC_NAME,nullptr);
		buffer = unique_ptr<char[]>(new char[buffer_size]);
		WTInfoW(WTI_DEVICES+deviceIndex,DVC_NAME,buffer.get());
		name = (wchar_t*)buffer.get();
		
		WTInfoW(WTI_DEVICES+deviceIndex,DVC_HARDWARE,&capabilities);
		WTInfoW(WTI_DEVICES+deviceIndex,DVC_NCSRTYPES,&nCursorTypes);
		WTInfoW(WTI_DEVICES+deviceIndex,DVC_FIRSTCSR,&firstCursor);
		WTInfoW(WTI_DEVICES+deviceIndex,DVC_PKTRATE,&reportRate);
		WTInfoW(WTI_DEVICES+deviceIndex,DVC_PKTDATA,&packetData);
		WTInfoW(WTI_DEVICES+deviceIndex,DVC_PKTMODE,&packetMode);
		WTInfoW(WTI_DEVICES+deviceIndex,DVC_CSRDATA,&cursorData);
		WTInfoW(WTI_DEVICES+deviceIndex,DVC_XMARGIN,&xMargin);
		WTInfoW(WTI_DEVICES+deviceIndex,DVC_YMARGIN,&yMargin);
		WTInfoW(WTI_DEVICES+deviceIndex,DVC_ZMARGIN,&zMargin);
		WTInfoW(WTI_DEVICES+deviceIndex,DVC_X,&x);
		WTInfoW(WTI_DEVICES+deviceIndex,DVC_Y,&y);
		WTInfoW(WTI_DEVICES+deviceIndex,DVC_Z,&z);
		WTInfoW(WTI_DEVICES+deviceIndex,DVC_NPRESSURE,&nPressure);
		WTInfoW(WTI_DEVICES+deviceIndex,DVC_TPRESSURE,&tPressure);
		WTInfoW(WTI_DEVICES+deviceIndex,DVC_ORIENTATION,axes);
		azimuth = axes[0];
		altitude = axes[1];
		twist = axes[2];
		if(iVersion >= 0x0101)
		{
			WTInfoW(WTI_DEVICES+deviceIndex,DVC_ROTATION,&axes);
			pitch = axes[0];
			roll = axes[1];
			yaw = axes[2];

			buffer_size = WTInfoW(WTI_DEVICES+deviceIndex,DVC_PNPID,nullptr);
			buffer = unique_ptr<char[]>(new char[buffer_size]);
			WTInfoW(WTI_DEVICES+deviceIndex,DVC_PNPID,buffer.get());
			plugAndPlayID = (wchar_t*)buffer.get();
		} // end if
	} // end Device constructotr	
}; // end struct WTDevice

struct ExtWTDevice : public WTDevice	// extra information for printing
{
	Indent indent;
	Indent sIndent;
	UINT w1;
	UINT w2;
	UINT w3;
	UINT sw1;
	UINT sw2;
	UINT sw3;

	ExtWTDevice(unsigned int deviceIndex,WORD version,Indent indentation,UINT cw1,UINT cw2,UINT cw3,Indent subIndent,UINT scw1,UINT scw2,UINT scw3)
		:WTDevice(deviceIndex,version),indent(indentation),w1(cw1),w2(cw2),w3(cw3),sIndent(subIndent),sw1(scw1),sw2(scw2),sw3(scw3){}
}; // end ExtWTDevice

struct WTDCapabilities
{
	WTDCapabilities(UINT capabilities,Indent indentation,UINT cw1,UINT cw2,UINT cw3,WORD version)
		:c(capabilities),indent(indentation),w1(cw1),w2(cw2),w3(cw3),iVersion(version){}

	UINT c;
	Indent indent;
	UINT w1;
	UINT w2;
	UINT w3;
	WORD iVersion;
}; // end struct WTDCapabilities

std::wostream &operator<<(std::wostream &wout, const WTDCapabilities &capabilities)
{
	wout << capabilities.indent << left << setw(capabilities.w1) << L"Capability" << right << setw(capabilities.w2) << L"Value" << L"\n";
	wout << capabilities.indent << left << setw(capabilities.w1) << L"HWC_INTEGRATED" << right << setw(capabilities.w2) << bool(HWC_INTEGRATED&capabilities.c)
		<< Indent(capabilities.w3) << L"Indicates that the display and digitizer share the same surface." << L"\n";
	wout << capabilities.indent << left << setw(capabilities.w1) << L"HWC_TOUCH" << right << setw(capabilities.w2) << bool(HWC_TOUCH&capabilities.c)
		<< Indent(capabilities.w3) << L"Indicates that the cursor must be in physical contact with the device to report position." << L"\n";
	wout << capabilities.indent << left << setw(capabilities.w1) << L"HWC_HARDPROX" << right << setw(capabilities.w2) << bool(HWC_HARDPROX&capabilities.c)
		<< Indent(capabilities.w3) << L"Indicates that device can generate events when the cursor is entering and leaving the physical detection range." << L"\n";
	if(capabilities.iVersion >= 0x0101)
	{
		wout << capabilities.indent << left << setw(capabilities.w1) << L"HWC_PHYSID_CURSORS" << right << setw(capabilities.w2) << bool(HWC_PHYSID_CURSORS&capabilities.c)
			<< Indent(capabilities.w3) << L"Indicates that device can uniquely identify the active cursor in hardware." << L"\n";
	} // end if
	wout << L"\n";
	return wout;
} // end function operator<<

std::wostream &operator<<(std::wostream &wout, const AXIS &axis)
{
	wstringstream wsout;
	wsout << axis.axMin << L".." << axis.axMax << L" @ ";
	if(axis.axUnits == TU_NONE)
		wsout << L"no units";
	else
	{
		wsout << toFloatingPoint(axis.axResolution) << L'/';
		switch(axis.axUnits)
		{
		case TU_INCHES:
			wsout << L"inch";
			break;
		case TU_CENTIMETERS:
			wsout << L"cm";
			break;
		case TU_CIRCLE:
			wsout << L"cycle";
			break;
		} // end switch
	} // end else
	wout << wsout.str();
	return wout;
} // end function operator<<

std::wostream &operator<<(std::wostream &wout, const ExtWTDevice &device)
{
	wout << device.indent << left << setw(device.w1) << L"Index" << right << setw(device.w2) << L"Value" << L"\n";
	wout << device.indent << left << setw(device.w1) << L"DVC_NAME" << right << setw(device.w2) << device.name
		<< Indent(device.w3) << L"Returns a displayable null- terminated string describing the device, manufacturer, and revision level." << L"\n";
	wout << device.indent << left << setw(device.w1) << L"DVC_HARDWARE" << right << setw(device.w2) << bitset<32>(device.capabilities)
		<< Indent(device.w3) << L"Returns flags indicating hardware and driver capabilities, as defined below:" << L"\n";
	wout << WTDCapabilities(device.capabilities,device.sIndent,device.sw1,device.sw2,device.sw3,device.iVersion);
	wout << device.indent << left << setw(device.w1) << L"DVC_NCSRTYPES" << right << setw(device.w2) << device.nCursorTypes
		<< Indent(device.w3) << L"Returns the number of supported cursor types." << L"\n";
	wout << device.indent << left << setw(device.w1) << L"DVC_FIRSTCSR" << right << setw(device.w2) << device.firstCursor
		<< Indent(device.w3) << L"Returns the first cursor type number for the device." << L"\n";
	wout << device.indent << left << setw(device.w1) << L"DVC_PKTRATE" << right << setw(device.w2) << device.reportRate
		<< Indent(device.w3) << L"Returns the maximum packet report rate in Hertz." << L"\n";
	wout << device.indent << left << setw(device.w1) << L"DVC_PKTDATA" << right << setw(device.w2) << bitset<32>(device.packetData)
		<< Indent(device.w3) << L"Returns a bit mask indicating which packet data items are always available." << L"\n";
	wout << WTDataMask(device.packetData,device.sIndent,device.sw1,device.sw2,device.sw3,device.iVersion);
	wout << device.indent << left << setw(device.w1) << L"DVC_PKTMODE" << right << setw(device.w2) << bitset<32>(device.packetMode)
		<< Indent(device.w3) << L"Returns a bit mask indicating which packet data items are physically relative, i.e., items for which the hardware can only report change, not absolute measurement." << L"\n";
	wout << WTDataMask(device.packetMode,device.sIndent,device.sw1,device.sw2,device.sw3,device.iVersion);
	wout << device.indent << left << setw(device.w1) << L"DVC_CSRDATA" << right << setw(device.w2) << bitset<32>(device.cursorData)
		<< Indent(device.w3) << L"Returns a bit mask indicating which packet data items are only available when certain cursors are connected. The individual cursor descriptions must be consulted to determine which cursors return which data." << L"\n";
	wout << WTDataMask(device.cursorData,device.sIndent,device.sw1,device.sw2,device.sw3,device.iVersion);
	wout << device.indent << left << setw(device.w1) << L"DVC_XMARGIN" << right << setw(device.w2) << device.xMargin
		<< Indent(device.w3) << L"Returns the size of tablet context margins in tablet native coordinates, in the x direction." << L"\n";
	wout << device.indent << left << setw(device.w1) << L"DVC_YMARGIN" << right << setw(device.w2) << device.yMargin
		<< Indent(device.w3) << L"Returns the size of tablet context margins in tablet native coordinates, in the y direction." << L"\n";
	wout << device.indent << left << setw(device.w1) << L"DVC_ZMARGIN" << right << setw(device.w2) << device.zMargin
		<< Indent(device.w3) << L"Returns the size of tablet context margins in tablet native coordinates, in the z direction." << L"\n";
	wout << device.indent << left << setw(device.w1) << L"DVC_X" << right << setw(device.w2) << device.x
		<< Indent(device.w3) << L"Returns the tablet's range and resolution capabilities, in the x axis." << L"\n";
	wout << device.indent << left << setw(device.w1) << L"DVC_Y" << right << setw(device.w2) << device.y
		<< Indent(device.w3) << L"Returns the tablet's range and resolution capabilities, in the y axis." << L"\n";
	wout << device.indent << left << setw(device.w1) << L"DVC_Z" << right << setw(device.w2) << device.z
		<< Indent(device.w3) << L"Returns the tablet's range and resolution capabilities, in the z axis." << L"\n";
	wout << device.indent << left << setw(device.w1) << L"DVC_NPRESSURE" << right << setw(device.w2) << device.nPressure
		<< Indent(device.w3) << L"Returns the tablet's range and resolution capabilities, for the normal pressure input." << L"\n";
	wout << device.indent << left << setw(device.w1) << L"DVC_TPRESSURE" << right << setw(device.w2) << device.tPressure
		<< Indent(device.w3) << L"Returns the tablet's range and resolution capabilities, for the tangential pressure input." << L"\n";
	wout << device.indent << left << setw(device.w1) << L"DVC_ORIENTATION" << right << setw(device.w2) << L""
		<< Indent(device.w3) << L"Returns a 3-element array describing the tablet's orientation range and resolution capabilities." << L"\n";
	wout << Indent(device.indent.size+4) << left << setw(device.w1-4) << L"azimuth" << right << setw(device.w2) << device.azimuth
		<< Indent(device.w3) << L"Specifies the clockwise rotation of the cursor about the z axis through a full circular range." << L"\n";
	wout << Indent(device.indent.size+4) << left << setw(device.w1-4) << L"altitude" << right << setw(device.w2) << device.altitude
		<< Indent(device.w3) << L"Specifies the angle with the x-y plane through a signed, semicir­cular range.  Positive values specify an angle upward toward the positive z axis; negative values specify an angle downward toward the negative z axis." << L"\n";
	wout << Indent(device.indent.size+4) << left << setw(device.w1-4) << L"twist" << right << setw(device.w2) << device.twist
		<< Indent(device.w3) << L"Specifies the clockwise rotation of the cursor about its own major axis." << L"\n";
	if(device.iVersion >= 0x0101)
	{
		wout << device.indent << left << setw(device.w1) << L"DVC_ROTATION" << right << setw(device.w2) << L""
			<< Indent(device.w3) << L"Returns a 3-element array describing the tablet's rotation range and resolution capabilities." << L"\n";
		wout << Indent(device.indent.size+4) << left << setw(device.w1-4) << L"pitch" << right << setw(device.w2) << device.pitch
			<< Indent(device.w3) << L"Specifies the pitch of the cursor." << L"\n";
		wout << Indent(device.indent.size+4) << left << setw(device.w1-4) << L"roll" << right << setw(device.w2) << device.roll
			<< Indent(device.w3) << L"Specifies the roll of the cursor." << L"\n";
		wout << Indent(device.indent.size+4) << left << setw(device.w1-4) << L"yaw" << right << setw(device.w2) << device.yaw
			<< Indent(device.w3) << L"Specifies the yaw of the cursor." << L"\n";
		wout << device.indent << left << setw(device.w1) << L"DVC_PNPID" << right << setw(device.w2) << device.plugAndPlayID
			<< Indent(device.w3) << L"Returns a null-terminated string containing the device's Plug and Play ID." << L"\n";
	} // end if
	wout << L"\n";
	return wout;
} // end function operator<<
