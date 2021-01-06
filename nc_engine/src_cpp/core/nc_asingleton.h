#ifndef NC_ASINGLETON_H
#define NC_ASINGLETON_H

#include <nc_core.hpp>

namespace NC
{
	template <class CType>
	class NC_API ASingleton
	{
	protected:
		ASingleton() = default;
		ASingleton(ASingleton& rCpy) = delete;
		void operator=(ASingleton& rCpy) = delete;
	public:
		virtual ~ASingleton() = default;

		static inline CType& Get() { static CType s_Single; return s_Single; }
	};
}

#endif	// NC_ASINGLETON_H