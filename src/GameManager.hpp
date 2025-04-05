//
// Created by thomas on 02/04/25.
//

#ifndef GAMESERVER_GAMEMANAGER_HPP
#define GAMESERVER_GAMEMANAGER_HPP


#include "Networking.hpp"
#include "Game.hpp"

class GameManager
{
public:
    GameManager() = default;
    ~GameManager() = default;
    void Tick();
private:
    Networking mNetworking;
    std::vector<Game> mGames;
    std::unordered_map<std::string, size_t> mGameMap;

    void ProcessMessage(std::tuple<std::array<char, BUFFER_SIZE>, size_t, sockaddr_in> message);
};


#endif //GAMESERVER_GAMEMANAGER_HPP
