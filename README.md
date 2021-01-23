This is an attempt to write a MUD using C++20 and Boost. The actual idea
was to use C++20 (and up) own network component which is available since
gcc 9, though the async parts and the io_context parts of it are not
really working like intended. So this is how Boost/ASIO came into play.

I try to keep the code that way, that it is fully useable with LTO and
can be compiled statically.
