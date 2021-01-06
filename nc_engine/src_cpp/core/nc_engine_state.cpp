#include "nc_pch.hpp"
#include "nc_engine_state.h"

#include <graphics/control/nc_drawer.h>

#include <core/nc_engine.h>
#include <systems/nc_ev_sys.h>
#include <systems/nc_io_sys.h>

#include <core/lua_decl.hpp>

#include <lua.hpp>

static NC::LuaState* pLState;

namespace NC
{
	static void* LuaAlloc(void* pAllocator, void* pBlock, Size szOld, Size szNew) {
		(void)pAllocator; (void)szOld;
		if (pBlock != nullptr) {
			if (szNew == 0) { free(pBlock); return nullptr; }
			else { return realloc(pBlock, szNew); }
		}
		else { return malloc(szNew); }
	}

	EngineState::EngineState() {
		pLState = lua_newstate(LuaAlloc, nullptr);
		luaL_openlibs(pLState);
	}
	EngineState::~EngineState() {
		lua_close(pLState);
	}

	// --<core_methods>--
	bool EngineState::Init() {
		return true;
	}
	void EngineState::OnEnable() {
	}
	void EngineState::OnDisable() {
	}
	void EngineState::Update() {
		String strCmd(512, '\0');
		std::cin >> &strCmd[0];
		std::cin.getline(&strCmd[strlen(&strCmd[0])], strCmd.size(), '\n');
		luaL_loadstring(pLState, &strCmd[0]);
		std::cout << '\n';
		if (lua_pcallk(pLState, 0, 0, 0, 0, 0) != LUA_OK) {
			if (strcmp(&strCmd[0], "quit") == 0) { Engine::Get().Quit(); }
			else if (strcmp(&strCmd[0], "continue") == 0) { }
			else { __debugbreak(); }
		}
	}
	// --</core_methods>--

	// --<on_event_methods>--
	void EngineState::OnEvent(MouseEvent& rmEvt)
	{
		switch (rmEvt.EvtType) {
		case ET_MOUSE_MOVE:
			break;
		case ET_MOUSE_SCROLL:
			break;
		case ET_MOUSE_PRESS:
			break;
		case ET_MOUSE_RELEASE:
			break;
		}
	}
	void EngineState::OnEvent(KeyboardEvent& rkEvt)
	{
		switch (rkEvt.EvtType) {
		case ET_KEY_PRESS:
			switch (rkEvt.unKeyCode) {
			case NC_KEY_ENTER_13:
				break;
			case NC_KEY_BACKSPACE_8:
				break;
			}
			break;
		case ET_KEY_RELEASE:
			break;
		case ET_KEY_TYPE:
			switch (rkEvt.cChar) {
			}
			break;
		}
	}
	void EngineState::OnEvent(WindowEvent& rwEvt)
	{
		switch (rwEvt.EvtType) {
		case ET_WINDOW_RESIZE:
			break;
		case ET_WINDOW_MOVE:
			break;
		case ET_WINDOW_FOCUS:
			break;
		case ET_WINDOW_CLOSE:
			break;
		}
	}
	// --</on_event_methods>--
}