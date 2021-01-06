#ifndef NCW_ENGINE_STATES_H
#define NCW_ENGINE_STATES_H

#include <core/nc_engine_state.h>

namespace NCW
{
	class GamerState : public NC::EngineState
	{
	public:
		GamerState();
		virtual ~GamerState();

		// --getters
		virtual inline const char* GetName() override { return "gamer_state"; }
		// --setters
		
		// --core_methods
		virtual bool Init() override;
		virtual void Update() override;
		virtual void OnEnable() override;
		virtual void OnDisable() override;
		// --on_event_methods
	};
}

#endif	// NCW_ENGINE_STATES_H