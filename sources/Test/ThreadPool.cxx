#include <chrono>
#include <iostream>
#include "Support/ThreadPool.hxx"

void wait()
{
    std::this_thread::sleep_for(std::chrono::seconds(10));
}

int32_t main()
{
    Mud::Support::Thread::Pool pool(8);
    std::list<std::future<void>> list;

    for (int32_t i = 0; i < 32; ++i)
    {
        list.emplace_back(pool.add(wait));
        std::cout << "pool: " << pool.maxThreads() << " " << pool.activeThreads() << " "
                  << pool.tasksAdded() << " " << pool.tasksInQueue() << std::endl;
    }

    for (int32_t i = 0; i < 35; ++i)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "pool: " << pool.maxThreads() << " " << pool.activeThreads() << " "
                  << pool.tasksAdded() << " " << pool.tasksInQueue() << std::endl;
    }

    return 0;
}
