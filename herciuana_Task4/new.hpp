#include <chrono>
#include <string>
#include <iostream>
class Timer
{
private:
    std::chrono::time_point<std::chrono::steady_clock> StartTime;

public:
    Timer() : StartTime{std::chrono::steady_clock::now()}
    {
    }
    void calculateTime(std::string str = "")
    {
        auto end = std::chrono::steady_clock::now();
        auto difference = end - StartTime;
        std::cout << str << std::chrono::duration_cast<std::chrono::milliseconds>(difference).count() << std::endl;
    }
};