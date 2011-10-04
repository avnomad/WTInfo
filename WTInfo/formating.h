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

std::wostream &operator<<(std::wostream &wout,const Indent &indent)
{
	wout << setw(indent.size) << L"";
	return wout;
} // end function operator<<