//
// Created by wasta-geek on 13/12/16.
//

#include    <signal.h>
#include    <ChiefInterpreter.hpp>
#include <Serializable/EntityPos.hpp>
#include    "Core.hpp"
#include    "ServerInterpreter.hpp"

Core    Core::_instance = Core();
bool running = true;

Core::Core() {}

Core::~Core() {
	delete this->_network;
}

void handleShutdown(int s) {
	running = false;
}

#ifdef _WIN32
BOOL WINAPI HandlerRoutine(DWORD signal)
{
	if (signal == CTRL_C_EVENT)
	{
		handleShutdown(0);
		return true;
	}
	return false;
}
#endif

void Core::catchShutdown() {
#ifdef __linux__ 
	struct sigaction sigIntHandler;


	sigIntHandler.sa_handler = handleShutdown;
	sigemptyset(&sigIntHandler.sa_mask);
	sigIntHandler.sa_flags = 0;
	sigaction(SIGINT, &sigIntHandler, NULL);
#elif _WIN32
	SetConsoleCtrlHandler(HandlerRoutine, true);
#endif
}

void Core::run(uint16_t port) {
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
	ChiefInterpreter::getInstance().setSubInterpreter(new ServerInterpreter());
	this->_network = new ServerNetwork(port);
	this->catchShutdown();
	_network->start();
	_gameManager.start();
	while (running);
	_network->stop();
	_gameManager.stop();
#ifdef _WIN32
	WSACleanup();
#endif
}

void Core::connectClient(uint32_t id, uint16_t port) {
	_network->clientConnected(id, port);
}

void Core::registerClient(uint32_t id, uint16_t port) {
	_network->clientRegistered(id, port);
}

void Core::sendGameList(uint32_t id)
{
	_network->sendGameList(id, this->_gameManager.getGameList());
}

void Core::sendRoomInfo(uint32_t playerId)
{
	_network->sendGameList(playerId, this->_gameManager.getRoomInfo(playerId));
}

void Core::createGame(uint32_t playerID) {
	std::cout << "CREATE GAME" << std::endl;
	std::cout << playerID << std::endl,
		_gameManager.createGame(playerID);
}

void Core::joinGame(uint32_t playerId, uint32_t gameId) {
	std::cout << "JOIN GAME" << std::endl;
	std::cout << playerId << std::endl,
		_gameManager.joinGame(playerId, gameId);
}

void Core::notifyLeaveRoom(uint32_t playerId, uint32_t gameId)
{
	this->_gameManager.notifyLeaveRoom(playerId, gameId);
}

void Core::launchGame(uint32_t gameId) {
	_gameManager.launchGame(gameId);
}

void Core::useButtonEvent(uint32_t playerId, const ButtonEvent &buttonEvent)
{
	_gameManager.useButtonEvent(playerId, buttonEvent);
}


void Core::useJoystickEvent(uint32_t playerId, const JoystickEvent &event)
{
    _gameManager.useJoystickEvent(playerId, event);
}

void Core::sendEntityPositions(uint32_t playerId, const EntityPos &entityPos) {
	this->_network->sendEntityPos(playerId, entityPos);
}

void Core::sendGameInfo(uint32_t gameId, uint32_t playerId)
{
	this->_network->sendGameInfo(gameId, playerId);
}

void Core::sendGameLaunched(uint32_t gameId, uint32_t playerId)
{
	_network->sendGameLaunched(gameId, playerId);
}

void Core::sendEndGame(bool isVictory, uint32_t playerId)
{
	_network->sendEndGame(isVictory, playerId);
}

Core &Core::getInstance()
{
	return _instance;
}

void Core::useLeaveGame(uint32_t playerId)
{
	this->_gameManager.useLeaveGame(playerId);
}
