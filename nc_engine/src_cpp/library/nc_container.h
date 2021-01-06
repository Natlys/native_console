#ifndef NC_CONTAINTER_H
#define NC_CONTAINTER_H

#include <nc_core.hpp>

namespace NC
{
	template <typename ValType, size_t szCount> using SArray = std::array<ValType, szCount>;
	template <typename ValType> using DArray = std::vector<ValType>;
	template <typename ValType> using DStack = std::stack<ValType>;
}

#endif	// NC_CONTAINTER_H