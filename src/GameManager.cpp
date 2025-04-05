//
// Created by thomas on 02/04/25.
//

#include "GameManager.hpp"

void GameManager::Tick()
{
    // get the messages from the networking
    auto messages = mNetworking.GetMessages();
    // process each message
    for (auto message: messages)
    {
        ProcessMessage(message);
    }
    // for each game, broadcast the state
    for (auto &game: mGames)
    {
        game.Broadcast();
    }
}

void GameManager::ProcessMessage(std::tuple<std::array<char, BUFFER_SIZE>, size_t, sockaddr_in> message)
{
    // get the first backslash from the message
    std::string messageString(std::get<0>(message).data());
    size_t pos = messageString.find("\\");
    if (pos == std::string::npos)
    {
        // no backslash found, return
        return;
    }
    // get the game name
    std::string gameName = messageString.substr(0, pos);
    // get the game id
    auto it = mGameMap.find(gameName);
    if (it == mGameMap.end())
    {
        // game not found, create a new game
        Game game(PORT, mNetworking.GetServerAddress(), mNetworking.GetSocket());
        mGames.push_back(game);
        mGameMap[gameName] = mGames.size() - 1;
        it = mGameMap.find(gameName);
    }
    mGames[it->second].Receive(std::get<0>(message), std::get<1>(message), std::get<2>(message));


}
