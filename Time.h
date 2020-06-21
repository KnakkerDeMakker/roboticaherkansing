#pragma once
#include <chrono>
#include <thread>

class Time
{
#ifndef _WIN32
	std::chrono::_V2::system_clock::time_point lastTime;
#else
	std::chrono::time_point<std::chrono::high_resolution_clock> lastTime;
#endif

public:
	Time() : lastTime(std::chrono::high_resolution_clock::now()) {};
	float DeltaTime;
	void Update();
};

bool test_Time();
