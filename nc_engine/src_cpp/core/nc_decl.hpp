#ifndef NC_DECL_HPP
#define NC_DECL_HPP

#include <nc_core.hpp>

namespace NC
{
	// --global
	class NC_API Engine;
	class NC_API EngineState;
	// --systems
	class NC_API EvSys;
	class NC_API TimeSys;
	class NC_API IOSys;
	// --important abstractions
	class NC_API ADataRes;
	
	struct NC_API AEvent;
	struct NC_API MouseEvent;
	struct NC_API KeyboardEvent;
	struct NC_API WindowEvent;

	template <class CType> class NC_API ASingleton;
	// --enums
	enum EventTypes : UInt32 {
		ET_NONE = 0,
		ET_WINDOW_CLOSE, ET_WINDOW_RESIZE, ET_WINDOW_MOVE, ET_WINDOW_FOCUS,
		ET_APP_TICK, ET_APP_UPDATE, ET_APP_RENDER,
		ET_MOUSE_MOVE, ET_MOUSE_SCROLL, ET_MOUSE_PRESS, ET_MOUSE_RELEASE,
		ET_KEY_RELEASE, ET_KEY_PRESS, ET_KEY_TYPE
	};
}

#endif	// NC_DECL_HPP