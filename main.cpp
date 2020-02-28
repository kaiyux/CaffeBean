#include "CaffeBean/include/net.h"
#include "CaffeBean/include/solver.h"

int main() {
    std::cout << "Hello, CaffeBean!" << std::endl;
    std::string train_cfg = "/Users/kaiyu/workspace/CaffeBean/examples/train_cfg.json";
    Solver *solver = new Solver(train_cfg);
    solver->solve();
    return 0;
}
