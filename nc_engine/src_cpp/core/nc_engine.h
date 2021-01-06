#ifndef NC_ENGINE_H
#define NC_ENGINE_H

#include <core/nc_asingleton.h>

#include <core/nc_decl.hpp>
#include <core/graphics_decl.hpp>

namespace NC
{
	/// NC_Engine class
	class NC_API Engine : public ASingleton<Engine>
	{
		using States = DArray<EngineState*>;
		friend class ASingleton<Engine>;
	private:
		Engine();
	public:
		~Engine();

		// --getters
		inline CWindow* GetWindow() { return m_pWindow; }
		inline EngineState* GetCurrState() { return m_pCurrState; }
		inline EngineState* GetState(const char* strName);
		// --setters
		void AddState(EngineState* pState);
		void RemoveState(const char* strName);
		void SwitchState(const char* strName);

		// --core_methods
		bool Init();
		void Quit();
		void Run();
	private:	// engine_only methods
		void Update();
		void OnEvent(AEvent& rEvt);
	private:	// engine_only attributes
		CWindow* m_pWindow;

		const char* m_strName;
		bool m_bIsRunning;

		EngineState* m_pCurrState;
		States m_States;
	};
}

#endif	// NC_ENGINE_H