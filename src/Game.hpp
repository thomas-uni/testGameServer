//
// Created by thomas on 02/04/25.
//

#ifndef GAMESERVER_GAME_HPP
#define GAMESERVER_GAME_HPP

#include <string>
#include <arpa/inet.h>
#include <vector>
#include <unordered_map>
#include "Networking.hpp"


#define MAX_PLAYERS 64

// state is the message that is received from the client
// the time is the time the message was received
// the char* is the encoded state, with length size
// the bitmask is what players have received this state
struct PlayerState
{
    float time;
    std::array<char, BUFFER_SIZE> data;
    std::size_t size;
    std::uint64_t bitmask;
};

struct Player
{
    int id;
    std::string name;
    sockaddr_in address;
    PlayerState state;
};


class Game
{
public:
    Game(int port, sockaddr_in server_addr, int server_socket);
    ~Game() = default;
    void Broadcast();
    void Receive(std::array<char, BUFFER_SIZE> buffer, int size, sockaddr_in client_addr);

private:
    // map of ip address to player id
    std::unordered_map<std::uint32_t , int> ipToPlayerId;

    std::vector<Player> players;
    int maxPlayers;
    int port;
    sockaddr_in server_addr;
    int server_socket;

};


#endif //GAMESERVER_GAME_HPP
