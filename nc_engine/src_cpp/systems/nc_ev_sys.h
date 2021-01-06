#ifndef NC_EVENT_SYSTEM_H
#define NC_EVENT_SYSTEM_H
#include <library/nc_aevent.h>

#include <graphics/gcontext/nc_cwindow.h>

namespace NC
{
	/// EventSystem static class
	/// -- Has static callback function for the window
	/// -- Keeps tracking of new events, Updates Time and InOut systems
	class NC_API EvSys
	{
	public:
		static CWindow* s_pAppWindow;
		static NativeWindow* s_pNativeWindow;
	public:
		// -- Getters

		// --------<Core Methods>--------
		static bool Init();
		static void OnQuit();
		static void Update();
		// --------</Core Methods>--------

		// ========<Console Callback Functions>========
		// --input callbacks: mouse
		static void cb_mouse_coord(Float64 xCrd, Float64 yCrd);
		static void cb_mouse_scroll(Float64 xCrd, Float64 yCrd);
		static void cb_mouse_button(Int32 nButton, Int32 nAction);
		// --input callbacks:keyboard
		static void cb_keyboard(Int32 nKey, Int32 nScanCode, Int32 nAction);
		static void cb_keyboard_char(Char cChar);
		// --window callbacks
		static void cb_menu(Int32 nCmdId);
		static void cb_window_size(Int32 nWidth, Int32 nHeight);
		static void cb_window_focus(Int32 nFocus);
		// ========</Console Callback Functions>========
	private: // Implementation Wizardy
		static bool s_bWindowFocused;
	};
}
#endif	// NC_EVENT_SYSTEM_H

/*
* Development started: 18.10.2020
* By MichailRis tutorial
* 31.10.2020
* Improved with the tutorials of Cherno
*/