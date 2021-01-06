#include "ncw_pch.hpp"
#include "ncw_engine_states.h"

#include <native_console.hpp>

namespace NCW
{
	GamerState::GamerState()
	{
		//
	}
	GamerState::~GamerState()
	{
		//
	}

	// --<core_methods>--
	bool GamerState::Init()
	{
		if (!EngineState::Init()) { return false; }
		return true;
	}
	void GamerState::Update()
	{
		NC::Drawer::BeginDraw();
		NC::Drawer::EndDraw();
	}
	void GamerState::OnEnable()
	{
	}
	void GamerState::OnDisable()
	{
	}
	// --</core_methods>--

	// --<on_event_methods>--
	// --</on_event_methods>--
}