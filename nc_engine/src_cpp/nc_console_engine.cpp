#include "nc_pch.hpp"
#include "nc_console_engine.h"

#define NC_INPUT_FLAGS ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT

namespace NC
{
    ConsoleEngine::ConsoleEngine() :
        m_cwInfo(CWindowInfo()),
        m_cpxInfo(CPixelInfo()),
        m_cfbInfo(CFrameBufInfo()),
        m_pCout(nullptr), m_pCin(nullptr),
        m_pCoutOrig(nullptr), m_pCinOrig(nullptr),
        m_cPixels(nullptr), m_szPixels(0) { }
    ConsoleEngine::~ConsoleEngine()
    {
        if (m_cPixels != nullptr) { delete[] m_cPixels; m_cPixels = nullptr; }
        SetConsoleActiveScreenBuffer(m_pCoutOrig);
        system("\a");
    }

    // --setters
    void ConsoleEngine::SetTitle(const char* strTitle) { m_cwInfo.strTitle = strTitle; }

    void ConsoleEngine::SetWndInfo(const CWindowInfo& rcwInfo) {
        m_cwInfo.whMaxSize = GetLargestConsoleWindowSize(m_pCout);
        if (rcwInfo.GetWidth() > m_cwInfo.whMaxSize.X || rcwInfo.GetHeight() > m_cwInfo.whMaxSize.Y) { Quit(); return; }
        m_cwInfo.xywhRect = rcwInfo.xywhRect;
    }
    void ConsoleEngine::SetPxInfo(const CPixelInfo& rcpxInfo) {
        m_cpxInfo.dwFontSize = rcpxInfo.dwFontSize;
        m_cpxInfo.FontFamily = FF_DONTCARE;
        m_cpxInfo.FontWeight = FW_NORMAL;
        m_cpxInfo.nFont = 0;
        swprintf_s(m_cpxInfo.FaceName, L"Consolas");
        m_cpxInfo.cbSize = sizeof(m_cpxInfo);
    }
    void ConsoleEngine::SetFBInfo(const CFrameBufInfo& rfbInfo) {
        m_cwInfo.whMaxSize = GetLargestConsoleWindowSize(m_pCout);
        if (rfbInfo.dwSize.X > m_cwInfo.whMaxSize.X || rfbInfo.dwSize.Y > m_cwInfo.whMaxSize.Y) { Quit(); return; }
        m_cfbInfo = rfbInfo;
    }

    bool ConsoleEngine::ResetWindow() {
        {   // framebuffer
            if (m_cPixels != nullptr) { delete[] m_cPixels; m_cPixels = nullptr; m_szPixels = 0; }
            if (m_cfbInfo.dwSize.X <= 0 || m_cfbInfo.dwSize.Y <= 0) { Quit(); return false; }

            m_szPixels = static_cast<Size>(m_cfbInfo.dwSize.X) * static_cast<Size>(m_cfbInfo.dwSize.Y);
            m_cPixels = new CPixel[m_szPixels];

            m_cfbInfo.dwMaximumWindowSize = m_cwInfo.whMaxSize;
            m_cfbInfo.srWindow = m_cwInfo.xywhRect;
            m_cfbInfo.wAttributes = 0b0000'1010;
            m_cfbInfo.wPopupAttributes = 0b0000'0010;
            m_cfbInfo.bFullscreenSupported = 1;
            m_cfbInfo.dwCursorPosition = V2xy{ 0, 0 };
            m_cfbInfo.cbSize = sizeof(m_cfbInfo);
            // in the hex every 2 digits are one byte;
            // here is abgr representation from left to right
            // or rgba from right to left
            // Here I make monochromatic pallete
            for (UInt8 cli = 0; cli < 16; cli++) m_cfbInfo.ColorTable[cli] = 0x11'11'11 * cli;

            if (!SetConsoleScreenBufferSize(m_pCout, m_cfbInfo.dwSize)) { Quit(); return false; }
            if (!SetConsoleScreenBufferInfoEx(m_pCout, &m_cfbInfo)) { Quit(); return false; }
            if (!SetConsoleScreenBufferSize(m_pCout, m_cfbInfo.dwSize)) { Quit(); return false; }
            if (!SetConsoleActiveScreenBuffer(m_pCout)) { Quit(); return false; }
        }
        {   // pixels
            if (!SetCurrentConsoleFontEx(m_pCout, TRUE, &m_cpxInfo)) { Quit(); return false; }
        }
        {   // window
            if (!SetConsoleWindowInfo(m_pCout, TRUE, &m_cwInfo.xywhRect)) { Quit(); return false; }
        }
        return true;
    }

    // --<core_methods>--
    bool ConsoleEngine::Init(CWindowInfo& rcwInfo, CPixelInfo& rcpxInfo, CFrameBufInfo& rfbInfo)
    {
        m_bIsRunning = true;

        m_pCoutOrig = GetStdHandle(STD_OUTPUT_HANDLE);
        m_pCinOrig = m_pCin = GetStdHandle(STD_INPUT_HANDLE);

        if (m_pCoutOrig == INVALID_HANDLE_VALUE || m_pCinOrig == INVALID_HANDLE_VALUE) { return false; }

        if (m_pCout != nullptr) { delete m_pCout; m_pCout = nullptr; }
        if ((m_pCout = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
            0, NULL, CONSOLE_TEXTMODE_BUFFER, m_cPixels)) == nullptr) { Quit(); return false; }

