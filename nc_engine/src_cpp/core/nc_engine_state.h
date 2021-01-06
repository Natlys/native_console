#ifndef NC_ENGINE_STATE_H
#define NC_ENGINE_STATE_H

#include <core/nc_decl.hpp>

namespace NC
{
	/// EngineState class
	class NC_API EngineState
	{
	public:
		EngineState();
		EngineState(EngineState& rCpy) = delete;
		void operator=(EngineState& rCpy) = delete;
		virtual ~EngineState();

		// --getters
		virtual inline const char* GetName() { return "engine_state"; }
		// --setters
		
		// --core_methods
		virtual bool Init();
		virtual void Update();
		virtual void OnEnable();
		virtual void OnDisable();
		// --on_event_methods
		virtual void OnEvent(MouseEvent& rmEvt);
		virtual void OnEvent(KeyboardEvent& rkEvt);
		virtual void OnEvent(WindowEvent& rwEvt);
	};

}

#endif	// NC_ENGINE_STATE_H