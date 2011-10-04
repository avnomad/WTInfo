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
	wout << options.indent << left << setw(options.w1) << L"Flag" << right << setw(options.w2) << L"Value" << L"\n";
	wout << options.indent << left << setw(options.w1) << L"CXO_SYSTEM" << right << setw(options.w2) << bool(CXO_SYSTEM&options.o)
		<< Indent(options.w3) << L"Specifies that the context is a system cursor context." << L"\n";
	wout << options.indent << left << setw(options.w1) << L"CXO_PEN" << right << setw(options.w2) << bool(CXO_PEN&options.o)
		<< Indent(options.w3) << L"Specifies that the context is a Pen Windows context, if Pen Windows is in­stalled. The context is also a system cursor context; specifying CXO_PEN implies CXO_SYSTEM." << L"\n";
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
}; // end struct WTCOptions

std::wostream &operator<<(std::wostream &wout, const WTDataMask &mask)
{
	wout << mask.indent << left << setw(mask.w1) << L"Flag" << right << setw(mask.w2) << L"Value" << L"\n";
	wout << mask.indent << left << setw(mask.w1) << L"PK_CONTEXT" << right << setw(mask.w2) << bool(PK_CONTEXT&mask.m)
		<< Indent(mask.w3) << L"Specifies the handle of the reporting con­text." << L"\n";
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
		<< Indent(mask.w3) << L"Specify barrel-button or tan­gent-to-surface pressure data." << L"\n";
	wout << mask.indent << left << setw(mask.w1) << L"PK_ORIENTATION" << right << setw(mask.w2) << bool(PK_ORIENTATION&mask.m)
		<< Indent(mask.w3) << L"Specifies cursor orientation informa­tion." << L"\n";
	if(mask.iVersion >= 0x0101) 
		wout << mask.indent << left << setw(mask.w1) << L"PK_ROTATION" << right << setw(mask.w2) << bool(PK_ROTATION&mask.m)
			<< Indent(mask.w3) << L"Specifies cursor rotation informa­tion." << L"\n";
	wout << L"\n";
	return wout;
} // end function operator<<

