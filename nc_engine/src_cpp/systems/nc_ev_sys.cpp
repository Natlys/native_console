#include <nc_pch.hpp>
#include "nc_ev_sys.h"

#include <core/nc_Engine.h>
#include <systems/nc_io_sys.h>
#include <systems/nc_time_sys.h>

NC::CWindow* NC::EvSys::s_pAppWindow(nullptr);
NC::NativeWindow* NC::EvSys::s_pNativeWindow{ nullptr };
bool NC::EvSys::s_bWindowFocused(false);

namespace NC
{
    // --==<Core Methods>==--
    bool EvSys::Init()
    {
        s_pAppWindow = Engine::Get().GetWindow();
        s_pNativeWindow = s_pAppWindow->GetNative();
        return true;
    }
    void EvSys::OnQuit()
    {
    }
    void EvSys::Update()
    {
    }

    // --==<Console Callback functions>==--
    // --input callback: mouse
    void EvSys::cb_mouse_coord(Float64 xCrd, Float64 yCrd)
    {
        IOSys::Cursor.xMoveDelta = IOSys::Cursor.xMove - xCrd;
        IOSys::Cursor.yMoveDelta = IOSys::Cursor.yMove - yCrd;
        IOSys::Cursor.xMove = xCrd; IOSys::Cursor.yMove = yCrd;

        MouseEvent mEvt(ET_MOUSE_MOVE, xCrd, yCrd);
        s_pAppWindow->GetInfo().cbOnEvent(mEvt);
    }
    void EvSys::cb_mouse_scroll(Float64 xCrd, Float64 yCrd)
    {
        IOSys::xScrollDelta = xCrd;
        IOSys::yScrollDelta = yCrd;

        MouseEvent mEvt(ET_MOUSE_SCROLL, xCrd, yCrd);
        s_pAppWindow->GetInfo().cbOnEvent(mEvt);
    }
    void EvSys::cb_mouse_button(Int32 nButton, Int32 nAction)
    {
        if (nAction == NC_RELEASE) {
            IOSys::s_bsMsBtns[nButton].bNew = false;
            MouseEvent mEvt(ET_MOUSE_RELEASE, nButton);
            s_pAppWindow->GetInfo().cbOnEvent(mEvt);
        }
        else if (nAction == NC_PRESS) {
            IOSys::s_bsMsBtns[nButton].bNew = true;
            MouseEvent mEvt(ET_MOUSE_PRESS, nButton);
            s_pAppWindow->GetInfo().cbOnEvent(mEvt);
        }
    }
    // --input callback: keyboard
    void EvSys::cb_keyboard(Int32 nKey, Int32 nScanCode, Int32 nAction)
    {
        if (nAction == NC_RELEASE) {
            IOSys::s_bsKeys[nKey].bNew = false;
            KeyboardEvent kEvt(ET_KEY_RELEASE, nKey);
            s_pAppWindow->GetInfo().cbOnEvent(kEvt);
        }
        else if (nAction == NC_PRESS) {
            IOSys::s_bsKeys[nKey].bNew = true;
            KeyboardEvent kEvt(ET_KEY_PRESS, nKey);
            s_pAppWindow->GetInfo().cbOnEvent(kEvt);
        }
        Char cChar = Char(nKey);
        if (std::isgraph(cChar)) {
            if (IOSys::GetKeyHeld(NC_KEY_SHIFT_LEFT)) { cChar = std::toupper(cChar); }
            else { cChar = std::tolower(cChar); }
            cb_keyboard_char(cChar);
        }
    }
    void EvSys::cb_keyboard_char(Char cChar)
    {
        KeyboardEvent kEvt(cChar);
        s_pAppWindow->GetInfo().cbOnEvent(kEvt);
    }
    // --window callbacks
    void EvSys::cb_menu(Int32 nCmdId)
    {
    }
    void EvSys::cb_window_size(Int32 nW, Int32 nH)
    {
        WindowEvent wEvt(ET_WINDOW_RESIZE, nW, nH);
        s_pAppWindow->GetInfo().cbOnEvent(wEvt);
    }
    void EvSys::cb_window_focus(Int32 nFocus)
    {
        s_bWindowFocused = nFocus;
        WindowEvent wEvt(ET_WINDOW_FOCUS, nFocus);
        s_pAppWindow->GetInfo().cbOnEvent(wEvt);
    }
    // --==</Console Callback functions>==--
}