cmake_minimum_required(VERSION 3.0)
project(server_rtype)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

file(

GLOB_RECURSE

SOURCE_FILES

src/*
)

include_directories(include)
include_directories(include/parser)
include_directories(include/Bonus)
include_directories(include/Decoratives)
include_directories(include/Entities)
include_directories(include/Entities/Player)
include_directories(include/Game/Collision)
include_directories(include/Game/Simulation)
include_directories(include/Monsters)
include_directories(include/Patterns)
include_directories(include/Utils)
include_directories(../shared/include)
include_directories(../shared/include/Interpreter)
include_directories(../shared/include/Network)
include_directories(../shared/include/Types)
include_directories(../shared/include/Serializable)

add_executable(server_rtype ${SOURCE_FILES} src/Monsters/EnemyShip.cpp include/Monsters/EnemyShip.hpp src/Monsters/Taz.cpp include/Monsters/Taz.hpp src/Missiles/AMissile.cpp include/Missiles/AMissile.hpp src/Missiles/StandardMissile.cpp include/Missiles/StandardMissile.hpp include/Missiles/WaveMissile.hpp src/Missiles/WaveMissile.cpp)

#ADD_LIBRARY( shared SHARED IMPORTED GLOBAL )
set_target_properties( shared PROPERTIES IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/../shared/libshared.a)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} shared)

IF (WIN32)
  # set stuff for windows
ELSEIF(UNIX)
	set(THREADS_PREFER_PTHREAD_FLAG ON)
	find_package(Threads REQUIRED)
	target_link_libraries(server_rtype -pthread)
ENDIF()
