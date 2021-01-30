#include "cmd_pch.hpp"
#include "cmd_engine.h"

#define CMD_INPUT_FLAGS ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT

namespace CMD
{
    CmdEngine::CmdEngine() :
        m_cwInfo(CWindowInfo()),
        m_cpxInfo(CPixelInfo()),
        m_pfbCur(nullptr),
        m_pCout(nullptr), m_pCin(nullptr)
    {
        this->SetWndSize(50, 20);
        this->SetPxSize(8, 16);
        m_pCout = GetStdHandle(STD_OUTPUT_HANDLE);
        m_pCin = GetStdHandle(STD_INPUT_HANDLE);
        m_cwInfo.strTitle = "cwindow";
    }
    CmdEngine::~CmdEngine() { }

    // --setters
    void CmdEngine::SetTitle(const char* strTitle) { m_cwInfo.strTitle = strTitle; SetConsoleTitleA(&strTitle[0]); }
    void CmdEngine::SetWndSize(UInt16 unWidth, UInt16 unHeight) {
        m_cwInfo.xywhRect.Left = m_cwInfo.xywhRect.Top = 0;
        m_cwInfo.xywhRect.Right = unWidth; m_cwInfo.xywhRect.Bottom = unHeight;
        for (auto& itBuf : m_fbs) { itBuf.SetSizeWH(GetWndWidth(), GetWndHeight()); }
    }
    void CmdEngine::SetPxSize(UInt16 nWidth, UInt16 nHeight){
        m_cpxInfo.dwFontSize.X = nWidth;
        m_cpxInfo.dwFontSize.Y = nHeight;
        m_cpxInfo.FontFamily = FF_DONTCARE;
        m_cpxInfo.FontWeight = FW_NORMAL;
        m_cpxInfo.nFont = 0;
        swprintf_s(m_cpxInfo.FaceName, L"Consolas");
        m_cpxInfo.cbSize = sizeof(m_cpxInfo);
    }

    void CmdEngine::SetWndInfo(const CWindowInfo& rcwInfo) { m_cwInfo = rcwInfo; SetConsoleWindowInfo(m_pfbCur->GetNative(), TRUE, &m_cwInfo.xywhRect); }
    void CmdEngine::SetPxInfo(const CPixelInfo& rcpxInfo) { m_cpxInfo = rcpxInfo; }
    void CmdEngine::SetCursorInfo(const CCursorInfo& rcurInfo) { m_curInfo = rcurInfo; SetConsoleCursorInfo(m_pfbCur->GetNative(), &m_curInfo); }
    
    // --<core_methods>--
    void CmdEngine::Run() {
        Init();
        if (!m_bIsRunning) { return; }

        auto fnUpdate = [this]()->void { while (m_bIsRunning) { Update(); } Quit(); };
        m_thrRun = Thread(fnUpdate);
    }
    bool CmdEngine::Init()
    {
        if (m_bIsRunning) { return false; }
        m_bIsRunning = true;
        m_Memory = MemArena(new Byte[1 << 20], 1 << 20);
        
        SetTitle(&m_cwInfo.strTitle[0]);
        if (!SetConsoleMode(m_pCin, CMD_INPUT_FLAGS)) { Quit(); return false; }
        
        auto fnRemakeFrameBuf = [this](CmdFrameBuf& cfb) {
            CFrameBufInfo fbInfo;
            fbInfo.cbSize = sizeof(fbInfo);
            fbInfo.dwSize = { GetWndWidth() + 1, GetWndHeight() + 1 };
            fbInfo.srWindow = m_cwInfo.xywhRect;
            fbInfo.wAttributes = 0b0000'1010;
            fbInfo.wPopupAttributes = 0b0000'0010;
            fbInfo.bFullscreenSupported = 1;
            fbInfo.dwCursorPosition = V2xy{ 0, 0 };
            for (UInt8 cli = 0; cli < 16; cli++) { fbInfo.ColorTable[cli] = 0x11'11'11 * cli; }

            m_cwInfo.whMaxSize = GetLargestConsoleWindowSize(m_pCout);
            if (m_cwInfo.GetHeight() > m_cwInfo.whMaxSize.Y) { m_cwInfo.xywhRect.Top = 0; m_cwInfo.xywhRect.Bottom = m_cwInfo.whMaxSize.Y; }
            if (m_cwInfo.GetHeight() > m_cwInfo.whMaxSize.Y) { m_cwInfo.xywhRect.Top = 0; m_cwInfo.xywhRect.Bottom = m_cwInfo.whMaxSize.Y; }

            V4xywh xywhMinRect = { 0, 0, 1, 1 };
            if (!SetConsoleWindowInfo(cfb.GetNative(), TRUE, &xywhMinRect)) { Quit(); return; }
            if (!SetCurrentConsoleFontEx(cfb.GetNative(), TRUE, &m_cpxInfo)) { Quit(); return; }
            cfb.SetInfo(fbInfo);
            cfb.Remake();
            if (!SetConsoleWindowInfo(cfb.GetNative(), TRUE, &m_cwInfo.xywhRect)) { Quit(); return; }
        };
        fnRemakeFrameBuf(m_fbs[0]);
        fnRemakeFrameBuf(m_fbs[1]);
        SwapBuffers();

        return m_bIsRunning;
    }
    void CmdEngine::Quit()
    {
        if (!m_bIsRunning) { return; }
        m_bIsRunning = false;
        
        delete[] m_Memory.GetDataBeg();
        m_Memory = MemArena(nullptr, 0);
        SetConsoleActiveScreenBuffer(m_pCout);
    }

