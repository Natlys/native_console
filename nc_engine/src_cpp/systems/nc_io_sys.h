#ifndef NC_IO_SYSTEM_H
#define NC_IO_SYSTEM_H

#include <core/nc_decl.hpp>

namespace NC
{
	class NC_API IOSys
	{
		friend class EvSys;
	public:	// Interface Structures
		struct NC_API BtnState
		{
			bool bPressed, bReleased;
			bool bHeld;
			bool bNew, bOld;
		};
	public:	// Interface Attributes
		static struct CursorState
		{
			double xHeld, yHeld;
			double xMove, yMove;
			double xMoveDelta, yMoveDelta;
			bool bBlocked;
		} Cursor;
		static double xScrollDelta, yScrollDelta;
	public:
		// -- Getters
		static inline bool GetKeyPressed(UInt16 unKeyId) { return s_bsKeys[unKeyId].bPressed; }
		static inline bool GetKeyReleased(UInt16 unKeyId) { return s_bsKeys[unKeyId].bReleased; }
		static inline bool GetKeyHeld(UInt16 unKeyId) { return s_bsKeys[unKeyId].bHeld; }
		static inline bool GetMsButtonPressed(UInt16 unButtonId) { return s_bsMsBtns[unButtonId].bPressed; }
		static inline bool GetMsButtonReleased(UInt16 unButtonId) { return s_bsMsBtns[unButtonId].bReleased; }
		static inline bool GetMsButtonHeld(UInt16 unButtonId) { return s_bsMsBtns[unButtonId].bHeld; }
		
		// -- Core Methods
		static void Update();

		static void UpdateKeyboard();
		static void UpdateMouseButtons();
	private:
		static BtnState s_bsKeys[NC_KEY_LAST];
		static BtnState s_bsMsBtns[NC_MS_BTN_LAST];
	};
	enum KeyCodes : wchar_t
	{
		NONE = 0,
		BELL = 7, // "\a" - sound signal
		BACKSPACE = 8, // Step backward - can be used for two symbols in one
		HTAB = 9, ENTER = 10, VTAB = 11, // Hor + Vert tabulation and EndLine
		SHIFT = 16, CTRL = 17, PAUSE = 19, CAPS_LOCK = 20, ESCAPE = 27,
		LEFT = 37, UP = 38, RIGHT = 39, DOWN = 40, INSERT = 45, DEL = 46,
		HOME = 36,
		SPACE = 32, EXCLAIM = 33, HASH = 35,
		K0 = 48, K1 = 49, K2, K3, K4, K5, K6, K7, K8, K9 = 57,
		COLON = 58, SEMICOLON = 59, LESSER = 60, EQUAL = 61, GREATER = 62,
		A = 65, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P = 80,
		Q = 81, R, S, T, U, V, W, X, Y, Z = 90,
		a = 97, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p = 112,
		q = 113, r, s, t, u, v, w, x, y, z = 122,
		F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
		RECT_DITHER = 177, QUAD = 254,
		PGUP, PGDN,
		RETURN, SCROLL,
		NP_MUL, NP_DIV, NP_ADD, NP_SUB, NP_DECIMAL, PERIOD
	};
}

#endif // CN_IO_SYSTEM_H