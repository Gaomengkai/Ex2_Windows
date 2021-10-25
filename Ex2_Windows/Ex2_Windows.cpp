#include <iostream>
#include "OopQueue.hpp"
extern const char* TestQUEUE(int& s);
int main()
{
    int score = -1;
    const char* res = TestQUEUE(score);
    std::cout << score << std::endl << res;
}
