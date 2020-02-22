#include "CaffeBean/include/net.h"

int main() {
    std::cout << "Hello, CaffeBean!" << std::endl;
    Net net;
    net.print_net();
    net.init_net();

    net.forward();
    CAFFEBEAN_LOG("net forward done");
    net.backward();
    CAFFEBEAN_LOG("net forward done");
    return 0;
}
