#ifndef NC_NUMBER_H
#define NC_NUMBER_H

#include <nc_core.hpp>

namespace NC
{
	using Int8 = __int8;
	using Int16 = __int16;
	using Int32 = __int32;
	using Int64 = __int64;
	
	using UInt8 = unsigned __int8;
	using UInt16 = unsigned __int16;
	using UInt32 = unsigned __int32;
	using UInt64 = unsigned __int64;

	using Float32 = float;
	using Float64 = double;
	using Float128 = long double;
}

#endif	// NC_NUMBER_H