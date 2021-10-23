#include <iostream>
#include <coroutine>
#include <pthread.h>
#include "util.hpp"

void *thread_func(void * arg);

struct MyResult
{
    struct promise_type
    {
        MyResult get_return_object() { return {}; }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() {}
    };
};

struct Awaiter
{
    Awaiter(int aa, int bb): a(aa), b(bb) {}
    bool await_ready() { return false; }
    int await_resume()
    {
        return res;
    }

    void await_suspend(std::coroutine_handle<> handle)
    {
        ghandle = handle;
        pthread_create(&tid, NULL, thread_func, (void*)this);
        pthread_detach(tid);
    }

    void set_res(int r) { res = r; }
    int get_res() { return res; }


    int res;
    int a, b;
    pthread_t tid;
    std::coroutine_handle<> ghandle;
};

void *thread_func(void * arg)
{
    Awaiter *waiter = (Awaiter*)arg;
    int res = jarvis::add(waiter->a, waiter->b);
    waiter->set_res(res);
    waiter->ghandle.resume();
    return NULL;
}

MyResult co_add(int a, int b)
{
    int res = co_await Awaiter(a, b);
    jarvis::send_res(res);
}

int main(int argc, char ** argv)
{
    for (int i = 0; i < 10; i++)
    {
        co_add(i, i * i);
        std::cout << "co_add return!" << std::endl;
    }

    // 防止退出导致子进程销毁
    while (true) {}

    return 0;
}