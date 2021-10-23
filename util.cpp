#include <iostream>
#include <unistd.h>
#include "util.hpp"

namespace jarvis
{

void* thread_func(void * arg)
{
    thread_arg *targ = (thread_arg*)arg;
    int res = add(targ->a, targ->b);
    targ->send(res);
    delete targ;
    return NULL;
}

int add(int a, int b)
{
    sleep(5);
    return a + b;
}

void send_res(int res)
{
    std::cout << "result is " << res << std::endl;
}

void register_callback(int a, int b, void (*send) (int))
{
    pthread_t tid;
    pthread_create(&tid, NULL, thread_func, (void*)new thread_arg(a, b, send_res));
    pthread_detach(tid);
}

void sync_add(int a, int b)
{
    int res = add(a, b);
    send_res(res);
    std::cout << "sync_add over!" << std::endl;
}

void async_add(int a, int b)
{
    register_callback(a, b, send_res);
    std::cout << "async_add over!" << std::endl;
}

}