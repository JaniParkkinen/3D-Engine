#include <Core/Time.hpp>

namespace Engine {
	Time::Time( ) {
		_start	= std::chrono::high_resolution_clock::now( );
		_end	= _start;
	};

	DeltaTime Time::Update( ) {
		_start		= _end;
		_end		= std::chrono::high_resolution_clock::now( );
		_deltaTime	= std::chrono::duration<double>( _end - _start ).count( );
		return _deltaTime;
	};

	DeltaTime Time::GetDeltaTime( ) {
		return _deltaTime;
	};
};