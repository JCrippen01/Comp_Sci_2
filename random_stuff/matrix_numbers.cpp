#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

int main() {
    std::srand(std::time(nullptr));

    const int width = 80;
    const int height = 25;

    std::cout << "\033[1;32m"; // green

    while (true) {
        std::cout << "\033[H"; // move cursor to top-left

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                char c = (std::rand() % 10 < 2) ? '0' + std::rand() % 10 : ' ';
                std::cout << c;
            }
            std::cout << "\n";
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::cout << "\033[0m";
}
