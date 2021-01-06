#include "nc_pch.hpp"
#include "nc_log_sys.h"

NC::LogFlags NC::LogSys::s_LogFlags = NC::LogFlags(
	NC::LF_WRITE_HEADER_LOGGER | NC::LF_WRITE_LOC_DIR |
	NC::LF_WRITE_LOC_FILE | NC::LF_WRITE_LOC_LINE);
NC::LogSys::ErrStack NC::LogSys::s_ErrStack;

namespace NC
{
	//
}