        m_cwInfo.xywhRect = V4xywh{ 0, 0, 1, 1 };
        SetConsoleWindowInfo(m_pCout, TRUE, &m_cwInfo.xywhRect);

        SetConsoleMode(m_pCout, NC_INPUT_FLAGS);

        SetWndInfo(rcwInfo);
        SetPxInfo(rcpxInfo);
        SetFBInfo(rfbInfo);
        if (!ResetWindow()) { Quit(); return false; }

        return true;
    }
    void ConsoleEngine::Quit()
    {
        m_bIsRunning = false;
        system("\a");
    }
    void ConsoleEngine::Update() {
        if (!m_bIsRunning) { return; }

        //WriteConsoleOutputW(m_pCout, m_cPixels, m_cfbInfo.dwSize,
        //    { 0, 0 }, &m_cwInfo.xywhRect);

        m_currTime = std::chrono::steady_clock::now();
        m_deltaTime = (m_currTime - m_lastTime).count();
        m_lastTime = m_currTime;

        Char strTitle[128];
        sprintf_s(strTitle, 128, "%s::UPS: %f\0",
            &m_cwInfo.strTitle[0], m_deltaTime / 1000.0f);
        SetConsoleTitleA(strTitle);

        OnEvent();
    }
    void ConsoleEngine::OnEvent() {
        GetNumberOfConsoleInputEvents(m_pCin, &m_cevInfo.unEvGetCount);

        if (m_cevInfo.unEvGetCount > 0) {
            ReadConsoleInputA(m_pCin, m_cevInfo.irEvents, m_cevInfo.unEvGetCount, &m_cevInfo.unEvReadCount);
            for (UInt16 evi = 0; evi < m_cevInfo.unEvGetCount; evi++) {
                MOUSE_EVENT_RECORD& rmsevt = m_cevInfo.irEvents[evi].Event.MouseEvent;
                KEY_EVENT_RECORD& rkevt = m_cevInfo.irEvents[evi].Event.KeyEvent;
                
                WINDOW_BUFFER_SIZE_RECORD& rwszevt = m_cevInfo.irEvents[evi].Event.WindowBufferSizeEvent;
                MENU_EVENT_RECORD& rmnevt = m_cevInfo.irEvents[evi].Event.MenuEvent;
                FOCUS_EVENT_RECORD& rfevt = m_cevInfo.irEvents[evi].Event.FocusEvent;
                
                switch (m_cevInfo.irEvents[evi].EventType) {
                case EC_MOUSE:
                    switch (m_cevInfo.irEvents[evi].Event.MouseEvent.dwEventFlags) {
                    case ET_MOUSE_MOVED:
                        m_cevInfo.MouseInfo.xyMove = rmsevt.dwMousePosition;
                    case ET_VSCROLL:
                        break;
                    case ET_HSCROLL:
                        break;
                    case 0:
                        for (UInt8 mi = 0; mi < MSB_COUNT; mi++) {
                            m_cevInfo.MouseInfo.bsButtons[mi].bNext = (1 << mi) && rmsevt.dwControlKeyState;
                        }
                        break;
                    }
                case EC_KEYBOARD:
                    m_cevInfo.KeyboardInfo.bsButtons[rkevt.wVirtualKeyCode].bNext = rkevt.bKeyDown;
                    m_cevInfo.KeyboardInfo.cTypedChars[rkevt.wVirtualKeyCode].ascii = rkevt.uChar.AsciiChar;
                    m_cevInfo.KeyboardInfo.cTypedChars[rkevt.wVirtualKeyCode].unicode = rkevt.uChar.UnicodeChar;
                    break;
                case EC_FOCUS:
                    m_cwInfo.bIsFocused = true;
                    break;
                case EC_WINDOW_SIZE:
                    m_cwInfo.xywhRect = {0, 0, rwszevt.dwSize.X, rwszevt.dwSize.Y };
                    ResetWindow();
                    break;
                }
            }
        }
        for (UInt8 mi = 0; mi < MSB_COUNT; mi++) {
            ButtonState& rbs = m_cevInfo.MouseInfo.bsButtons[mi];
            rbs.bPressed = false;
            if (rbs.bNext != rbs.bLast) {
                if (rbs.bNext == true) {
                    rbs.bPressed = rbs.bHeld = true;
                }
                else {
                    rbs.bPressed = rbs.bHeld = false;
                }
            }
            rbs.bNext = rbs.bLast;
        }
        for (UInt16 ki = 0; ki < KC_COUNT; ki++) {
            ButtonState& rbs = m_cevInfo.KeyboardInfo.bsButtons[ki];
            rbs.bPressed = false;
            if (rbs.bNext != rbs.bLast) {
                if (rbs.bNext == true) {
                    rbs.bPressed = rbs.bHeld = true;
                }
                else { rbs.bHeld = false; }
            }
            rbs.bNext = rbs.bLast;
        }
    }
    // --</core_methods>--
}