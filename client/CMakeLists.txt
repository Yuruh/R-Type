cmake_minimum_required(VERSION 3.0)
project(client_rtype)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(client_rtype ${SOURCE_FILES} src/display/AEntity.cpp
        include/display/AEntity.hpp include/display/IAnimatedSprites.hpp src/display/TileSetSprites.cpp include/display/TileSetSprites.hpp
        src/display/ASpritesHandler.cpp include/display/ASpritesHandler.hpp src/display/SfmlSpriteHandler.cpp include/display/SfmlSpriteHandler.hpp
        include/display/AScene.hpp include/display/Button.hpp include/Core.hpp include/display/DisplaySfml.hpp
        include/EventsSfml.hpp include/display/IAnimated.hpp include/display/IDisplay.hpp include/IEventManager.hpp
        include/INetwork.hpp include/display/IScene.hpp include/display/IWindow.hpp include/display/Scrolling.hpp include/display/Selectable.hpp
        include/display/TextureManager.hpp include/display/WindowSfml.hpp src/display/AScene.cpp src/display/Button.cpp src/Core.cpp
        src/display/DisplaySfml.cpp src/EventsSfml.cpp src/main.cpp src/display/Scrolling.cpp src/display/Selectable.cpp  src/display/TextureManager.cpp
        src/display/WindowSfml.cpp src/display/ObjectPool.cpp include/display/ObjectPool.hpp src/display/SoundManager.cpp
        include/display/SoundManager.hpp src/display/SoundPlayer.cpp include/display/SoundPlayer.hpp include/ClientInterpreter.hpp src/ClientInterpreter.cpp
        src/display/menu/TitleScreen.cpp include/display/menu/TitleScreen.hpp src/display/menu/ChooseGameScreen.cpp include/display/menu/ChooseGameScreen.hpp
        src/display/menu/SettingsScreen.cpp include/display/menu/SettingsScreen.hpp src/display/menu/RoomScreen.cpp include/display/menu/RoomScreen.hpp
	    src/Network/ClientNetwork.cpp include/Network/ClientNetwork.hpp src/display/GameScene.cpp include/display/GameScene.hpp src/display/PlayerSprites.cpp include/display/PlayerSprites.hpp)

include_directories(include)
include_directories(../shared/include)
include_directories(../shared/include/Serializable)
include_directories(../shared/include/Interpreter)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(client_rtype ${SFML_LIBRARIES})
endif()

#ADD_LIBRARY( shared SHARED IMPORTED GLOBAL )
set_target_properties( shared PROPERTIES IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/../shared/libshared.a)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} shared)
IF (WIN32)
  # set stuff for windows
ELSE()
	set(THREADS_PREFER_PTHREAD_FLAG ON)
	find_package(Threads REQUIRED)
	target_link_libraries(client_rtype -pthread)
ENDIF()
