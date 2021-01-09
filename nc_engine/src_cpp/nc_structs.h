#ifndef NC_STRUCTS_H
#define NC_STRUCTS_H

#include <nc_core.hpp>

// Pixel
namespace NC
{
	/// Pixel structure
	/// Description:
	/// -- Represents color in rgba for float and unsigned integer formats
	struct NC_API Pixel
	{
	public:
	};
	struct NC_API CWindowInfo
	{
	public:
		String strTitle = "cwindow";
		V4xywh xywhRect = { 0, 0, 1, 1 };
		V2wh whMaxSize = { 1, 1 };
		bool bIsFocused = false;
	public:
		inline Int16 GetWidth() const {
			return static_cast<Int16>(std::abs(
				static_cast<Int16>(xywhRect.Right) - static_cast<Int16>(xywhRect.Left)));
		}
		inline Int16 GetHeight() const {
			return static_cast<Int16>(std::abs(
				static_cast<Int16>(xywhRect.Bottom) - static_cast<Int16>(xywhRect.Top)));
		}
		inline V2xy GetSize() const { return { GetWidth(), GetHeight() }; }
	};
	struct NC_API ButtonState {
		bool bNext = false, bLast = false, bPressed = false, bHeld = false;
	};
	struct NC_API CEventsInfo
	{
		UInt64 unEvGetCount = 0;
		UInt64 unEvReadCount = 0;
		INPUT_RECORD irEvents[32];

		struct {
			union {
				V2xy xyMove = { 0, 0 };
				struct { UInt16 xMove, yMove; };
			};
			union {
				V2xy xyHeld = { 0, 0 };
				struct { UInt16 xHeld, yHeld; };
			};
			struct { double xDelta = 0.0, yDelta = 0.0; } Scroll;
			ButtonState bsButtons[MSB_COUNT]{ 0 };
		} MouseInfo;
		struct {
			union {
				WChar unicode;
				Char ascii;
			} cTypedChars[KC_COUNT]{ 0 };
			ButtonState bsButtons[KC_COUNT]{ 0 };
		} KeyboardInfo;
	};
}

#endif	// NC_STRUCTS_H