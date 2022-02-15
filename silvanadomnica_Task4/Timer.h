#include <chrono>
#include <string>
#include <iostream>
class Timer
{
    std::chrono::steady_clock::time_point start;

public:
    Timer() : start{std::chrono::steady_clock::now()}
    {
    }
    void ShowResult(std::string message = "")
    {
        auto end = std::chrono::steady_clock::now();
        auto difference = end - start;
        std::cout << message << std::chrono::duration_cast<std::chrono::milliseconds>(difference).count() << std::endl;
    }
};