    void CmdEngine::Update()
    {
        SwapBuffers();
        PollEvents();
    }
    void CmdEngine::PollEvents()
    {
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
                case CMD_MS_EVT:
                    switch (m_cevInfo.irEvents[evi].Event.MouseEvent.dwEventFlags) {
                    case CMD_MS_MOVED:
                        m_cevInfo.msInfo.xMove = rmsevt.dwMousePosition.X;
                        m_cevInfo.msInfo.yMove = rmsevt.dwMousePosition.Y;
                        break;
                    default:
                        for (UInt8 mi = 0; mi < CMD_MS_BTN_COUNT; mi++) { m_cevInfo.msInfo.bsButtons[mi].bNew = ((1 << mi) & rmsevt.dwButtonState) > 0; }
                        break;
                    }
                case CMD_KEY_EVT:
                    m_cevInfo.kbInfo.bsKeys[rkevt.wVirtualKeyCode].bNew = rkevt.bKeyDown;
                    m_cevInfo.kbInfo.aChars[rkevt.wVirtualKeyCode] = rkevt.uChar.AsciiChar;
                    m_cevInfo.kbInfo.wChars[rkevt.wVirtualKeyCode] = rkevt.uChar.UnicodeChar;
                    break;
                case CMD_FOCUS_EVT:
                    m_cwInfo.bIsFocused = rfevt.bSetFocus;
                    break;
                case CMD_WND_SIZE_EVT:
                    m_cwInfo.xywhRect = { 0, 0, rwszevt.dwSize.X, rwszevt.dwSize.Y };
                    break;
                }
            }
        }

        for (UInt8 mi = 0; mi < MSB_COUNT; mi++) {
            ButtonState& rbs = m_cevInfo.msInfo.bsButtons[mi];
            rbs.bPressed = rbs.bReleased = false;
            if (rbs.bNew != rbs.bOld) {
                if (rbs.bNew == true) {
                    m_cevInfo.msInfo.xHeld[mi] = m_cevInfo.msInfo.xMove;
                    m_cevInfo.msInfo.yHeld[mi] = m_cevInfo.msInfo.yMove;
                    rbs.bPressed = rbs.bHeld = true;
                }
                else {
                    rbs.bReleased = true; rbs.bHeld = false;
                }
            }
            rbs.bOld = rbs.bNew;
        }
        for (UInt16 ki = 0; ki < KC_COUNT; ki++) {
            ButtonState& rbs = m_cevInfo.kbInfo.bsKeys[ki];
            rbs.bPressed = rbs.bReleased = false;
            if (rbs.bNew != rbs.bOld) {
                if (rbs.bNew == true) {
                    rbs.bPressed = rbs.bHeld = true;

                }
                else {
                    rbs.bReleased = true; rbs.bHeld = false;
                }
            }
            rbs.bOld = rbs.bNew;
        }
    }
    void CmdEngine::OnEvent(AEvent& rEvt)
    {
    }
    void CmdEngine::SwapBuffers()
    {
        m_pfbCur = (m_pfbCur == &m_fbs[0]) ? &m_fbs[1] : &m_fbs[0];
        if (!SetConsoleActiveScreenBuffer(m_pfbCur->GetNative())) { Quit(); return; }
        if (!WriteConsoleOutputW(m_pfbCur->GetNative(), &m_pfbCur->GetPxData()[0],
            { m_pfbCur->GetWidth(), m_pfbCur->GetHeight() }, { 0, 0 }, &m_pfbCur->GetInfo().srWindow)) { Quit(); return; }
    }
    // --</core_methods>--
}