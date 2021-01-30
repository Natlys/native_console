#ifndef CMD_FRAME_BUFFER_H
#define CMD_FRAME_BUFFER_H

#include <cmd_core.hpp>
#include <cmd_structs.h>

namespace CMD
{
	/// CmdFrameBuf class
	class CMD_API CmdFrameBuf {
	public:
		CmdFrameBuf();
		~CmdFrameBuf();

		// --getters
		inline Int16 GetWidth() const { return static_cast<Int16>(m_Info.dwSize.X); }
		inline Int16 GetHeight() const { return static_cast<Int16>(m_Info.dwSize.Y); }
		inline CPixel* GetPxData() { return m_pPxData; }
		inline Size GetPxCount() { return m_szPxCount; }
		inline Ptr GetNative() { return m_pCout; }
		inline CFrameBufInfo& GetInfo() { return m_Info; }
		// --setters
		inline void SetSizeWH(UInt16 unWidth, UInt16 unHeight) { m_Info.dwSize = { static_cast<Int16>(unWidth), static_cast<Int16>(unHeight) }; }
		inline void SetInfo(const CFrameBufInfo& rfbInfo) { m_Info = rfbInfo; }
		inline void SetClearPattern(CPixelTypes cpxPattern) { m_cpxClear.Char.UnicodeChar = cpxPattern; }
		inline void SetClearColor(UInt16 cColor) { m_cpxClear.Attributes = cColor; }
		// --core_methods
		void Remake();
		inline void Clear() { for (Size pxi = 0; pxi < m_szPxCount; pxi++) { m_pPxData[pxi] = m_cpxClear; } }
		inline void DrawPixelX(Size xCrd, UInt16 cColor);
		inline void DrawPixelXY(UInt16 xCrd, UInt16 yCrd, UInt16 cColor);
		inline void DrawLineX(UInt16 xCrd0, UInt16 xCrd1, UInt16 cColor);
		inline void DrawLineY(UInt16 yCrd0, UInt16 yCrd1, UInt16 cColor);
		inline void DrawLineXY(UInt16 xCrd0, UInt16 yCrd0, UInt16 xCrd1, UInt16 yCrd1, UInt16 cColor);
		inline void DrawStrXY(UInt16 xCrd, UInt16 yCrd, UInt16 cColor, const char* str);
		inline void DrawRectXY(UInt16 nLt, UInt16 nTp, UInt16 nRt, UInt16 nBt, UInt16 cColor);
	private:
		Ptr m_pCout;
		Size m_szPxCount;
		CPixel* m_pPxData;
		CPixel m_cpxClear;
		CFrameBufInfo m_Info;
	};
	// --==<drawing_methods>==--
	inline void CmdFrameBuf::DrawPixelX(Size xCrd, UInt16 cColor) {
		if (xCrd + 1 >= m_szPxCount) { return; }
		UInt16 unWidth = GetWidth();
		CPixel cpx;
		cpx.Attributes = cColor;
		cpx.Char.UnicodeChar = CPT_SOLID;
		m_pPxData[xCrd] = cpx;
		m_pPxData[xCrd + 1] = cpx;
	}
	inline void CmdFrameBuf::DrawPixelXY(UInt16 xCrd, UInt16 yCrd, UInt16 cColor) {
		UInt16 unWidth = GetWidth();
		UInt16 unHeight = GetHeight();
		if (xCrd >= unWidth || yCrd > unHeight) { return; }
		Size szCrd = NWL_XY_TO_X(xCrd, yCrd, unWidth + 1);
		CPixel cpx;
		cpx.Attributes = cColor;
		cpx.Char.UnicodeChar = CPT_SOLID;
		m_pPxData[szCrd] = cpx;
		m_pPxData[szCrd + 1] = cpx;
	}
	inline void CmdFrameBuf::DrawLineX(UInt16 xCrd0, UInt16 xCrd1, UInt16 cColor) {
		UInt16 unWidth = GetWidth();
		UInt16 unHeight = GetHeight();
		if (xCrd0 < 0 || xCrd0 >= unWidth || xCrd1 < 0 || xCrd1 >= unWidth) { return; }
		CPixel cpx;
		cpx.Char.UnicodeChar = CPT_SOLID;
		cpx.Attributes = cColor;
		for (UInt16 ix = xCrd0; ix <= xCrd1; ix++) {
			for (UInt16 iy = 0; iy <= unHeight; iy++) {
				Size szCrd = NWL_XY_TO_X(ix, iy, unWidth);
				m_pPxData[szCrd] = cpx;
				m_pPxData[szCrd + 1] = cpx;
			}
		}
	}
	inline void CmdFrameBuf::DrawLineY(UInt16 yCrd0, UInt16 yCrd1, UInt16 cColor) {
		UInt16 unWidth = GetWidth();
		UInt16 unHeight = GetHeight();
		if (yCrd0 < 0 || yCrd0 >= unHeight || yCrd1 < 0 || yCrd1 >= unHeight) { return; }
		CPixel cpx;
		cpx.Char.UnicodeChar = CPT_SOLID;
		cpx.Attributes = cColor;
		for (UInt16 iy = yCrd0; iy <= yCrd1; iy++) {
			for (UInt16 ix = 0; ix <= unWidth; ix++) {
				Size szCrd = NWL_XY_TO_X(ix, iy, unWidth);
				m_pPxData[szCrd] = cpx;
				m_pPxData[szCrd + 1] = cpx;
			}
		}
	}
	inline void CmdFrameBuf::DrawLineXY(UInt16 xCrd0, UInt16 yCrd0, UInt16 xCrd1, UInt16 yCrd1, UInt16 cColor) {
		Int16 nDeltaX = xCrd1 - xCrd0;
		Int16 nDeltaY = yCrd1 - yCrd0;
		Int16 nDirX = nDeltaX < 0 ? -1 : 1;
		Int16 nDirY = nDeltaY < 0 ? -1 : 1;
		Int16 nErr = 0;
		Int16 nDeltaErr = nDeltaY;
		for (Int16 nX = xCrd0, nY = yCrd0; nX != xCrd1; nX += nDirX) {
			DrawPixelXY(nX, nY, cColor);
			nErr += nDeltaErr;
			if (nErr > nDeltaX) {
				nY += nDirY;
				nErr -= (nDeltaX);
			}
		}
	}
	inline void CmdFrameBuf::DrawStrXY(UInt16 xCrd, UInt16 yCrd, UInt16 cColor, const char* str) {
		UInt16 unWidth = GetWidth();
		UInt16 unHeight = GetHeight();
		UInt16 unLen = static_cast<UInt16>(strlen(str));
		UInt16 unStrEndX = xCrd + unLen;
		if (xCrd > unWidth || yCrd > unHeight) { return; }
		UInt64 unWritten = 0;
		for (UInt16 ci = 0; ci < unLen; ci++, xCrd++) {
			if (xCrd > unWidth) { xCrd = 0; yCrd++; }
			CPixel cpx;
			cpx.Char.UnicodeChar = CPT_SOLID;
			cpx.Attributes = cColor;
			m_pPxData[ci] = cpx;
			m_pPxData[ci].Char.AsciiChar = str[ci];
			m_pPxData[ci].Char.UnicodeChar = (TCHAR)str[ci];
		}
	}
	inline void CmdFrameBuf::DrawRectXY(UInt16 nLt, UInt16 nTp, UInt16 nRt, UInt16 nBt, UInt16 cColor) {
		UInt16 unWidth = GetWidth();
		UInt16 unHeight = GetHeight();
		if (nLt > nRt) { nLt = nLt - nRt; nRt = nRt + nLt; nLt = nRt - nLt; }
		if (nTp > nBt) { nTp = nTp - nBt; nBt = nBt + nTp; nTp = nBt - nTp; }
		if (nLt > unWidth) { nLt = unWidth; }
		if (nRt > unWidth) { nRt = unWidth; }
		if (nTp > unHeight) { nTp = unHeight; }
		if (nBt > unHeight) { nBt = unHeight; }
		CPixel cpx;
		cpx.Char.UnicodeChar = CPT_SOLID;
		cpx.Attributes = cColor;
		for (UInt16 iy = nTp; iy <= nBt; iy++) {
			for (UInt16 ix = nLt; ix <= nRt; ix++) {
				Size szCrd = NWL_XY_TO_X(ix, iy, unWidth);
				m_pPxData[szCrd] = cpx;
				m_pPxData[szCrd + 1] = cpx;
			}
		}
	}
	// --==</drawing_methods>==--
}
#endif	// CMD_FRAME_BUFFER_H