#include <ncw_pch.hpp>
#include <native_console.hpp>

#include <core/ncw_engine_states.h>

int main(int nArgs, char** strArgs)
{
	NC::Engine* pEngine = &NC::Engine::Get();
	if (!pEngine->Init()) { return -1; }

	pEngine->Run();

	return 0;
}