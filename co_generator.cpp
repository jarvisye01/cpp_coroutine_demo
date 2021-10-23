#include <iostream>
#include <coroutine>

struct MyResult
{
    struct promise_type
    {
        MyResult get_return_object() { return MyResult(this); }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void return_void() {}
        std::suspend_always yield_value(const int v)
        {
            val = v;
            return {};
        }
        void unhandled_exception() {}

        void resume()
        {
            std::coroutine_handle<promise_type>::from_promise(*this).resume();
        }

        int get_val()
        {
            return val;
        }

        int val;
    };

    MyResult(promise_type *p): ptr(p) {}
    
    int get_val()
    {
        int v = ptr->get_val();
        resume();
        return v;
    }

    void resume()
    {
        ptr->resume();
    }

    promise_type *ptr;
};

MyResult generator(int num)
{
    for (int i = num; ; i = i + 5)
        co_yield i;
}

int main(int argc, char ** argv)
{
    MyResult y = generator(5);
    std::cout << y.get_val() << std::endl;
    std::cout << y.get_val() << std::endl;
    std::cout << y.get_val() << std::endl;
    std::cout << y.get_val() << std::endl;
    std::cout << y.get_val() << std::endl;
    return 0;
}