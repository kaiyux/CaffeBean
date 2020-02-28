#include "CaffeBean/include/net.h"
#include "CaffeBean/include/solver.h"

int main() {
    std::cout << "Hello, CaffeBean!" << std::endl;
    std::string config_file = "/Users/kaiyu/workspace/CaffeBean/examples/test_net.json";
    float learning_rate = 0.01;
    int step = 2000, display_step = 100;
    Solver *solver = new Solver(config_file, learning_rate, step, display_step);
    solver->solve();
    return 0;
}
