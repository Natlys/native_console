#ifndef CMD_ENGINE_H
#define CMD_ENGINE_H

#include <cmd_core.hpp>
#include <cmd_structs.h>
#include <cmd_gui.h>

namespace CMD
{
	/// CmdEngine class
	class CMD_API CmdEngine
	{
		using Widgets = HashMap<UInt32, CWidget*>;
	public:
		CmdEngine();
		CmdEngine(const CmdEngine& rCpy) = delete;
		void operator=(const CmdEngine& rCpy) = delete;
	public:
		~CmdEngine();

		// --getters
		static inline CmdEngine& Get()					{ static CmdEngine s_CEngine; return s_CEngine; }
		inline std::thread& GetRunThread()				{ return m_thrRun; }
		inline const Int16 GetWndWidth()		const	{ return m_cwInfo.GetWidth(); }
		inline const Int16 GetWndHeight()		const	{ return m_cwInfo.GetHeight(); }
		inline const CWindowInfo& GetWndInfo()	const	{ return m_cwInfo; }
		inline const CPixelInfo& GetPxInfo()	const	{ return m_cpxInfo; }
		inline const CFrameBufInfo& GetFBInfo()	const	{ return m_cfbInfo; }
		inline const CEventsInfo& GetEvInfo()	const	{ return m_cevInfo; }
		inline const DArray<CPixel>& GetPxBuf()	const	{ return m_cpxBuf; }
		
		inline UInt16 GetMouseMoveX()	{ return m_cevInfo.MouseInfo.xMove; }
		inline UInt16 GetMouseMoveY()	{ return m_cevInfo.MouseInfo.yMove; }
		inline V2xy GetMouseMoveXY()	{ return m_cevInfo.MouseInfo.xyMove; }

		inline bool GetMousePressed(MouseButtons msCode) const { return m_cevInfo.MouseInfo.bsButtons[msCode].bPressed; }
		inline bool GetMouseReleased(MouseButtons msCode) const { return m_cevInfo.MouseInfo.bsButtons[msCode].bReleased; }
		inline bool GetMouseHeld(MouseButtons msCode) const { return m_cevInfo.MouseInfo.bsButtons[msCode].bHeld; }
		inline bool GetKeyPressed(KeyCodes kCode) const { return m_cevInfo.KeyboardInfo.bsButtons[kCode].bPressed; }
		inline bool GetKeyReleased(KeyCodes kCode) const { return m_cevInfo.KeyboardInfo.bsButtons[kCode].bReleased; }
		inline bool GetKeyHeld(KeyCodes kCode) const { return m_cevInfo.KeyboardInfo.bsButtons[kCode].bHeld; }
		
		inline void* GetCout() { return m_pCout; }
		inline void* GetCIn() { return m_pCin; }

		inline Widgets& GetWidgets() { return m_cWidgets; }
		inline CWidget* GetWidget(UInt32 unId) { return m_cWidgets.find(unId) == m_cWidgets.end() ? nullptr : m_cWidgets[unId]; }
		// --setters
		void SetTitle(const char* strTitle);
		void SetWndInfo(const CWindowInfo& rcwInfo);
		void SetWndSize(UInt16 nWidth, UInt16 nHeight);
		void SetPxInfo(const CPixelInfo& rcpxInfo);
		void SetPxSize(UInt16 nWidth, UInt16 nHeight);
		void SetFBInfo(const CFrameBufInfo& rfbInfo);
		bool ResetWindow();
		inline void SetClearPattern(CPixelTypes cpxPattern) { m_cpxClear.Char.UnicodeChar = cpxPattern; }
		inline void SetClearColor(UInt16 cColor) { m_cpxClear.Attributes = cColor; }
		inline void ClearPxBuf() { for (Size pxi = 0; pxi < m_cpxBuf.size(); pxi++) { m_cpxBuf[pxi] = m_cpxClear; } }
		inline void AddWidget(CWidget* pcWidget) {
			if (pcWidget == nullptr) { return; }
			m_cWidgets[pcWidget->GetId()] = pcWidget;
		}
		inline void RmvWidget(UInt32 unId) {
			auto& itWgt = m_cWidgets.find(unId);
			if (itWgt == m_cWidgets.end()) { return; }
			m_cWidgets.erase(itWgt);
		}
		// --predicates
		inline bool IsRunning() const { return m_bIsRunning; }

