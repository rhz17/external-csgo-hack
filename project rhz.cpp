#include "hacks/hacks.h"

std::int32_t main( ) {
	std::cout << "Waiting csgo process..." << std::endl;
	while ( !SlimUtils::SlimMem::GetPID( L"csgo.exe", &var::pid ) )
		std::this_thread::sleep_for( std::chrono::milliseconds( 3000 ) );

	if ( !var::mem.Open( var::pid, SlimUtils::ProcessAccess::ReadWrite ) ) {
		std::cout << "Failed to open csgo process, error-code: " << GetLastError( ) << std::endl;
		std::cout << "Closing project rhz in 3 seconds..." << std::endl;

		std::this_thread::sleep_for( std::chrono::milliseconds( 3000 ) );
		return 0;
	}
	std::cout << "Success, csgo process in memory..." << std::endl;
	std::cout << "Trying to find client.dll module in 5 seconds..." << std::endl;
	std::this_thread::sleep_for( std::chrono::milliseconds( 5000 ) );

	const SlimUtils::SlimModule* module = var::mem.GetModule( L"client.dll" );
	if ( module ) {
		std::cout << "Alright, client.dll module is open..." << std::endl;
		std::cout << "Starting hacks in 3 seconds..." << std::endl;

		std::this_thread::sleep_for( std::chrono::milliseconds( 3000 ) );

		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << "* STARTED *" << std::endl;

		while ( true ) {
			std::cout << "Trigger bot [" << var::config.trigger_delay << "ms] (use - to subtract and + to add 10ms)... \r";

			// run memory
			hacks::memory_init( module );
			hacks::memory_input( );

			// run hacks
			hacks::memory_trigger_bot( module );
			hacks::memory_auto_jump( module );

			// relieve CPU usage
			std::this_thread::sleep_for( std::chrono::milliseconds( 15 ) );
		}
	}
	else {
		std::cout << "Cannot access client.dll module..." << std::endl;
		std::cout << "Closing project rhz in 3 seconds..." << std::endl;

		std::this_thread::sleep_for( std::chrono::milliseconds( 3000 ) );
		return 0;
	}
}