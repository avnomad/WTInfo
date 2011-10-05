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

wstring toBinary(UINT number)
{
	wstring s;
	const UINT bits = 8*sizeof(UINT);
	const UINT mask = 1 << bits-1;

	for(UINT c = 0 ; c < bits ; ++c)
	{
		s.push_back((number&mask)?L'1':L'0');
		number <<= 1;
	} // end for
	return s;
} // end function toBinary

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
	wout << context.indent << left << setw(context.w1) << L"Flag" << right << setw(context.w2) << L"Value" << L"\n";
	wout << context.indent << left << setw(context.w1) << L"CTX_NAME" << right << setw(context.w2) << context.c.lcName
		<< Indent(context.w3) << L"Returns a 40 character array containing the default name. The name may occupy zero to 39 characters; the remainder of the array is padded with zeroes." << L"\n";
	wout << context.indent << left << setw(context.w1) << L"CTX_OPTIONS" << right << setw(context.w2) << toBinary(context.c.lcOptions)
		<< Indent(context.w3) << L"Returns option flags. For the default digitizing context, CXO_MARGIN and CXO_MGNINSIDE are allowed. For the default system context, CXO_SYSTEM is required; CXO_PEN, CXO_MARGIN, and CXO_MGNINSIDE are allowed." << L"\n";
	wout << WTCOptions(context.c.lcOptions,context.sIndent,context.sw1,context.sw2,context.sw3);
	wout << context.indent << left << setw(context.w1) << L"CTX_STATUS" << right << setw(context.w2) << toBinary(context.c.lcStatus)
		<< Indent(context.w3) << L"Returns zero." << L"\n";
	wout << WTCStatus(context.c.lcStatus,context.sIndent,context.sw1,context.sw2,context.sw3);
	wout << context.indent << left << setw(context.w1) << L"CTX_LOCKS" << right << setw(context.w2) << toBinary(context.c.lcLocks)
		<< Indent(context.w3) << L"Returns which attributes of the default context are locked." << L"\n";
	wout << WTCLocks(context.c.lcLocks,context.sIndent,context.sw1,context.sw2,context.sw3);
	wsout << L"0x" << std::hex << std::uppercase << std::setfill(L'0') << setw(2*sizeof(UINT)) << context.c.lcMsgBase;
	wout << context.indent << left << setw(context.w1) << L"CTX_MSGBASE" << right << setw(context.w2) << wsout.str()
		<< Indent(context.w3) << L"Returns the value WT_DEFBASE." << L"\n";
	wout << context.indent << left << setw(context.w1) << L"CTX_DEVICE" << right << setw(context.w2) << (INT)context.c.lcDevice
		<< Indent(context.w3) << L"Returns the default device.  If this value is -1, then it also known as a \"virtual device\"." << L"\n";
	wout << context.indent << left << setw(context.w1) << L"CTX_PKTRATE" << right << setw(context.w2) << context.c.lcPktRate
		<< Indent(context.w3) << L"Returns the default context packet report rate, in Hertz." << L"\n";
	wout << context.indent << left << setw(context.w1) << L"CTX_PKTDATA" << right << setw(context.w2) << toBinary(context.c.lcPktData)
		<< Indent(context.w3) << L"Returns which optional data items will be in packets returned from the context. For the default digitizing context, this field must at least indicate buttons, x, and y data." << L"\n";
	wout << WTDataMask(context.c.lcPktData,context.sIndent,context.sw1,context.sw2,context.sw3,context.iVersion);
	wout << context.indent << left << setw(context.w1) << L"CTX_PKTMODE" << right << setw(context.w2) << toBinary(context.c.lcPktMode)
		<< Indent(context.w3) << L"Returns whether the packet data items will be returned in absolute or relative mode." << L"\n";
	wout << WTDataMask(context.c.lcPktMode,context.sIndent,context.sw1,context.sw2,context.sw3,context.iVersion);
	wout << context.indent << left << setw(context.w1) << L"CTX_MOVEMASK" << right << setw(context.w2) << toBinary(context.c.lcMoveMask)
		<< Indent(context.w3) << L"Returns which packet data items can generate motion events in the context." << L"\n";
	wout << WTDataMask(context.c.lcMoveMask,context.sIndent,context.sw1,context.sw2,context.sw3,context.iVersion);
	wout << context.indent << left << setw(context.w1) << L"CTX_BTNDNMASK" << right << setw(context.w2) << toBinary(context.c.lcBtnDnMask)
		<< Indent(context.w3) << L"Returns the buttons for which button press events will be processed in the context. The default context must at least select button press events for one button." << L"\n";
	wout << context.indent << left << setw(context.w1) << L"CTX_BTNUPMASK" << right << setw(context.w2) << toBinary(context.c.lcBtnUpMask)
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
