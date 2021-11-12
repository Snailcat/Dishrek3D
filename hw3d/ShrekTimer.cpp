#include "ShrekTimer.h"

using namespace std::chrono;

ShrekTimer::ShrekTimer() noexcept
{
	last = steady_clock::now();
}

float ShrekTimer::Mark() noexcept
{
	const auto old = last;
	last = steady_clock::now();
	const duration<float> frameTime = last - old;
	return frameTime.count();
}

float ShrekTimer::Peek() const noexcept
{
	return duration<float>( steady_clock::now() - last ).count();
}
