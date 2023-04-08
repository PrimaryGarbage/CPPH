cmake_minimum_required(VERSION 3.22)
project(cpph VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
set(BUILD_SHARED_LIBS OFF)

set(PRIMARY_SRC
	main.cpp
    commands.hpp commands.cpp
    utils.hpp utils.cpp
    exception.hpp
	)

list(TRANSFORM PRIMARY_SRC PREPEND "src/")

add_executable(${PROJECT_NAME} ${PRIMARY_SRC})

set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX -d)

target_include_directories(${PROJECT_NAME} PRIVATE
		${CMAKE_SOURCE_DIR} src external
	)

target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/external/lib)