#ifndef NWC_CORE_HPP
#define NWC_CORE_HPP
/// The main header of configurations and definitions

#if defined NWC_LINK_DYNAMIC
#ifdef NWC_BUILD_DLL
#define NWC_API __declspec(dllexport)
#elif defined NWC_BUILD_EXE
#define NWC_API __declspec(dllimport)
#endif
#else
#define NWC_API
#endif

#include <nwc_pch.hpp>

// --<type_alias>--
namespace NWC
{
	using CHistoryInfo = CONSOLE_HISTORY_INFO;
	using CSelectionInfo = CONSOLE_SELECTION_INFO;
	using CFrameBufInfo = CONSOLE_SCREEN_BUFFER_INFOEX;
	using CPixelInfo = CONSOLE_FONT_INFOEX;
	using CCursorInfo = CONSOLE_CURSOR_INFO;
	using CPixel = CHAR_INFO;
	using V2xy = COORD;
	using V2wh = COORD;
	using V4xywh = SMALL_RECT;
}
// --</type_alias>--

namespace NWC
{
	/// 0xFF'FF'FF'FF -> 32 bits
	/// counting from left:
	/// 4 bits - red; 4 bits - blue; 4 bits - green; 4 bits - alpha
	enum CPixelTypes : WChar {
		CPT_DITHER = 0x2489,
		CPT_1_4 = 0x2591,
		CPT_2_4 = 0x2592,
		CPT_3_4 = 0x2593,
		CPT_SOLID = 0x2588,
	};
	/// 0b0000'0000 -> 8 bits; 0x00 -> 8 bits
	/// right 4 bits - background -> 16 variations; right digit - back
	/// left 4 bits - foreground -> 16 variations; left digit - char
	enum CColorsDefault : UInt16 {
		CCD_FG_BLACK = 0x00,
		CCD_FG_DARK_BLUE = 0x01,
		CCD_FG_DARK_GREEN = 0x02,
		CCD_FG_DARK_CYAN = 0x03,
		CCD_FG_DARK_RED = 0x04,
		CCD_FG_DARK_MAGENTA = 0x05,
		CCD_FG_DARK_YELLOW = 0x06,
		CCD_FG_GREY = 0x07,
		CCD_FG_DARK_GREY = 0x08,
		CCD_FG_BLUE = 0x09,
		CCD_FG_GREEN = 0x0A,
		CCD_FG_CYAN = 0x0B,
		CCD_FG_RED = 0x0C,
		CCD_FG_MAGENTA = 0x0D,
		CCD_FG_YELLOW = 0x0E,
		CCD_FG_WHITE = 0x0F,
		CCD_BG_BLACK = 0x00,
		CCD_BG_DARK_BLUE = 0x10,
		CCD_BG_DARK_GREEN = 0x20,
		CCD_BG_DARK_CYAN = 0x30,
		CCD_BG_DARK_RED = 0x40,
		CCD_BG_DARK_MAGENTA = 0x50,
		CCD_BG_DARK_YELLOW = 0x60,
		CCD_BG_GREY = 0x70,
		CCD_BG_DARK_GREY = 0x80,
		CCD_BG_BLUE = 0x90,
		CCD_BG_GREEN = 0xA0,
		CCD_BG_CYAN = 0xB0,
		CCD_BG_RED = 0xC0,
		CCD_BG_MAGENTA = 0xD0,
		CCD_BG_YELLOW = 0xE0,
		CCD_BG_WHITE = 0xF0,
	};
	enum CColorsNum : UInt16 {
		CCN_FG_1 = 0x00, CCN_FG_2 = 0x01, CCN_FG_3 = 0x02, CCN_FG_4 = 0x03,
		CCN_FG_5 = 0x04, CCN_FG_6 = 0x05, CCN_FG_7 = 0x06, CCN_FG_8 = 0x07,
		CCN_FG_9 = 0x08, CCN_FG_10 = 0x09, CCN_FG_11 = 0x0A, CCN_FG_12 = 0x0B,
		CCN_FG_13 = 0x0C, CCN_FG_14 = 0x0D, CCN_FG_15 = 0x0E, CCN_FG_16 = 0x0F,

		CCN_BG_1 = 0x00, CCN_BG_2 = 0x10, CCN_BG_3 = 0x20, CCN_BG_4 = 0x30,
		CCN_BG_5 = 0x40, CCN_BG_6 = 0x50, CCN_BG_7 = 0x60, CCN_BG_8 = 0x70,
		CCN_BG_9 = 0x80, CCN_BG_10 = 0x90, CCN_BG_11 = 0xA0, CCN_BG_12 = 0xB0,
		CCN_BG_13 = 0xC0, CN_BG_14 = 0xD0, CCN_BG_15 = 0xE0, CCN_BG_16 = 0xF0,
	};
}

#endif	// NWC_CORE_HPP