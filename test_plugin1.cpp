#include <iostream>

extern "C" __declspec(dllexport) void plugin_main() {
    std::cout << "From test plugin 1!\n";
}
