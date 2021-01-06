#include "nc_pch.hpp"
#include "nc_cwindow.h"

#include <systems/nc_time_sys.h>

namespace NC
{
    CWindow::CWindow(const WindowInfo& rWindowInfo) :
        m_WindowInfo(WindowInfo()),
        m_CPixelInfo(CPixelInfo()),
        m_CFBInfo(CFrameBufInfo()),
        m_Native(NativeWindow()), m_NativeOrig(NativeWindow()),
        m_CBuffer(nullptr), m_CPixels(nullptr), m_szPixels(0)
    {
        m_NativeOrig.pCout = nullptr;
        m_NativeOrig.pCin = nullptr;
        m_Native.pCout = GetStdHandle(STD_OUTPUT_HANDLE);
        m_Native.pCin = GetStdHandle(STD_INPUT_HANDLE);
        m_WindowInfo.xywhRect = V4xywh{0, 0, 1, 1};
        SetConsoleWindowInfo(m_Native.pCout, TRUE, &m_WindowInfo.xywhRect);
        
        UInt64 unFlags = ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT;
        SetConsoleMode(m_Native.pCout, unFlags);
        
        Reset(rWindowInfo);
        setlocale(LC_ALL, "en");
    }
    CWindow::~CWindow()
    {
        setlocale(LC_ALL, "en");
        //if (m_CBuffer) delete m_CBuffer;
        if (m_CPixels) delete[] m_CPixels;
        SetConsoleActiveScreenBuffer(m_NativeOrig.pCout);
    }

    // --setters
    void CWindow::SetTitle(const char* strTitle) { m_WindowInfo.strTitle = strTitle; }

    void CWindow::SetSize(UInt16 unWidth, UInt16 unHeight) {
        m_WindowInfo.whMaxSize = GetLargestConsoleWindowSize(m_Native.pCout);
        if (unWidth > m_WindowInfo.whMaxSize.X || unHeight > m_WindowInfo.whMaxSize.Y) { return; }
        m_WindowInfo.xywhRect = { 0, 0, static_cast<Int16>(unWidth), static_cast<Int16>(unHeight) };
        m_CFBInfo.dwSize.X = unWidth + 1; m_CFBInfo.dwSize.Y = unHeight + 1;
        
        if (m_CPixels != nullptr) { delete[] m_CPixels; m_CPixels = nullptr; m_szPixels = 0; }
        if (m_CBuffer != nullptr) { delete m_CBuffer; m_CBuffer = nullptr; }
        if (m_CFBInfo.dwSize.X <= 0 || m_CFBInfo.dwSize.Y <= 0 || m_CBuffer != nullptr || m_CPixels != nullptr) { return; }
        m_szPixels = static_cast<Size>(m_CFBInfo.dwSize.X) * static_cast<Size>(m_CFBInfo.dwSize.Y);
        m_CPixels = new CPixel[m_szPixels];
        m_CBuffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, m_CPixels);
        ResetPixels();

        m_CFBInfo.dwMaximumWindowSize = m_WindowInfo.whMaxSize;
        m_CFBInfo.srWindow = m_WindowInfo.xywhRect;
        m_CFBInfo.wAttributes = 0b0000'1010;
        m_CFBInfo.wPopupAttributes = 0b0000'0010;
        m_CFBInfo.bFullscreenSupported = 1;
        m_CFBInfo.dwCursorPosition = V2xy{ 0, 0 };
        m_CFBInfo.cbSize = sizeof(m_CFBInfo);
        // in the hex every 2 digits are one byte;
        // here is abgr representation from left to right
        // or rgba from right to left
        // Here I make monochromatic pallete
        for (UInt8 cli = 0; cli < 16; cli++) m_CFBInfo.ColorTable[cli] = 0x11'11'11 * cli;

        SetConsoleScreenBufferSize(m_Native.pCout, m_CFBInfo.dwSize);
        SetConsoleScreenBufferInfoEx(m_Native.pCout, &m_CFBInfo);
        SetConsoleScreenBufferSize(m_Native.pCout, m_CFBInfo.dwSize);
        SetConsoleActiveScreenBuffer(m_Native.pCout);
        SetConsoleWindowInfo(m_Native.pCout, TRUE, &m_WindowInfo.xywhRect);
    }
    void CWindow::SetPxSize(UInt16 unPxW, UInt16 unPxH) {
        m_WindowInfo.whPxSize.X = m_CPixelInfo.dwFontSize.X = static_cast<Int16>(unPxW);
        m_WindowInfo.whPxSize.X = m_CPixelInfo.dwFontSize.Y = static_cast<Int16>(unPxH);
        m_CPixelInfo.FontFamily = FF_DONTCARE;
        m_CPixelInfo.FontWeight = FW_NORMAL;
        m_CPixelInfo.nFont = 0;
        swprintf_s(m_CPixelInfo.FaceName, L"Consolas");
        m_CPixelInfo.cbSize = sizeof(m_CPixelInfo);
        SetCurrentConsoleFontEx(m_Native.pCout, TRUE, &m_CPixelInfo);
    }
    void CWindow::Reset(const WindowInfo& rWindowInfo) {
        m_WindowInfo = rWindowInfo;
        SetTitle(&rWindowInfo.strTitle[0]);
        SetSize(rWindowInfo.xywhRect.Right, rWindowInfo.xywhRect.Bottom);
        SetPxSize(rWindowInfo.whPxSize.X, rWindowInfo.whPxSize.Y);
    }

    // --<core_methods>--
    void CWindow::Update()
    {
        //WriteConsoleOutputW(m_Native.pCout, m_CPixels, m_CFBInfo.dwSize,
       //     { 0, 0 }, &m_WindowInfo.xywhRect);

        Char strTitle[128];
        sprintf_s(strTitle, 128, "%s::FPS: %f\0",
            &m_WindowInfo.strTitle[0], 1.0f / TimeSys::GetRealDelta());
        SetConsoleTitleA(strTitle);
    }
    // --</core_methods>--
}