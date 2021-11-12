#pragma once
#include <chrono>

class ShrekTimer
{
public:
	ShrekTimer() noexcept;
	float Mark() noexcept;
	float Peek() const noexcept;
private:
	std::chrono::steady_clock::time_point last;
};