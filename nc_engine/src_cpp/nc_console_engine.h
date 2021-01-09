#ifndef NC_CONSOLE_ENGINE_H
#define NC_CONSOLE_ENGINE_H

#include <nc_core.hpp>
#include <nc_vector.h>
#include <nc_structs.h>

namespace NC
{
	struct NC_API CWindowInfo
	{
	public:
		String strTitle = "cwindow";
		V4xywh xywhRect = { 0, 0, 1, 1 };
		V2wh whMaxSize = { 1, 1 };
		bool bIsFocused = false;
	public:
		inline Int16 GetWidth() const { return static_cast<Int16>(std::abs(
			static_cast<Int16>(xywhRect.Right) - static_cast<Int16>(xywhRect.Left))); 
		}
		inline Int16 GetHeight() const { return static_cast<Int16>(std::abs(
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
				V2xy xyMove = {0, 0};
				struct { UInt16 xMove, yMove; };
			};
			union {
				V2xy xyHeld = {0, 0};
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
	/// ConsoleEngine class
	class NC_API ConsoleEngine
	{
	private:
		ConsoleEngine();
		ConsoleEngine(const ConsoleEngine& rCpy) = delete;
		void operator=(const ConsoleEngine& rCpy) = delete;
	public:
		~ConsoleEngine();

		// --getters
		static inline ConsoleEngine& Get()		{ static ConsoleEngine s_CEngine; return s_CEngine; }
		inline const Int16 GetWndWidth()		const	{ return m_cwInfo.GetWidth(); }
		inline const Int16 GetWndHeight()		const	{ return m_cwInfo.GetHeight(); }
		inline const CWindowInfo& GetWndInfo()	const	{ return m_cwInfo; }
		inline const CPixelInfo& GetPxInfo()	const	{ return m_cpxInfo; }
		inline const CFrameBufInfo& GetFBInfo()	const	{ return m_cfbInfo; }
		inline const CEventsInfo& GetEvInfo()	const	{ return m_cevInfo; }
		inline const CPixel* GetPxBuf()			const	{ return m_cPixels; }
		inline const Size GetPxBufSize()		const	{ return m_szPixels; }
		
		inline UInt16 GetMouseMoveX()	{ return m_cevInfo.MouseInfo.xMove; }
		inline UInt16 GetMouseMoveY()	{ return m_cevInfo.MouseInfo.yMove; }
		inline V2xy GetMouseMoveXY()	{ return m_cevInfo.MouseInfo.xyMove; }

		inline bool GetMousePressed(MouseButtons msCode) const { return m_cevInfo.MouseInfo.bsButtons[msCode].bPressed; }
		inline bool GetMouseHeld(MouseButtons msCode) const { return m_cevInfo.MouseInfo.bsButtons[msCode].bHeld; }
		inline bool GetKeyPressed(KeyCodes kCode) const { return m_cevInfo.KeyboardInfo.bsButtons[kCode].bPressed; }
		inline bool GetKeyHeld(KeyCodes kCode) const { return m_cevInfo.KeyboardInfo.bsButtons[kCode].bHeld; }
		
		inline void* GetCout() { return m_pCout; }
		inline void* GetCIn() { return m_pCin; }
		// --setters
		void SetTitle(const char* strTitle);
		void SetWndInfo(const CWindowInfo& rcwInfo);
		void SetPxInfo(const CPixelInfo& rcpxInfo);
		void SetFBInfo(const CFrameBufInfo& rfbInfo);
		bool ResetWindow();
		inline void SetPixelX(Size xCrd, UInt16 cColor, CPixelTypes cpxPattern) {
			if (xCrd >= m_szPixels) { return; }
			//m_cPixels[xCrd] = CPixel{ cpxPattern, cColor };
			//WriteConsoleOutputW(m_pCout, m_cPixels, m_cfbInfo.dwSize,
			//	{ 0, 0 }, &m_cwInfo.xywhRect);
			WriteConsoleOutputAttribute(m_pCout, &cColor, 1,
				{ static_cast<Int16>(xCrd) % GetWndWidth(), static_cast<Int16>(xCrd) / GetWndWidth() }, nullptr);
		}
		inline void SetPixelXY(UInt16 xCrd, UInt16 yCrd, UInt16 cColor, CPixelTypes cpxPattern) {
			SetPixelX(static_cast<Size>(xCrd) + static_cast<Size>(yCrd) * static_cast<Size>(GetWndWidth()), cColor, cpxPattern);
		}
		// --predicates
		inline bool IsRunning() const { return m_bIsRunning; }

		// --core_methods
		bool Init(CWindowInfo& rcwInfo, CPixelInfo& rcpxInfo, CFrameBufInfo& rfbInfo);
		void Quit();
		void Update();
	private:
		inline void OnEvent();
	private:
		bool m_bIsRunning;

		void *m_pCout, *m_pCin;
		void *m_pCoutOrig, *m_pCinOrig;
		
		CWindowInfo m_cwInfo;
		CPixelInfo m_cpxInfo;
		CFrameBufInfo m_cfbInfo;
		CEventsInfo m_cevInfo;

		CPixel* m_cPixels;
		Size m_szPixels;

		std::chrono::steady_clock::time_point m_currTime;
		std::chrono::steady_clock::time_point m_lastTime;
		double m_deltaTime;
	};
}

#endif	// NC_CONSOLE_ENGINE_H