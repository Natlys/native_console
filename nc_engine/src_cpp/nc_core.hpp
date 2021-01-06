#ifndef NC_CORE_HPP
#define NC_CORE_HPP
/// The main header of configurations and definitions

namespace NC
{
	//
}

#if (defined NC_BUILD_LIB)
#define NC_API __declspec(dllexport)
#elif (defined NC_BUILD_EXE)
#define NC_API __declspec(dllimport)
#else
#define NC_API
#endif	// NC_BUILD

#endif	// NC_CORE_HPP

#include <core/nc_def.hpp>