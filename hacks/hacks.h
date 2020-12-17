#pragma once

#include "../var/var.h"
#include "../memory/offset.h"

#include <cstdint>
#include <thread>

#include <algorithm>

namespace hacks {
	inline void memory_init( const SlimUtils::SlimModule* module ) {
		// local infos
		var::LocalPlayer = var::mem.Read<DWORD>( module->ptrBase + offset::dwLocalPlayer );
		var::LocalHealth = var::mem.Read<std::int32_t>( var::LocalPlayer + offset::m_iHealth );
		var::LocalTeam = var::mem.Read<std::int32_t>( var::LocalPlayer + offset::m_iTeamNum );
		var::CrosshairID = var::mem.Read<std::int32_t>( var::LocalPlayer + offset::m_iCrosshairId );

		// enemy infos
		var::EnemyPlayer = var::mem.Read<DWORD>( module->ptrBase + offset::dwEntityList + ( ( var::CrosshairID - 1 ) * offset::s_EntityLoop ) );
		var::EnemyHealth = var::mem.Read<std::int32_t>( var::EnemyPlayer + offset::m_iHealth );
		var::EnemyTeam = var::mem.Read<std::int32_t>( var::EnemyPlayer + offset::m_iTeamNum );
	}

	inline void memory_input( ) {
		if ( GetAsyncKeyState( VK_ADD ) ) {
			std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );
			var::config.trigger_delay += 10;
		}

		if ( GetAsyncKeyState( VK_SUBTRACT ) ) {
			std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );
			var::config.trigger_delay -= 10;
		}

		var::config.trigger_delay = std::clamp( var::config.trigger_delay, 0, 200 );

		// place other keys of other features here
	}

	inline void memory_trigger_bot( const SlimUtils::SlimModule* module ) {
		if ( var::LocalHealth > 0 && var::EnemyHealth > 0 ) {
			if ( var::LocalTeam != var::EnemyTeam ) {
				// make delay. use trigger delay from config
				std::this_thread::sleep_for( std::chrono::milliseconds( var::config.trigger_delay ) );

				// make shoot
				var::mem.Write<std::int32_t>( module->ptrBase + offset::dwForceAttack, sizeof( std::int32_t ) + 1 );
				std::this_thread::sleep_for( std::chrono::milliseconds( 50 ) );
				var::mem.Write<std::int32_t>( module->ptrBase + offset::dwForceAttack, sizeof( std::int32_t ) );
			}
		}
	}

	inline void memory_auto_jump( const SlimUtils::SlimModule* cs_module ) {
		// empty
	}
}