#include <iostream>
#include <string>

#include "util.hpp"

int main(int argc, char ** argv)
{
    for (int i = 0; i < 10; i++)
    {
        jarvis::sync_add(i, i * i);
    }
    // 防止退出导致子进程销毁
    while (true) {}
    return 0;
}