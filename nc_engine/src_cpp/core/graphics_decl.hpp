#ifndef GRAPHICS_DECL_HPP
#define GRAPHICS_DECL_HPP

#include <nc_core.hpp>

namespace NC
{
	// --control
	class NC_API Drawer;
	// --graphics_context
	class NC_API CWindow;
	// --enums&structs
	/// 0xFF'FF'FF'FF -> 32 bits
	/// counting from left:
	/// 4 bits - red; 4 bits - blue; 4 bits - green; 4 bits - alpha
	enum CPixelTypes : WChar {
		PX_DITHER = 0x2489,
		PX_1_4 = 0x2591,
		PX_2_4 = 0x2592,
		PX_3_4 = 0x2593,
		PX_SOLID = 0x2588,
	};
	/// 0b0000'0000 -> 8 bits; 0x00 -> 8 bits
	/// right 4 bits - background -> 16 variations; right digit - back
	/// left 4 bits - foreground -> 16 variations; left digit - char
	enum CColors_def : UInt16 {
		CD_FG_BLACK		= 0x00,
		CD_FG_DARK_BLUE	= 0x01,
		CD_FG_DARK_GREEN	= 0x02,
		CD_FG_DARK_CYAN	= 0x03,
		CD_FG_DARK_RED		= 0x04,
		CD_FG_DARK_MAGENTA	= 0x05,
		CD_FG_DARK_YELLOW	= 0x06,
		CD_FG_GREY			= 0x07,
		CD_FG_DARK_GREY	= 0x08,
		CD_FG_BLUE			= 0x09,
		CD_FG_GREEN		= 0x0A,
		CD_FG_CYAN			= 0x0B,
		CD_FG_RED			= 0x0C,
		CD_FG_MAGENTA		= 0x0D,
		CD_FG_YELLOW		= 0x0E,
		CD_FG_WHITE		= 0x0F,
		CD_BG_BLACK		= 0x00,
		CD_BG_DARK_BLUE	= 0x10,
		CD_BG_DARK_GREEN	= 0x20,
		CD_BG_DARK_CYAN	= 0x30,
		CD_BG_DARK_RED		= 0x40,
		CD_BG_DARK_MAGENTA	= 0x50,
		CD_BG_DARK_YELLOW	= 0x60,
		CD_BG_GREY			= 0x70,
		CD_BG_DARK_GREY	= 0x80,
		CD_BG_BLUE			= 0x90,
		CD_BG_GREEN		= 0xA0,
		CD_BG_CYAN			= 0xB0,
		CD_BG_RED			= 0xC0,
		CD_BG_MAGENTA		= 0xD0,
		CD_BG_YELLOW		= 0xE0,
		CD_BG_WHITE		= 0xF0,
	};
	enum CColors_num : UInt16 {
		CN_FG_1		= 0x00,	CN_FG_2		= 0x01,	CN_FG_3		= 0x02,	CN_FG_4 = 0x03,
		CN_FG_5		= 0x04,	CN_FG_6		= 0x05,	CN_FG_7		= 0x06,	CN_FG_8 = 0x07,
		CN_FG_9		= 0x08,	CN_FG_10	= 0x09,	CN_FG_11	= 0x0A,	CN_FG_12 = 0x0B,
		CN_FG_13	= 0x0C,	CN_FG_14	= 0x0D,	CN_FG_15	= 0x0E,	CN_FG_16 = 0x0F,

		CN_BG_1		= 0x00, CN_BG_2		= 0x10,	CN_BG_3		= 0x20,	CN_BG_4		= 0x30,
		CN_BG_5		= 0x40, CN_BG_6		= 0x50,	CN_BG_7		= 0x60,	CN_BG_8		= 0x70,
		CN_BG_9		= 0x80, CN_BG_10	= 0x90,	CN_BG_11	= 0xA0,	CN_BG_12	= 0xB0,
		CN_BG_13	= 0xC0, CN_BG_14	= 0xD0,	CN_BG_15	= 0xE0,	CN_BG_16	= 0xF0
	};
}

#define XY_TO_X(x, y, w) (y * w + x)

#endif	// GRAPHICS_DECL_HPP