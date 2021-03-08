#include <iostream>
#include "Support/Telnet.hxx"

namespace T = Mud::Support::Telnet;
using C = T::Control;
using O = T::Option;

constexpr auto seq = [](auto &&...args)
    { return T::sequence(std::forward<decltype(args)>(args)...); };

void print(const std::string &what, const std::string &msg)
{
    std::cout << what << ':';
    for (auto chr : msg)
        std::cout << ' ' << std::hex << (static_cast<uint16_t>(chr) & 0xff);
    std::cout << std::endl;
}

int32_t main()
{
    const std::string msg1(seq(C::Iac) + seq(C::Will) + seq(O::TType));
    const std::string msg2(seq(C::Iac) + seq(C::Do) + seq(O::TType));
    const std::string msg3(seq(C::Iac) + seq(C::Sb) + seq(O::TType) + '\x01' + seq(C::Iac) +
                           seq(C::Se));
    const std::string msg4(seq(C::Iac) + seq(C::Sb) + seq(O::TType) + '\x00' + 'V' + 'T' + '1' +
                           '0' + '0' + '\x00' + seq(C::Iac) + seq(C::Se));

    print("client -> server (want to tell terminal type)", msg1);
    print("server -> client (do it)", msg2);
    print("server -> client (want one suboption terminal type and end suboption", msg3);
    print("client -> server (want to tell 1 suboption string VT100 and end suboption", msg4);

    return 0;
}
