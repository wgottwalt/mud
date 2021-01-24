#include <iostream>
#include "Net/Server.hxx"

int32_t main()
{
    Mud::Net::Server server;

    server.execute();

    return 0;
}
