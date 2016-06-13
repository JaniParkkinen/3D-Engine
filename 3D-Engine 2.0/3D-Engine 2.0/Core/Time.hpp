#ifndef Engine_Time_hpp
#define Engine_Time_hpp

#include <chrono>

namespace Engine
{
	typedef double DeltaTime;

	class Time
	{
	public:
		Time();
		~Time();
		DeltaTime Update();
		DeltaTime GetDeltaTime();
	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> _start;
		std::chrono::time_point<std::chrono::high_resolution_clock> _end;
		DeltaTime _deltaTime;
	};
};
#endif
