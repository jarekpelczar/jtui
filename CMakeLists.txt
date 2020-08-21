cmake_minimum_required(VERSION 2.8)
project(jtui CXX)

IF(CMAKE_VERSION VERSION_LESS "3.1.3")
	set(CMAKE_CXX_FLAGS	"${CMAKE_CXX_FLAGS} -std=c++17")
ELSE()
	set(CMAKE_CXX_STANDARD 17)
	set(CMAKE_CXX_STANDARD_REQUIRED ON)
ENDIF()

include_directories(include)

add_definitions(-Wall -Wextra -Werror)

set(jtui_headers
	include/jtui/jtui_display.h
	include/jtui/jtui_app.h	
	)
	
set(jtui_private_headers
	)
	
set(jtui_sources
	source/jtui_app.cpp
	source/jtui_render_buffer.cpp
	)

add_library(jtui STATIC
	${jtui_headers}
	${jtui_private_headers}
	${jtui_sources})

add_subdirectory(examples)
