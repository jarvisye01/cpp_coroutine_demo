#pragma once
#include <string>
#include <pthread.h>

namespace jarvis
{

struct thread_arg
{
    int a;
    int b;
    void (*send) (int);
    thread_arg(int aa, int bb, void (*s) (int)): a(aa), b(bb), send(s) {}
};

void* thread_func(void * arg);

int add(int a, int b);

void send_res(int res);

void register_callback(int a, int b, void (*send) (int));

void sync_add(int a, int b);

void async_add(int a, int b);

}