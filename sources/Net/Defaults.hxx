#pragma once

#include <boost/asio.hpp>

namespace Mud::Net
{
    namespace ASIO = boost::asio;
    namespace IP = ASIO::ip;
    using TCP = IP::tcp;

    static const uint16_t DefaultPort = 5555;
}
