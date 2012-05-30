struct Error	// what about &&?
{
	Error(const wstring & msg)
		:message(msg){}

	wstring message;
};

std::wostream &operator<<(std::wostream &wout,const Error &error)
{
	wchar_t *error_message;
	FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS,
					nullptr,GetLastError(),0,(LPWSTR)&error_message,0,nullptr);
	wout << error.message << error_message;
	LocalFree(error_message);
	return wout;
} // end function operator<<
