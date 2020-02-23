#include "CaffeBean/include/net.h"
#include "CaffeBean/include/solver.h"

int main() {
    std::cout << "Hello, CaffeBean!" << std::endl;
    std::string config_file = "/Users/kaiyu/workspace/CaffeBean/examples/test_net.json";
    Solver *solver = new Solver(config_file);
    Net net;
    net.init_net();
    net.forward();
    CAFFEBEAN_LOG("net forward done");
    net.backward();
    CAFFEBEAN_LOG("net forward done");
    return 0;
}
