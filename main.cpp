#include "CaffeBean/include/net.h"

int main() {
    std::cout << "Hello, CaffeBean!" << std::endl;
    Net net;
    net.print_net();
    net.forward();
    net.backward();
    return 0;
}
