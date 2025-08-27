#include "../include/BinomialTreeEngine.h"
#include "../include/BlackScholesEngine.h"
#include "../include/Payoff.h"
#include "../include/Option.h"
#include <iostream>
#include <cassert>
#include <cmath>

int main() {
    // === Payoff Tests ===
    {
        auto callPayoff = std::make_shared<CallPayoff>(100.0);
        double callResult = callPayoff->evaluate(120.0);
        assert(callResult == 20.0);
        assert(callPayoff->evaluate(80.0) == 0.0);
        std::cout << "CallPayoff tests passed." << std::endl;

        auto putPayoff = std::make_shared<PutPayoff>(100.0);
        double putResult = putPayoff->evaluate(80.0);
        assert(putResult == 20.0);
        assert(putPayoff->evaluate(120.0) == 0.0);
        std::cout << "PutPayoff tests passed." << std::endl;
    }

    // === Black-Scholes Tests ===
    {
        auto callPayoff = std::make_shared<CallPayoff>(100.0);
        Option callOption(1.0, callPayoff);

        auto putPayoff = std::make_shared<PutPayoff>(100.0);
        Option putOption(1.0, putPayoff);

        BlackScholesEngine bsEngine(100.0, 0.05, 0.2);

        double callPrice = bsEngine.call_price(callOption);
        double putPrice  = bsEngine.put_price(putOption);

        // Known reference values for S=100, K=100, r=5%, sigma=20%, T=1
        assert(std::fabs(callPrice - 10.45) < 0.05);
        assert(std::fabs(putPrice - 5.57) < 0.05);

        std::cout << "Black-Scholes call price: " << callPrice << " (✓)" << std::endl;
        std::cout << "Black-Scholes put price: "  << putPrice  << " (✓)" << std::endl;
    }

    // === Special Case Tests ===
    {
        // Expired call: should equal intrinsic value
        auto callPayoff = std::make_shared<CallPayoff>(100.0);
        Option expiredCall(0.0, callPayoff);

        BlackScholesEngine bsEngine(120.0, 0.05, 0.2);
        assert(bsEngine.call_price(expiredCall) == 20.0);

        // Zero volatility put: deterministic payoff
        auto putPayoff = std::make_shared<PutPayoff>(100.0);
        Option putOption(1.0, putPayoff);

        BlackScholesEngine zeroVolEngine(100.0, 0.05, 0.0);
        double putPrice = zeroVolEngine.put_price(putOption);

        // Forward = S*exp(rT) = 105.13 -> payoff = 0
        assert(std::fabs(putPrice - 0.0) < 1e-8);

        std::cout << "Special case tests passed." << std::endl;
    }

    // === Binomial Tree vs Black-Scholes Convergence ===
    {
        auto callPayoff = std::make_shared<CallPayoff>(100.0);
        Option callOption(1.0, callPayoff);

        BlackScholesEngine bsEngine(100.0, 0.05, 0.2);
        double bsPrice = bsEngine.call_price(callOption);

        BinomialTreeEngine btEngine(100.0, 0.05, 0.2, 5000);
        double btPrice = btEngine.price(callOption);

        assert(std::fabs(btPrice - bsPrice) < 0.05);

        std::cout << "Binomial vs Black-Scholes convergence test passed." << std::endl;
        std::cout << "BS price = " << bsPrice << ", Binomial price = " << btPrice << std::endl;
    }

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
