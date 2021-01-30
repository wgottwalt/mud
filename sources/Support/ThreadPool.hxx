#pragma once

#include <condition_variable>
#include <functional>
#include <future>
#include <list>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>

namespace Mud::Support::Thread
{
    template <typename Thread = std::thread, template <typename> typename Container = std::list,
              template <typename> typename Queue = std::queue>
    class Pool {
    public:
        //--- public types and constants ---
        using Callable = std::function<void()>;

        //--- public constructors ---
        Pool(const uint32_t num_threads = std::thread::hardware_concurrency())
        : _threads(), _callables(), _mutex(), _cv(), _max_threads(num_threads), _halt(false)
        {
            for (uint32_t i = 0; i < _max_threads; ++i)
            {
                _threads.emplace_back(
                    [this]()
                    {
                        while (true)
                        {
                            Callable callable;
                            {
                                std::unique_lock<std::mutex> lock(_mutex);

                                _cv.wait(lock, [this](){ return _halt || !_callables.empty(); });

                                if (_halt && _callables.empty())
                                    return;

                                callable = std::move(_callables.front());
                                _callables.pop();
                            }
                            callable();
                        }
                    });
            }
        }

        Pool(const Pool &rhs) = delete;
        Pool(Pool &&rhs) = delete;

        ~Pool()
        {
            {
                std::unique_lock<std::mutex> lock(_mutex);
                _halt = true;
            }

            _cv.notify_all();
            for (auto &thread : _threads)
                thread.join();
        }

        //--- public operators ---
        Pool &operator=(const Pool &rhs) = delete;
        Pool &operator=(Pool &&rhs) = delete;

        //--- public methods ---
        uint32_t maxHardwareThreads() const noexcept
        {
            return std::thread::hardware_concurrency();
        }

        uint32_t maxThread() const noexcept
        {
            return _max_threads;
        }

        size_t threadCount() const
        {
            return _callables.size();
        }

        template <typename F, typename ...Args>
        auto add(F &&func, Args &&...args)-> std::future<std::result_of_t<F(Args...)>>
        {
            auto callable = std::make_shared<std::packaged_task<std::result_of_t<F(Args...)>()>>(
                            std::bind(std::forward<F>(func), std::forward<Args>(args)...));
            auto result = callable->get_future();
            {
                std::unique_lock<std::mutex> lock(_mutex);

                if (_halt)
                    throw std::runtime_error("ThreadPool already haltet");

                _callables.emplace([callable](){ (*callable)(); });
            }
            _cv.notify_one();

            return result;
        }

    private:
        //--- private properties ---
        Container<Thread> _threads;
        Queue<Callable> _callables;
        std::mutex _mutex;
        std::condition_variable _cv;
        uint32_t _max_threads;
        bool _halt;
    };
}
