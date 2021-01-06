#ifndef NC_WINDOW_H
#define NC_WINDOW_H

#include <core/nc_decl.hpp>
#include <core/graphics_decl.hpp>

namespace NC
{
	using EventCallback = std::function<void(AEvent& rEvt)>;
	struct NC_API NativeWindow
	{
		void* pCout = nullptr, * pCin = nullptr;
	};
	struct NC_API WindowInfo
	{
	public:
		EventCallback cbOnEvent = nullptr;
		String strTitle = "ConsoleWindow";
		V4xywh xywhRect = { 0, 0, 1, 1 };
		V2wh whMaxSize = { 1, 1 };
		V2wh whPxSize = { 1, 1 };
		bool bVSync = false;
	public:
		WindowInfo() = default;
		WindowInfo(const char* sTitle, V2wh WH, V2wh PxWH) :
			strTitle(sTitle),
			xywhRect{ 0, 0, WH.X, WH.Y },
			whPxSize{ PxWH.X, PxWH.Y } { }
	};
	/// Window class
	class NC_API CWindow
	{
	public:
		CWindow(const WindowInfo& rWindowInfo);
		~CWindow();

		// --getters
		inline const UInt16 GetWidth() const { return m_WindowInfo.xywhRect.Right - m_WindowInfo.xywhRect.Left; }
		inline const UInt16 GetHeight() const { return m_WindowInfo.xywhRect.Bottom - m_WindowInfo.xywhRect.Top; }
		inline const WindowInfo& GetInfo() const { return m_WindowInfo; }
		inline const CPixelInfo& GetPxInfo() const { return m_CPixelInfo; }
		inline const CFrameBufInfo& GetFBInfo() const { return m_CFBInfo; }
		inline const CPixel* GetPixels() { return m_CPixels; }
		inline NativeWindow* GetNative() { return &m_Native; }
		// --setters
		void SetTitle(const char* strTitle);
		void SetSize(UInt16 unW, UInt16 unH);
		void SetPxSize(UInt16 unPxW, UInt16 unPxH);
		inline void SetEventCallback(EventCallback cbOnEvent) { m_WindowInfo.cbOnEvent = cbOnEvent; }
		inline void SetPixel(UInt16 unX, UInt16 unY, CPixel cPx) {
			Size szPos = XY_TO_X(unX, unY, GetWidth());
			SetPixel(szPos, cPx);
		}
		inline void SetPixel(Size szPos, CPixel cPx) {
			if (szPos < m_szPixels)
			m_CPixels[szPos] = cPx;
			m_CPixels[szPos + 1] = cPx;
		}
		void Reset(const WindowInfo& rWindowInfo);
		inline void ResetPixels() { memset(&m_CPixels[0], 0, sizeof(CPixel) * m_szPixels); }

		// --core_methods
		void Update();
	private:
		NativeWindow m_Native;
		NativeWindow m_NativeOrig;
		
		WindowInfo m_WindowInfo;
		CPixelInfo m_CPixelInfo;

		void* m_CBuffer;
		CFrameBufInfo m_CFBInfo;
		CPixel* m_CPixels;
		Size m_szPixels;
	};
}

#endif	// NC_WINDOW_H