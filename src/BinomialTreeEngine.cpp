#include "BinomialTreeEngine.h"
#include <iostream>
#include <cmath>
#include <vector>

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

    // Building terminal node values
    std::vector<double> value;
    for (int i = 0; i < steps + 1; i++){
        double S = spot * pow(u, i) * pow(d, steps - i);
        value.push_back((*option.get_payoff()).evaluate(S));
    }

    // Stepping backward through tree for early exercise check
    for (int i = steps - 1; i >= 0; i--){
        double S = spot * pow(u, i) * pow(d, steps - i);
        double expected = discount * (p * value[i + 1] + (1 - p) * value[i]);
        double early_exercise = (*option.get_payoff()).evaluate(S);
        value[i] = std::max(early_exercise, expected); 
    }
    
    // Returning root as the option price
    return value[0];
}
