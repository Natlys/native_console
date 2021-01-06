#ifndef NC_GSTRUCTS_H
#define NC_GSTRUCTS_H

#include <core/nc_adata_res.h>

#include <core/graphics_decl.hpp>

// Pixel
namespace NC
{
	/// Pixel structure
	/// Description:
	/// -- Represents color in rgba for float and unsigned integer formats
	struct NC_API Pixel
	{
	public:
		Pixel(float nRgba) :
			unRgba(static_cast<UInt32>(nRgba * 255.0f)) {}
		explicit Pixel(UInt8 red, UInt8 green, UInt8 blue, UInt8 alpha = 0) :
			unR(red), unG(green), unB(blue), unA(alpha) {}
		explicit Pixel(float red, float green, float blue, float alpha) :
			unR(static_cast<UInt8>(red * 255.0f)),
			unG(static_cast<UInt8>(green * 255.0f)),
			unB(static_cast<UInt8>(blue * 255.0f)),
			unA(static_cast<UInt8>(alpha * 255.0f)) {}

		union { UInt32 unRgba; struct { UInt8 unR, unG, unB, unA; }; };
	public:
		// -- Convertion to float
		inline const float fR() const { return static_cast<float>(unR) / 255.0f; }
		inline const float fG() const { return static_cast<float>(unG) / 255.0f; }
		inline const float fB() const { return static_cast<float>(unB) / 255.0f; }
		inline const float fA() const { return static_cast<float>(unA) / 255.0f; }
		// -- Operations with other pixels
		inline Pixel operator+(const Pixel& rPixel) { return Pixel(
			static_cast<UInt8>(unR * rPixel.unR),	static_cast<UInt8>(unG * rPixel.unG),
			static_cast<UInt8>(unB * rPixel.unB),	static_cast<UInt8>(unA * rPixel.unA)); }
		inline Pixel operator-(const Pixel& rPixel) { return Pixel(
			static_cast<UInt8>(unR - rPixel.unR),	static_cast<UInt8>(unG - rPixel.unG),
			static_cast<UInt8>(unB - rPixel.unB),	static_cast<UInt8>(unA - rPixel.unA)
		);}
		inline Pixel operator*(const Pixel& rPixel) { return Pixel(
			static_cast<UInt8>(unR * rPixel.unR),	static_cast<UInt8>(unG * rPixel.unG),
			static_cast<UInt8>(unB * rPixel.unB),	static_cast<UInt8>(unA * rPixel.unA));
		}
		inline Pixel operator/(const Pixel& rPixel) { return Pixel(
			static_cast<UInt8>(unR / rPixel.unR),	static_cast<UInt8>(unG / rPixel.unG),
			static_cast<UInt8>(unB / rPixel.unB),	static_cast<UInt8>(unA / rPixel.unA));
		}
		inline Pixel& operator+=(const Pixel& rPixel) { unR + rPixel.unR; unG + rPixel.unG; unB + rPixel.unB; unA + rPixel.unA; return *this; }
		inline Pixel& operator-=(const Pixel& rPixel) { unR - rPixel.unR; unG - rPixel.unG; unB - rPixel.unB; unA - rPixel.unA; return *this; }
		inline Pixel& operator*=(const Pixel& rPixel) { unR * rPixel.unR; unG * rPixel.unG; unB * rPixel.unB; unA * rPixel.unA; return *this; }
		inline Pixel& operator/=(const Pixel& rPixel) { unR / rPixel.unR; unG / rPixel.unG; unB / rPixel.unB; unA / rPixel.unA; return *this; }
		// --operators for indexing
		inline Int8& operator[](UInt8 nPos) {
			return ((Int8*)(&unRgba))[nPos];
		}
	};
	/// ConsolePixel struct
	/*struct NC_API CPixel
	{
	public:
		WChar pxChar;
		Pixel pxColor;
	public:
		CPixel() :
		pxChar(' '), pxColor(Pixel(0)) {}
	};*/
}

#endif	// NC_GSTRUCTS_H