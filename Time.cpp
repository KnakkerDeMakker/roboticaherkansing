#include "Time.h"

void Time::Update()
{
	auto now = std::chrono::high_resolution_clock::now();

	//Calculate ms elapsed
	auto elapsed = now - lastTime;
	DeltaTime = (float)(elapsed.count() / 1000000);

	//Update last known time
	lastTime = now;

	//Max 60Hz
	using namespace std::chrono_literals;
	std::this_thread::sleep_for(16ms);
}

bool test_Time()
{
	try
	{
		using namespace std::chrono_literals;
		Time t;
		std::this_thread::sleep_for(1s);
		t.Update();
		if (t.DeltaTime > 1005 || t.DeltaTime < 995)
			throw "TIME ERROR";
	}
	catch (const char *e)
	{
		return false;
	}
	return true;
}
