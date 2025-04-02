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
            if (player.id != otherPlayer.id &&
                (player.state.bitmask & (1 << otherPlayer.id)) == 0)
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
        player.id = players.size();
        player.address = *client_addr;
        player.state = state;
        players.emplace_back(player);
    }
    else
    {
        // update the player state
        int id = it->second;
        players[id].state = state;
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