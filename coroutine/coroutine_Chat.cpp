#include <exception>
#include <iostream>
#include <coroutine>
#include <utility>
#include <string>


struct Chat {
    struct promise_type; // Forward declare nested promise_type

    using Handle = std::coroutine_handle<promise_type>;
    Handle mCoroHdl{};

    explicit Chat(promise_type* p) : mCoroHdl{Handle::from_promise(*p)} {}
    Chat(Chat&& rhs) noexcept : mCoroHdl{std::exchange(rhs.mCoroHdl, nullptr)} {}
    ~Chat() { if (mCoroHdl) mCoroHdl.destroy(); }

    std::string listen() {
        if (!mCoroHdl.done()) mCoroHdl.resume();
        return std::move(mCoroHdl.promise()._msgOut);
    }

    void answer(std::string msg) {
        mCoroHdl.promise()._msgIn = std::move(msg);
        if (!mCoroHdl.done()) mCoroHdl.resume();
    }

    struct promise_type {
        std::string _msgOut{}, _msgIn{};

        Chat get_return_object() { return Chat(this); }
        std::suspend_always initial_suspend() noexcept { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        std::suspend_always yield_value(std::string msg) noexcept { _msgOut = std::move(msg); return {}; }
        void return_value(std::string msg) noexcept { _msgOut = std::move(msg); }
        void unhandled_exception() noexcept {}
        
        struct awaiter {
            promise_type& pt;
            bool await_ready() const noexcept { return false; }
            void await_suspend(std::coroutine_handle<>) const noexcept {}
            std::string await_resume() noexcept { return std::move(pt._msgIn); }
        };
        auto await_transform(std::string) noexcept { return awaiter{*this}; }
    };
};


Chat fun() {
    co_yield "Hello\n";
    std::cout << co_await std::string{};
    co_return "Here!\n";
}

void use() {
    Chat chat = fun();
    std::cout << chat.listen();
    chat.answer("Where are you?\n");
    std::cout << chat.listen();
}

int main() {
    use();
    return 0;
}