#include "../include/BinomialTreeEngine.h"
#include "../include/Payoff.h"
#include "../include/Option.h"
#include <iostream>
#include <cassert>

int main() {
    // Test 1: CallPayoff
    auto callPayoff = std::make_shared<CallPayoff>(100.0);
    double callResult = callPayoff->evaluate(120.0);
    assert(callResult == 20.0);
    std::cout << "CallPayoff test passed." << std::endl;

    // Test 2: PutPayoff
    auto putPayoff = std::make_shared<PutPayoff>(100.0);
    double putResult = putPayoff->evaluate(80.0);
    assert(putResult == 20.0);
    std::cout << "PutPayoff test passed." << std::endl;

    std::cout << "All tests passed!" << std::endl;
    return 0;
}