		// --core_methods
		bool Init();
		void Run();
		void Quit();
		// --drawing_methods
		inline void DrawPixelX(Size xCrd, UInt16 cColor) {
			if (xCrd + 1 >= m_cpxBuf.size()) { return; }
			//m_cpxDraw.Attributes = cColor;
			//m_cpxBuf[xCrd] = m_cpxBuf[xCrd + 1] = m_cpxDraw;
			UInt16 unWidth = GetWndWidth();
			UInt64 unWritten = 0;
			FillConsoleOutputAttribute(m_pCout, cColor, 2, { static_cast<Int16>(xCrd % unWidth), static_cast<Int16>(xCrd / unWidth) }, &unWritten);
			FillConsoleOutputCharacterW(m_pCout, m_cpxDraw.Char.UnicodeChar, 2, { static_cast<Int16>(xCrd % unWidth), static_cast<Int16>(xCrd / unWidth) }, &unWritten);
		}
		inline void DrawPixelXY(UInt16 xCrd, UInt16 yCrd, UInt16 cColor) {
			UInt16 unWidth = GetWndWidth();
			UInt16 unHeight = GetWndHeight();
			if (xCrd < 0 || xCrd >= unWidth || yCrd < 0 || yCrd >= unHeight) { return; }
			UInt64 unWritten = 0;
			FillConsoleOutputAttribute(m_pCout, cColor, 2, { static_cast<Int16>(xCrd), static_cast<Int16>(yCrd) }, &unWritten);
			FillConsoleOutputCharacterW(m_pCout, m_cpxDraw.Char.UnicodeChar, 2, { static_cast<Int16>(xCrd), static_cast<Int16>(yCrd) }, &unWritten);
		}
		inline void DrawLineX(UInt16 xCrd0, UInt16 xCrd1, UInt16 cColor) {
			UInt16 unWidth = GetWndWidth();
			UInt16 unHeight = GetWndHeight();
			if (xCrd0 < 0 || xCrd0 >= unWidth || xCrd1 < 0 || xCrd1 >= unWidth) { return; }
			UInt64 unWritten = 0;
			for (UInt16 ix = xCrd0; ix <= xCrd1; ix++) {
				for (UInt16 iy = 0; iy <= unHeight; iy++) {
					FillConsoleOutputAttribute(m_pCout, cColor, 2, { static_cast<Int16>(ix), static_cast<Int16>(iy) }, &unWritten);
					FillConsoleOutputCharacterW(m_pCout, m_cpxDraw.Char.UnicodeChar, 2, { static_cast<Int16>(ix), static_cast<Int16>(iy) }, &unWritten);
				}
			}
		}
		inline void DrawLineY(UInt16 yCrd0, UInt16 yCrd1, UInt16 cColor){
			UInt16 unWidth = GetWndWidth();
			UInt16 unHeight = GetWndHeight();
			if (yCrd0 < 0 || yCrd0 >= unHeight || yCrd1 < 0 || yCrd1 >= unHeight) { return; }
			UInt64 unWritten = 0;
			for (UInt16 iy = yCrd0; iy <= yCrd1; iy++) {
				FillConsoleOutputAttribute(m_pCout, cColor, unWidth, { static_cast<Int16>(0), static_cast<Int16>(iy) }, &unWritten);
				FillConsoleOutputCharacterW(m_pCout, m_cpxDraw.Char.UnicodeChar, unWidth, { static_cast<Int16>(0), static_cast<Int16>(iy) }, &unWritten);
			}
		}
		inline void DrawLineXY(UInt16 xCrd0, UInt16 yCrd0, UInt16 xCrd1, UInt16 yCrd1, UInt16 cColor) {
			UInt16 nDeltaX = xCrd1 - xCrd0;
			UInt16 nDeltaY = yCrd1 - yCrd0;
			UInt16 nDirX = nDeltaX < 0 ? -1 : 1;
			UInt16 nDirY = nDeltaY < 0 ? -1 : 1;
			UInt16 nErr = 0;
			UInt16 nDeltaErr = nDeltaY + nDirY;
			for (UInt16 nX = xCrd0, nY = yCrd0; nX != xCrd1; nX += nDirX) {
				DrawPixelXY(nX, nY, cColor);
				nErr += nDeltaErr;
				if (nErr >= nDeltaX + nDirX) {
					nY += nDirY;
					nErr = 0;
				}
			}
		}
		inline void DrawStrXY(UInt16 xCrd, UInt16 yCrd, UInt16 cColor, const char* str) {
			UInt16 unWidth = GetWndWidth();
			UInt16 unHeight = GetWndHeight();
			UInt16 unLen = static_cast<UInt16>(strlen(str));
			UInt16 unStrEndX = xCrd + unLen;
			if (xCrd < 0 || xCrd > unWidth || yCrd < 0 || yCrd > unHeight) { return; }
			UInt64 unWritten = 0;
			for (UInt16 ci = 0; ci < unLen; ci++, xCrd++) {
				if (xCrd > unWidth) { xCrd = 0; yCrd++; }
				FillConsoleOutputAttribute(m_pCout, cColor, 1, { static_cast<Int16>(xCrd), static_cast<Int16>(yCrd) }, &unWritten);
				FillConsoleOutputCharacterW(m_pCout, str[ci], 1, { static_cast<Int16>(xCrd), static_cast<Int16>(yCrd) }, &unWritten);
			}
		}
		// --other_methods
		void MakeSound(SoundTypes sType = ST_BEEP);
		void ChangeSoundFreq(Int32 unFreq);
		void ChangeSoundDur(Int32 unDur);
	private:
		inline void Update();
		inline void OnEvent();
	private:
		bool m_bIsRunning;
		std::thread m_thrRun;

		void *m_pCout, *m_pCin;
		void *m_pCoutOrig, *m_pCinOrig;
		
		CWindowInfo m_cwInfo;
		CPixelInfo m_cpxInfo;
		CFrameBufInfo m_cfbInfo;
		CEventsInfo m_cevInfo;

		DArray<CPixel> m_cpxBuf;
		CPixel m_cpxClear;
		CPixel m_cpxDraw;

		Widgets m_cWidgets;

		std::chrono::steady_clock::time_point m_tpCurrTime;
		std::chrono::steady_clock::time_point m_tpLastTime;
		double m_nDeltaTime;

		UInt32 m_unSoundFreq;
		UInt32 m_unSoundDur;
	};
}

#endif	// CMD_ENGINE_H