#pragma once

#include <atomic>
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
    template <template <typename> typename Container = std::list,
              template <typename> typename Queue = std::queue>
    class Pool {
    public:
        //--- public types and constants ---
        using Task = std::function<void()>;

        //--- public constructors ---
        Pool(const uint32_t num_threads = std::thread::hardware_concurrency())
        : _threads(), _tasks(), _mutex(), _cv(), _tasks_added(0), _active_threads(0), _halt(false)
        {
            for (uint32_t i = 0; i < num_threads; ++i)
            {
                _threads.emplace_back(
                    [this]()
                    {
                        while (true)
                        {
                            Task task;

                            {
                                std::unique_lock<std::mutex> lock(_mutex);

                                _cv.wait(lock, [this](){ return _halt || !_tasks.empty(); });
                                if (_halt && _tasks.empty())
                                    return;

                                task = std::move(_tasks.front());
                                _tasks.pop();
                            }

                            ++_active_threads;
                            task();
                            --_active_threads;
                        }
                    });
            }
        }

        Pool(const Pool &rhs) = delete;
        Pool(Pool &&rhs) = delete;

        ~Pool()
        {
            _halt = true;
            _cv.notify_all();
            _threads.clear();
        }

        //--- public operators ---
        Pool &operator=(const Pool &rhs) = delete;
        Pool &operator=(Pool &&rhs) = delete;

        //--- public methods ---
        uint32_t maxThreads() const noexcept
        {
            return _threads.size();
        }

        uint32_t activeThreads() const noexcept
        {
            return _active_threads;
        }

        uint64_t tasksAdded() const noexcept
        {
            return _tasks_added;
        }

        uint64_t tasksInQueue() const noexcept
        {
            return _tasks.size();
        }

        template <typename F, typename ...Args>
        auto add(F &&func, Args &&...args) -> std::future<std::result_of_t<F(Args...)>>
        {
            if (!_halt)
            {
                auto task = std::make_shared<std::packaged_task<std::result_of_t<F(Args...)>()>>(
                            std::bind(std::forward<F>(func), std::forward<Args>(args)...));
                auto result = task->get_future();

                {
                    std::unique_lock<std::mutex> lock(_mutex);
                    _tasks.emplace([task](){ (*task)(); });
                }
                ++_tasks_added;
                _cv.notify_one();

                return result;
            }

            throw std::runtime_error("ThreadPool already haltet");
        }

    private:
        //--- private properties ---
        Container<std::jthread> _threads;
        Queue<Task> _tasks;
        std::mutex _mutex;
        std::condition_variable _cv;
        std::atomic<uint64_t> _tasks_added;
        std::atomic<uint32_t> _active_threads;
        std::atomic<bool> _halt;
    };
}
