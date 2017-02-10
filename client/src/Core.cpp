//
// Created by yuruh on 29/11/16.
//

#include <ClientInterpreter.hpp>
#include <ChiefInterpreter.hpp>
#include <Serializable/SimpleInfo.hpp>
#include "Core.hpp"
#include "display/DisplaySfml.hpp"
#include "EventsSfml.hpp"
#include "GameList.hpp"
bool        connected = false;

Core    Core::_instance = Core();

Core::Core()
{
}

Core::~Core()
{
	if (this->eventManager != NULL)
		delete this->eventManager;
	if (this->display != NULL)
		delete this->display;
	if (this->network != NULL)
		delete this->network;
}

void Core::run(const std::string &hostname, uint16_t port)
{
#ifdef _WIN32
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
		throw std::runtime_error("WSAStartup failed");
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		WSACleanup();
		throw std::runtime_error("Could not find a usable version of Winsock.dll");
	}
#endif
	ChiefInterpreter::getInstance().setSubInterpreter(new ClientInterpreter());
	this->network = new ClientNetwork(hostname, port);

	this->network->start();
	this->network->connectClient();
	while (!connected);
	while (this->display->isActive()) {
		this->display->update();
		this->eventManager->handleInputs();
	}
	this->network->stop();
#ifdef _WIN32
	WSACleanup();
#endif
}

Core &Core::getInstance()
{
    return _instance;
}

void Core::useEntityPos(const EntityPos &entityPos)
{
    this->display->modifyEntityPos(entityPos);
}

void Core::useButtonEvent(const ButtonEvent &buttonEvent)
{
    this->display->useButtonEvent(buttonEvent);
    this->network->sendButtonEvent(buttonEvent);
}

void Core::connectServer(uint16_t port)
{
    this->network->clientConnected(port);
}

void Core::registerServer(uint16_t port)
{
    this->network->clientRegistered(port);

    this->display = new DisplaySfml();
    this->display->init();
    this->eventManager = new EventsSfml();
    connected = true;
}

void Core::sendCreateGame()
{
    this->network->createGame();
}

void Core::sendLaunchGame(uint32_t gameId)
{
    this->network->launchGame(gameId);
}

void Core::requireGameList()
{
    this->network->requireGameList();
}

void Core::requireRoomInfo()
{
    this->network->requireRoomInfo();
}

void Core::useGameList(const GameList &gameList)
{
    this->display->useGameList(gameList);
}

void Core::useGameInfo(const GameInfo &gameInfo)
{
    this->display->useGameInfo(gameInfo);
}

void Core::sendJoinGame(uint32_t gameId)
{
    this->network->joinGame(gameId);
}

void Core::sendLeaveRoom(uint32_t gameId)
{
    this->network->leaveRoom(gameId);
}

void Core::sendLeaveGame()
{
    this->network->leaveGame();
}

void Core::useGameResult(const SimpleInfo &simpleInfo)
{
    this->display->useGameResult(simpleInfo);
}

void Core::useJoystickEvent(const JoystickEvent &joystickEvent)
{
//    this->display->useButtonEvent(buttonEvent);
    this->network->sendJoystickEvent(joystickEvent);
}
