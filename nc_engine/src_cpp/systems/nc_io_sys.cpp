#include <nc_pch.hpp>
#include "nc_io_sys.h"

#include <graphics/gcontext/nc_CWindow.h>

#include <systems/nc_ev_sys.h>

// Cursor state
NC::IOSys::CursorState NC::IOSys::Cursor{ 0 };
// Mouse buttons checking
NC::IOSys::BtnState NC::IOSys::s_bsMsBtns[NC_MS_BTN_LAST] { NC::IOSys::BtnState{ false, false, false, false, false } };
// Keyboard checking
NC::IOSys::BtnState NC::IOSys::s_bsKeys[NC_KEY_LAST] { NC::IOSys::BtnState{ false, false, false, false, false } };
    
double NC::IOSys::xScrollDelta{ 0.0 }, NC::IOSys::yScrollDelta{0.0f};

namespace NC
{
    void IOSys::Update()
    {
        Cursor.xMoveDelta = Cursor.yMoveDelta = 0.0f;
        INPUT_RECORD irEvents[32];
        UInt64 unEvtLeft = 0;
        GetNumberOfConsoleInputEvents(EvSys::s_pNativeWindow->pCin, &unEvtLeft);
        if (unEvtLeft != 0)
        {
            ReadConsoleInputA(EvSys::s_pNativeWindow->pCin, irEvents, unEvtLeft, &unEvtLeft);
            for (int ev = 0; ev < unEvtLeft; ev++)
            {
                switch (irEvents[ev].EventType)
                { // Check all 5 kinds of windows events
                case NC_MS_EVT:
                    _MOUSE_EVENT_RECORD msEvt = irEvents[ev].Event.MouseEvent;
                    switch (msEvt.dwEventFlags)
                    {
                    case NC_MS_MOVED:
                        EvSys::cb_mouse_coord(static_cast<double>(msEvt.dwMousePosition.X),
                            static_cast<double>(msEvt.dwMousePosition.Y));
                        break;
                    case NC_MS_WHEELED: case NC_MS_HWHEELED:
                        EvSys::cb_mouse_scroll(static_cast<double>(msEvt.dwMousePosition.X),
                            static_cast<double>(msEvt.dwMousePosition.Y));
                        break;
                    case 0: // Process buttons
                        for (Int16 m = NC_MS_BTN_0; m < NC_MS_BTN_LAST; m++)
                            EvSys::cb_mouse_button(m, msEvt.dwButtonState & (1 << m));
                        UpdateMouseButtons();
                        break;
                    }
                    break;
                case NC_KEY_EVT:
                    _KEY_EVENT_RECORD keyEvt = irEvents[ev].Event.KeyEvent;
                    EvSys::cb_keyboard(keyEvt.wVirtualKeyCode, keyEvt.wVirtualScanCode, keyEvt.bKeyDown);
                    UpdateKeyboard();
                    break;
                case NC_MENU_EVT:
                    EvSys::cb_menu(irEvents[ev].Event.MenuEvent.dwCommandId);
                    break;
                case NC_WND_SIZE_EVT:
                    EvSys::cb_window_size(irEvents[ev].Event.WindowBufferSizeEvent.dwSize.X,
                        irEvents[ev].Event.WindowBufferSizeEvent.dwSize.Y);
                    break;
                case NC_FOCUS_EVT:
                    EvSys::cb_window_focus(irEvents[ev].Event.FocusEvent.bSetFocus);
                    break;
                }
            }
        }
        UpdateKeyboard();
        UpdateMouseButtons();
    }
    void IOSys::UpdateKeyboard()
    {
        for (UInt32 ki = 0; ki < NC_KEY_LAST; ki++)
        {
            s_bsKeys[ki].bPressed = s_bsKeys[ki].bReleased = false;
            if (s_bsKeys[ki].bNew != s_bsKeys[ki].bOld) {
                if (s_bsKeys[ki].bNew == true) {
                    s_bsKeys[ki].bPressed = s_bsKeys[ki].bHeld = true;
                } else {
                    s_bsKeys[ki].bHeld = false;
                    s_bsKeys[ki].bReleased = true;
                }
            }
            s_bsKeys[ki].bOld = s_bsKeys[ki].bNew;
        }
    }
    void IOSys::UpdateMouseButtons()
    {
        for (UInt32 mi = NC_MS_BTN_0; mi < NC_MS_BTN_LAST; mi++)
        {
            s_bsMsBtns[mi].bPressed = s_bsMsBtns[mi].bReleased = false;
            if (s_bsMsBtns[mi].bNew != s_bsMsBtns[mi].bOld)
            {
                if (s_bsMsBtns[mi].bNew)
                {
                    s_bsMsBtns[mi].bPressed = s_bsMsBtns[mi].bHeld = true;
                    Cursor.xHeld = Cursor.xMove;
                    Cursor.yHeld = Cursor.yMove;
                }
                else
                {
                    s_bsMsBtns[mi].bHeld = false;
                    s_bsMsBtns[mi].bReleased = true;
                }
            }
            s_bsMsBtns[mi].bOld = s_bsMsBtns[mi].bNew;
        }
    }
}