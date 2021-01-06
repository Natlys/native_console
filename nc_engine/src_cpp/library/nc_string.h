#ifndef NC_STRING_H
#define NC_STRING_H

#include <nc_core.hpp>

namespace NC
{
	using String = std::basic_string<char, std::char_traits<char>, std::allocator<char>>;
	using WString = std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t>>;

	using Char = char;
	using WChar = wchar_t;
	using UChar = unsigned char;
}

#endif	// NC_STRING_H