#include "BinomialTreeEngine.h"
#include <iostream>

int main() {
    // Step 1: Create payoff (call or put)
    // e.g., payoff = make_shared<PutPayoff>(strike);
    auto payoff = std::make_shared<PutPayoff>(100.0); 

    // Step 2: Create option with maturity and payoff
    Option option = Option(100.0, payoff);

    // Step 3: Create binomial tree engine with spot, rate, volatility, steps
    BinomialTreeEngine engine = BinomialTreeEngine(100.0, 0.05, 0.2, 1000);

    // Step 4: Call engine.price(option) to get the value
    double value = engine.price(option); 

    // Step 5: Print result to console
    std::cout << "Option value: $" << value << std::endl; 

    // Step 6: (Optional) run multiple scenarios

    return 0;
}