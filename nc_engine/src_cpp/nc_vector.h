#ifndef NC_VECTOR_H
#define NC_VECTOR_H

#include <nc_core.hpp>

namespace NC
{
	/// Vector2d struct
	template <typename ValType> struct NC_API Vector2
	{
	public:
		ValType x, y;
	public:
		Vector2() :
			x(ValType()), y(ValType()) {}
		Vector2(ValType value) :
			x(value), y(value) {}
	};

	using V2i8 = Vector2<Int8>;
	using V2i16 = Vector2<Int16>;
	using V2i32 = Vector2<Int32>;
	using V2i64 = Vector2<Int64>;

	using V2ui8 = Vector2<UInt8>;
	using V2ui16 = Vector2<UInt16>;
	using V2ui32 = Vector2<UInt32>;
	using V2ui64 = Vector2<UInt64>;

	using V2f32 = Vector2<Float32>;
	using V2f64 = Vector2<Float64>;
	using V2f128 = Vector2<Float128>;
}

#endif	// NC_VECTOR_H