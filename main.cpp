#include "CaffeBean/include/net.h"
#include "CaffeBean/include/solver.h"

void train(std::string train_cfg) {
    Solver *solver = new Solver(train_cfg);
    solver->solve();
    delete solver;
}

void test(std::string test_cfg) {
    Solver *solver = new Solver(test_cfg);
    solver->infer();
    delete solver;
}

int main() {
    std::cout << "Hello, CaffeBean!" << std::endl;
    std::string train_cfg = "/Users/kaiyu/workspace/CaffeBean/examples/train_cfg.json";
    std::string test_cfg = "/Users/kaiyu/workspace/CaffeBean/examples/test_cfg.json";

    train(train_cfg);
    test(test_cfg);
    return 0;
}
