#include <iostream>
#include "Support/Time.hxx"

namespace TIME = Mud::Support::Time;

int32_t main()
{
    const auto t1 = TIME::now();
    const auto t2 = TIME::nowTimeT() + 101000;
    const auto t3 = TIME::now() + std::chrono::seconds(2020000);

    std::cout << "t1:      " << TIME::toDateString(t1) << "\n"
              << "t2:      " << TIME::toDateString(t2) << "\n"
              << "t3:      " << TIME::toDateString(t3)
              << std::endl;

    return 0;
}
