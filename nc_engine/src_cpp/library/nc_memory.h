#ifndef NC_MEMORY_H
#define NC_MEMORY_H

#include <nc_core.hpp>

namespace NC
{
	template <typename RefType> using RefOwner = std::unique_ptr<RefType>;
	template <typename RefType> using RefKeeper = std::shared_ptr<RefType>;

	using Byte = char;
}

#endif	// NC_MEMORY_H