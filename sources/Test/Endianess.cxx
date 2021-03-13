#include <iostream>
#include "Support/Endian.hxx"

namespace E = Mud::Support::Endian;

int32_t main()
{
    const uint64_t test = 0xF0F0F0F012345678;

    std::cout << "byte swap " << std::hex << test << " to " << E::swap(test) << std::endl;

    return 0;
}
