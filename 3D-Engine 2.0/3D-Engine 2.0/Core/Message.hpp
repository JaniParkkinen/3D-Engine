#ifndef Engine_Message_hpp
#define Engine_Message_hpp

#include <Windows.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <exception>
#include <time.h>
#include <ctime>
#include <chrono>
#include <string>

//Trace	- Only when I would be "tracing" the code and trying to find one part of a function specifically
//Debug	- Information that is diagnostically helpful to people more than just developers (IT, sysadmins, etc)
//Info	- Generally useful information to log (service start / stop, configuration assumptions, etc). Info I want to always have available but usually dont care about under normal circumstances. This is my out - of - the - box config level
//Warn	- Anything that can potentially cause application oddities, but for which I am automatically recoverring(such as switching from a primary to backup server, retrying an operation, missing secondary data, etc)
//Error	- Any error which is fatal to the operation but not the service or application (cant open a required file, missing data, etc). These errors will force user (administrator, or direct user) intervention. These are usually reserved (in my apps) for incorrect connection strings, missing services, etc.
//Fatal	- Any error that is forcing a shutdown of the service or application to prevent data loss (or further data loss). I reserve these only for the most heinous errors and situations where there is guaranteed to have been data corruption or loss.

//GrayWizardx - StackOverflow 8.1.2010
//http://stackoverflow.com/questions/2031163/when-to-use-log-level-warn-vs-error

namespace Engine {
	enum class MessageType : size_t {
		Trace,
		Debug,
		Info,
		Warning,
		Error,
		Fatal
	};

	void MessageFunction( int line, const char* file, std::string message, MessageType type ) {
		//Store message in temporary container and convert line end to null
		size_t i = 0;
		while ( message[ i ] != NULL ) {
			if ( message[ i ] == '\n' ) { message[ i ] = NULL; };
			i++;
		}

		std::wstringstream Msg;

		//Get time and format it
		std::time_t timeNow = std::chrono::system_clock::to_time_t( std::chrono::system_clock::now( ) );
		char str[ 26 ];
		ctime_s( str, sizeof( str ), &timeNow );
		for ( i = 0; i < 24; i++ ) { Msg << str[ i ]; }; Msg << ": ";

		//Handle each type of error separately
		switch ( type ) {
			case MessageType::Trace:
			{
				#ifdef _DEBUG
				Msg << "[TRACE] " << message.c_str( ) << std::endl;
				OutputDebugString( Msg.str( ).c_str( ) );
				#endif
				break;
			}
			case MessageType::Debug:
			{
				#ifdef _DEBUG
				Msg << "[DEBUG] " << message.c_str( ) << "\n\t\t\t\t    File: " << file << "\n\t\t\t\t    Line: " << line << std::endl;
				OutputDebugString( Msg.str( ).c_str( ) );
				#endif
				break;
			}
			case MessageType::Info:
			{
				#ifdef _DEBUG
				Msg << "[INFO] " << message.c_str( ) << std::endl;
				OutputDebugString( Msg.str( ).c_str( ) );
				#endif
				break;
			}
			case MessageType::Warning:
			{
				#ifdef _DEBUG
				Msg << "[WARNING] " << message.c_str( ) << "\n\t\t\t\t    File: " << file << "\n\t\t\t\t    Line: " << line << std::endl;
				OutputDebugString( Msg.str( ).c_str( ) );

				std::wofstream log_file( "MessageLog.txt", std::ios_base::out | std::ios_base::app );
				std::wstringstream fileMsg;
				for ( i = 0; i < 24; i++ ) { fileMsg << str[ i ]; }; fileMsg << ": ";
				fileMsg << "[WARNING] " << message.c_str( ) << "\n\t\t    File: " << file << "\n\t\t    Line: " << line << std::endl;
				log_file << fileMsg.str( );
				log_file.close( );
				#endif
				break;
			}
			case MessageType::Error:
			{
				#ifdef _DEBUG
				Msg << "[ERROR] " << message.c_str( ) << "\n\t\t\t\t    File: " << file << "\n\t\t\t\t    Line: " << line << std::endl;
				OutputDebugString( Msg.str( ).c_str( ) );
				#endif
				std::wofstream log_file( "MessageLog.txt", std::ios_base::out | std::ios_base::app );
				std::wstringstream fileMsg;
				for ( i = 0; i < 24; i++ ) { fileMsg << str[ i ]; }; fileMsg << ": ";
				fileMsg << "[ERROR] " << message.c_str( ) << "\n\t\t    File: " << file << "\n\t\t    Line: " << line << std::endl;
				log_file << fileMsg.str( );
				log_file.close( );

				throw 0;

				break;
			}
			case MessageType::Fatal:
			{
				#ifdef _DEBUG
				Msg << "[FATAL] " << message.c_str( ) << "\n\t\t\t\t    File: " << file << "\n\t\t\t\t    Line: " << line << std::endl;
				OutputDebugString( Msg.str( ).c_str( ) );
				#endif
				std::wofstream log_file( "MessageLog.txt", std::ios_base::out | std::ios_base::app );
				std::wstringstream fileMsg;
				for ( i = 0; i < 24; i++ ) { fileMsg << str[ i ]; }; fileMsg << ": ";
				fileMsg << "[FATAL] " << message.c_str( ) << "\n\t\t    File: " << file << "\n\t\t    Line: " << line << std::endl;
				log_file << fileMsg.str( );
				log_file.close( );

				throw "FATAL";

				break;
			}
			default:
			{
				break;
			}
		}
	}

	#define Message(message, type) Engine::MessageFunction(__LINE__, __FILE__, message, type);
}
#endif
