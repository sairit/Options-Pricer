#include "../include/BinomialTreeEngine.h"
#include <iostream>
#include <cmath>

BinomialTreeEngine::BinomialTreeEngine(double spot, double rate, double volatility, int steps) : spot(spot), rate(rate), volatility(volatility), steps(steps) {
    std::cout << "Binomial Tree Engine created with: spot =  " << spot << ", rate = " << rate << ", volatility = " << volatility << ", steps = " << steps << std::endl;
}

double BinomialTreeEngine::price(const Option& option) const {
    // Precomputing tree parameters
    double dt = option.get_maturity() / steps;
    double u = exp(volatility * sqrt(dt));
    double d = 1 / u;
    double p = (exp(rate * dt) - d) / (u - d);
    double discount = exp(-rate * dt);
    const auto& payoff = option.get_payoff();

    // Building terminal node values
    double value[steps + 1];
    double S = spot * pow(d, steps);
    for (int i = 0; i <= steps; i++){
        value[i] = payoff->evaluate(S);
        S *= (u / d);
    }

    // Stepping backward through tree for early exercise check
    for (int t = steps - 1; t >= 0; --t) {
        double S = spot * pow(d, t);
        for (int i = 0; i <= t; ++i) {
            double expected = discount * (p * value[i+1] + (1 - p) * value[i]);
            double early_exercise = payoff->evaluate(S);
            value[i] = std::max(early_exercise, expected);
            S *= (u / d);
        }
    }
    
    // Returning root as the option price
    return value[0];
}
