#include <nc_pch.hpp>
#include "nc_adata_res.h"

NC::ADataRes::IdStack NC::ADataRes::s_IdStack = DStack<UInt32>();

namespace NC
{
	ADataRes::ADataRes() :
		m_unId(0)
	{
		if (s_IdStack.size() == 1) m_unId = s_IdStack.top()++;
		else if (s_IdStack.size() > 1) { m_unId = s_IdStack.top(); s_IdStack.pop(); }
		else if (s_IdStack.size() == 0) { s_IdStack.push(1); }
	}
	ADataRes::ADataRes(const ADataRes& rDataRes) :
		m_unId(0)
	{
		if (s_IdStack.size() == 1) m_unId = s_IdStack.top()++;
		else if (s_IdStack.size() > 1) { m_unId = s_IdStack.top(); s_IdStack.pop(); }
		else if (s_IdStack.size() == 0) { s_IdStack.push(1); }
	}
	ADataRes::~ADataRes()
	{
		if (s_IdStack.top() == m_unId) s_IdStack.pop();
		s_IdStack.push(m_unId);
	}
}