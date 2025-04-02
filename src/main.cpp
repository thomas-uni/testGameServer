#include "GameManager.hpp"

#define TICK_RATE 0.016f // 60 FPS
int main() {
    GameManager gameManager;
    while(true) {
        // get the time
        auto start = std::chrono::high_resolution_clock::now();
        // Main loop
        gameManager.Tick();
        // get the time again
        auto end = std::chrono::high_resolution_clock::now();
        // calculate the time taken
        std::chrono::duration<float> duration = end - start;
        // if the time taken is less than the tick rate, sleep for the difference
        if (duration.count() < TICK_RATE) {
            std::this_thread::sleep_for(std::chrono::milliseconds(
                static_cast<int>((TICK_RATE - duration.count()) * 1000)));
        }
        // else, print the time taken
        else {
            std::cout << "Tick took too long: " << duration.count() << " seconds" << std::endl;
        }
    }
}
