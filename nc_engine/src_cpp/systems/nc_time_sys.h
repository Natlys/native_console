#ifndef NC_TIME_SYSTEM_H
#define NC_TIME_SYSTEM_H
#include <library/nc_time.h>

#include <core/nc_decl.hpp>

namespace NC
{
	/// TimeSystem static class
	/// Description:
	/// -- The class for getting time. Update Method updates values
	class NC_API TimeSys
	{
	public:
		friend class EvSys;
	public:
		// -- Getters
		static inline float GetRealLast() { return s_nRealLast; }
		static inline float GetRealTime() { return s_nRealTime; }
		static inline float GetRealDelta() { return s_nRealDelta; }
		static inline RealTimeCounter& GetRealTimeCounter() { return s_RealTimeCounter; }

		static inline float GetAppTime() { return s_nAppTime; }
		static inline float GetAppLast() { return s_nAppLast; }
		static inline float GetAppDelta() { return s_nAppDelta; }
		static inline float GetAppSpeed() { return s_nTimeSpeed; }
		static inline AppTimeCounter& GetAppTimeCounter() { return s_AppTimeCounter; }
		// -- Setters
		static inline void SetAppSpeed(float nSpeed) { s_nTimeSpeed = nSpeed; }

		// -- Core Methods
		static void Update();
	private:
		// Time: current frame, last frame and the difference between them
		static float s_nAppTime, s_nAppDelta, s_nAppLast;
		static float s_nRealTime, s_nRealDelta, s_nRealLast;
		static float s_nTimeSpeed;

		static RealTimeCounter s_RealTimeCounter;
		static AppTimeCounter s_AppTimeCounter;
	};
}

#endif // NC_TIME_SYSTEM_H