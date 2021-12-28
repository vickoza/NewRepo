// CoFib.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <coroutine>
#include <iostream>
#include <iomanip>

template<typename T>
struct ReturnObject {
    struct promise_type {
        T value_;
        void return_void() noexcept {}

        ReturnObject get_return_object() {
            return {
              .h_ = std::coroutine_handle<promise_type>::from_promise(*this)
            };
        }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void unhandled_exception() {}
        std::suspend_always yield_value(T value) {
            value_ = value;
            return {};
        }
    };

    std::coroutine_handle<promise_type> h_;
};

ReturnObject<unsigned long long> getNextFib()
{
    auto prev = static_cast<unsigned long long>(0);
    auto value = static_cast<unsigned long long>(1);
    while (true)
    {
        co_yield value;            // starts at 1
        auto temp = value + prev;
        prev = value;
        value = temp;
    }
}

int main()
{
    auto h = getNextFib().h_;
    auto& promise = h.promise();
    for (auto i = 0; i < 2; ++i)
    {
        for (auto j = 0; j < 12; ++j)
        {
            std::cout <<std::left << std::setw(6) << promise.value_ ;
            h();
        }
        std::cout << '\n';
    }
    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
