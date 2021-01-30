#include <cmd_pch.hpp>
#include "cmd_framebuf.h"

#include <cmd_engine.h>

namespace CMD
{
	CmdFrameBuf::CmdFrameBuf():m_pCout(nullptr),
		m_szPxCount(0), m_pPxData(nullptr),
		m_cpxClear(CPixel{ CPT_SOLID, CCN_BG_1 | CCN_FG_1 }),
		m_Info(CFrameBufInfo())
	{
		m_pCout = CreateConsoleScreenBuffer(GENERIC_WRITE | GENERIC_READ, NULL, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	}
	CmdFrameBuf::~CmdFrameBuf() { CloseHandle(m_pCout); }

    // --setters

    // --==<core_methods>==--
    void CmdFrameBuf::Remake() {
		if (m_pPxData != nullptr) {
			DelTArr<CPixel>(CmdEngine::Get().GetMemory(), m_pPxData, m_szPxCount);
			m_pPxData = nullptr;
			m_szPxCount = 0;
		}
		m_Info.dwMaximumWindowSize = GetLargestConsoleWindowSize(m_pCout);

		m_szPxCount = static_cast<Size>(GetWidth()) * static_cast<Size>(GetHeight());
		m_pPxData = NewTArr<CPixel>(CmdEngine::Get().GetMemory(), m_szPxCount);
		memset(m_pPxData, 0, m_szPxCount * sizeof(CPixel));
	
		if (!SetConsoleScreenBufferInfoEx(m_pCout, &m_Info)) { return; }
		if (!SetConsoleScreenBufferSize(m_pCout, m_Info.dwSize)) { return; }
	}
    // --==</core_methods>==--
}