#include "CaffeBean/include/net.h"
#include "CaffeBean/include/solver.h"

int main() {
    std::cout << "Hello, CaffeBean!" << std::endl;
    std::string config_file = "/Users/kaiyu/workspace/CaffeBean/examples/test_net.json";
    Solver *solver = new Solver(config_file);
    solver->solve();
    return 0;
}
