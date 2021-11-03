#pragma once

#define CURL_STATICLIB

#include "../shared/curl/include/curl/curl.h"

#pragma comment(lib, "ws2_32")
#pragma comment(lib, "Crypt32")
#pragma comment(lib, "wldap32")
#pragma comment(lib, "Normaliz")

#include "../shared/rapidjson/document.h"
#include "../shared/rapidjson/writer.h"
#include "../shared/rapidjson/stringbuffer.h"

using namespace rapidjson;

namespace get_offset {
	// json offsets
	inline Document offsets = { };

	inline static std::size_t write( void* contents, std::size_t size, std::size_t nmemb, void* userp ) {
		( ( std::string* )userp )->append( ( char* )contents, size * nmemb );
		return size * nmemb;
	}

	inline bool raw( ) {
		CURLcode res = { };
		std::string read_buffer = { };

		CURL* curl = curl_easy_init( );
		if ( curl ) {
			curl_easy_setopt( curl, CURLOPT_URL, "https://raw.githubusercontent.com/frk1/hazedumper/master/csgo.json" );
			curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, write );
			curl_easy_setopt( curl, CURLOPT_WRITEDATA, &read_buffer );
			res = curl_easy_perform( curl );

			if ( res != CURLE_OK ) {
				std::cout << "Something went wrong on curl request!" << std::endl;
				return false;
			}

			curl_easy_cleanup( curl );
			offsets.Parse( read_buffer.c_str( ) );
			std::cout << "Allright, offsets have been captured" << std::endl;

			return true;
		}

		return false;
	}

	inline DWORD offset( const std::string& netvar ) {
		if ( offsets.HasParseError( ) ) {
			std::cout << "Sommething went wrong on offsets parse!" << std::endl;
			return 0;
		}

		Value& data = netvar.find( "dw" ) != std::string::npos ? offsets[ "signatures" ][ netvar.c_str( ) ] : offsets[ "netvars" ][ netvar.c_str( ) ];
		std::cout << netvar << ": " << data.GetUint( ) << std::endl;
		return data.GetUint( );
	}
}