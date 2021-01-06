#include <nc_pch.hpp>
#include "nc_time_sys.h"

float NC::TimeSys::s_nRealTime(0.0f), NC::TimeSys::s_nRealDelta(0.0f), NC::TimeSys::s_nRealLast(0.0f);
float NC::TimeSys::s_nAppTime(0.0f), NC::TimeSys::s_nAppDelta(0.0f), NC::TimeSys::s_nAppLast(0.0f);
float NC::TimeSys::s_nTimeSpeed(1.0f);

NC::RealTimeCounter NC::TimeSys::s_RealTimeCounter = RealTimeCounter();
NC::AppTimeCounter NC::TimeSys::s_AppTimeCounter = AppTimeCounter();

#if (defined NC_PLATFORM_WINDOWS)   // chrono library timing
    static std::chrono::steady_clock::time_point s_tpCurrTime;
    static std::chrono::steady_clock::time_point s_tpLastTime;
    static std::chrono::duration<float> s_dfDeltaTime;
#endif  // CN_WINDOW

namespace NC
{
    // ========<Core Methods>========
    void TimeSys::Update()
    {
#if (defined NC_PLATFORM_WINDOWS)
        s_tpCurrTime = std::chrono::steady_clock::now();
        s_dfDeltaTime = s_tpCurrTime - s_tpLastTime;
        s_tpLastTime = s_tpCurrTime;
        
        //s_nRealTime = std::chrono::duration(s_tpCurrTime);
        s_nRealDelta = s_dfDeltaTime.count();
#endif // CN_WINDOW_GLFW
    }
    // ========</Core Methods>========
}