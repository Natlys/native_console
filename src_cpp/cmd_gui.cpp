#include <cmd_pch.hpp>
#include <cmd_gui.h>

#include <cmd_engine.h>

CMD::IdStack CMD::CWidget::s_IdStack = CMD::IdStack();

namespace CMD
{
	CWidget::CWidget() : m_unId(0), m_strName("cwidget") {
		m_unId = s_IdStack.GetFreeId();
		m_strName = m_strName + "_" + std::to_string(m_unId);
		CmdEngine::Get().AddWidget(this);
	}
	CWidget::CWidget(const char* strName) : m_unId(0), m_strName(strName) {
		m_unId = s_IdStack.GetFreeId();
		m_strName = m_strName + "_" + std::to_string(m_unId);
		CmdEngine::Get().AddWidget(this);
	}
	CWidget::~CWidget(){
		s_IdStack.SetFreeId(m_unId);
		CmdEngine::Get().RmvWidget(m_unId);
	}
}