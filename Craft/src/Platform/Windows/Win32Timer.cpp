#include "crpch.h"
#include "Utils\Timer.h"

namespace Craft
{
	struct Members
	{
		LARGE_INTEGER m_Start;
		double m_Frequency;
	};

	Timer::Timer()
		: m_Members(new (m_Reserved) Members())
	{
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);
		m_Members->m_Frequency = 1.0 / frequency.QuadPart;

		Reset();
	}

	Timer::~Timer()
	{
	}

	void Timer::Reset()
	{
		QueryPerformanceCounter(&m_Members->m_Start);
	}

	float Timer::Elapsed()
	{
		LARGE_INTEGER current;
		QueryPerformanceCounter(&current);
		u64 cycles = current.QuadPart - m_Members->m_Start.QuadPart;
		return (float)(cycles * m_Members->m_Frequency);
	}

	float Timer::ElapsedMillisecond()
	{
		return Elapsed() * 1000.0f;
	}
}