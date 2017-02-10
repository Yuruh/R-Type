cmake_minimum_required(VERSION 3.0)
project(shared)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(include)
include_directories(include/Interpreter)
include_directories(include/Network)
 
set(SOURCE_FILES
src/Interpreter/ChiefInterpreter.cpp include/Interpreter/ChiefInterpreter.hpp include/Interpreter/IInterpreter.hpp src/Serializable/ConnectInfo.cpp include/Serializable/ConnectInfo.hpp
        src/Serializable/ASerializable.cpp include/Serializable/ASerializable.hpp
		src/Network/ASocket.cpp include/Network/ASocket.hpp
        src/Serializable/EntityPos.cpp include/Serializable/EntityPos.hpp
		src/Serializable/SimpleInfo.cpp include/Serializable/SimpleInfo.hpp
        src/Serializable/GameInfo.cpp include/Serializable/GameInfo.hpp
        src/Serializable/ButtonEvent.cpp include/Serializable/ButtonEvent.hpp
        include/Serializable/ISerializable.hpp include/Network/ISocket.hpp include/Runnable.hpp
        include/Threadable.hpp src/ThreadPool.cpp
		include/Types include/Serializable include/EntityType.hpp src/Serializable/GameList.cpp include/Serializable/GameList.hpp include/Serializable/JoystickEvent.hpp src/Serializable/JoystickEvent.cpp)

IF (WIN32)
	add_library(shared ${SOURCE_FILES}
src/Network/Windows/TcpSocket.cpp
src/Network/Windows/UdpSocket.cpp)
target_link_libraries(${PROJECT_NAME} wsock32 ws2_32)
ELSEIF(UNIX)
	add_library(shared ${SOURCE_FILES}
src/Network/Linux/TcpSocket.cpp
src/Network/Linux/UdpSocket.cpp)
ENDIF()