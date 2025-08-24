#include "../include/BlackScholesEngine.h"  
#include <iostream>

// Constructor
BlackScholesEngine::BlackScholesEngine(double spot, double rate, double volatility) : spot(spot), rate(rate), volatility(volatility) {
    std::cout << "BlackScholes engine created with: spot =  " << spot << ", rate = " << rate << ", volatility = " << volatility << std::endl;
}

// Returns the probability that a standard normal less than or equal to x 
// Note: Stable for |x| up to ~10
double BlackScholesEngine::norm_cdf(double x) {
    return 0.5 * (1.0 + erf(x / sqrt(2.0)));
}

// Calculates European call price
double BlackScholesEngine::call_price(const Option& option) const {
    double T = option.get_maturity();
    double strike = (option.get_payoff())->get_strike();  

    // Special Case 1: If call is expired.
    if (T == 0) {
        return std::max(spot - strike, 0.0);
    }

    // Special Case 2: Checking cutoff for degeneracy.
    if (volatility * sqrt(T) <= TINY_EPSILON) {
        double F = spot * exp(rate * T);
        double discount = exp(-rate * T);
        return discount * std::max(F - strike, 0.0);
    }
    
    double d1 = (std::log(spot / strike) + (rate + 0.5 * volatility * volatility) * T) / (volatility * sqrt(T));
    double d2 = d1 - volatility * sqrt(T); 
    
    double call = spot * norm_cdf(d1) - strike * exp(-rate * T) * norm_cdf(d2);
    return call;
}

// Calculates European call price
double BlackScholesEngine::put_price(const Option& option) const {
    double T = option.get_maturity(); 
    double strike = (option.get_payoff())->get_strike(); 
    
    // Special Case 1: If put is expired.
    if (T == 0) {
        return std::max(strike - spot, 0.0);
    }

    // Special Case 2: Checking cutoff for degeneracy.
    if (volatility * sqrt(T) <= TINY_EPSILON) {
        double F = spot * exp(rate * T);
        double discount = exp(-rate * T);
        return discount * std::max(strike - F, 0.0);
    }
    
    double d1 = (std::log(spot / strike) + (rate + 0.5 * volatility * volatility) * T) / (volatility * sqrt(T));
    double d2 = d1 - volatility * sqrt(T); 
    
    double put = strike * exp(-rate * T) * norm_cdf(-d2) - spot * norm_cdf(-d1);
    return put; 
}

