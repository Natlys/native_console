#ifndef NC_ALGORITHM_H
#define NC_ALGORITHM_H

#include <nc_pch.hpp>

namespace NC
{
	template<typename ArrType, typename IterType, typename ObjType>
	inline IterType& FindById(ArrType& rContainer, UInt32 unId) {
		return std::find_if(rContainer.begin(), rContainer.end(),
			[=](ObjType* pObj)->bool {return pObj->GetId() == unId; });
	}
}

#define FIND_BY_FUNC(Containter, ObjType, val, func) std::find_if(Containter.begin(), Containter.end(),	\
	[=](ObjType Obj)->bool{ return Obj func() == val; });
#define FIND_BY_FUNC_NAME(Containter, ObjType, val, func) std::find_if(Containter.begin(), Containter.end(),	\
	[=](ObjType Obj)->bool{ return strcmp(Obj func(), val) == 0; });

#endif	// NC_ALGORITHM_H