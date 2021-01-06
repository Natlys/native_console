#ifndef NC_TIME_H
#define NC_TIME_H

#include <nc_core.hpp>

namespace NC
{
	/// RealTimeCounter class
	/// Description:
	/// -- Counts real time during "BeginCount" - "EndCount" calls
	/// -- Counts own life time
	class NC_API RealTimeCounter
	{
	public:
		RealTimeCounter();
		~RealTimeCounter() = default;

		// -- Getters
		inline float GetCreationTime() { return m_nCreationTime; }
		inline float GetCountedTime() { return m_nEndTime - m_nBeginTime; }
		// -- Setters
		void BeginCount();
		void EndCount();

		// -- Core Methods
	private:
		float m_nBeginTime;
		float m_nEndTime;
		float m_nCreationTime;
	};
	/// AppTimeCounter class
	/// Description:
	/// -- Same as RealTimer but counts application time
	class NC_API AppTimeCounter
	{
	public:
		AppTimeCounter();
		~AppTimeCounter() = default;

		// -- Getters
		inline float GetCreationTime() { return m_nCreationTime; }
		inline float GetCountedTime() { return m_nEndTime - m_nBeginTime; }
		// -- Setters
		void BeginCount();
		void EndCount();

		// -- Core Methods
	private:
		float m_nBeginTime;
		float m_nEndTime;
		float m_nCreationTime;
	};
}

#endif // CN_TIME_H