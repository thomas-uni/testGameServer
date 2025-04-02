//
// Created by thomas on 02/04/25.
//

#include "Game.hpp"

void Game::Broadcast()
{
    // for each player, send the state to all other players
    for (Player &player : players)
    {
        for (const Player &otherPlayer : players)
        {
            if ((player.state.bitmask & (1 << otherPlayer.id)) == 0)
            {
                // send the state to the other player
                player.state.bitmask |= (1 << otherPlayer.id);
                sendto(server_socket, player.state.data.data(), player.state.size, 0, (struct sockaddr *)&otherPlayer.address, sizeof(otherPlayer.address));
            }
        }
    }

}

void Game::Receive(std::array<char, BUFFER_SIZE>buffer, int size, sockaddr_in *client_addr)
{
    // construct the player state
    PlayerState state;
    state.data = buffer;
    state.size = size;
    // Get the current time point using steady_clock
    auto now = std::chrono::steady_clock::now();
    // Convert the time point to a duration since epoch (nanoseconds)
    auto duration = now.time_since_epoch();
    auto nanos = std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
    state.time = nanos;
    state.bitmask = 0;
    // get the player id
    std::uint32_t ip = client_addr->sin_addr.s_addr ^
                      (client_addr->sin_port << 16);
    auto it = ipToPlayerId.find(ip);
    if (it == ipToPlayerId.end())
    {
        // add the player
        Player player;
        int id = players.size();
        player.id = id;
        player.address = *client_addr;
        player.state = state;
        player.state.bitmask |= (1 << player.id);
        // add the player address to the end of the state data
        std::memcpy(players[id].state.data.data() + players[id].state.size, &players[id].address, sizeof(players[id].address));
        players[id].state.size += sizeof(players[id].address);
        players.emplace_back(player);
        ipToPlayerId[ip] = player.id;
    }
    else
    {
        // update the player state
        int id = it->second;
        players[id].state = state;
        players[id].state.bitmask |= (1 << id);
        // add the player address to the end of the state data
        std::memcpy(players[id].state.data.data() + players[id].state.size, &players[id].address, sizeof(players[id].address));
        players[id].state.size += sizeof(players[id].address);


    }
}

Game::Game(int port, sockaddr_in server_addr, int server_socket) :
    port(port),
    server_addr(server_addr),
    server_socket(server_socket),
    maxPlayers(MAX_PLAYERS)
{
    players.reserve(maxPlayers);
}