//	Copyright (C) 2011-2012 Vaptistis Anogeianakis <el05208@mail.ntua.gr>
/*
 *	This file is part of WTInfo.
 *
 *	WTInfo is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	WTInfo is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with WTInfo.  If not, see <http://www.gnu.org/licenses/>.
 */

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
