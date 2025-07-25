#include "Payoff.h"
#include <iostream>
#include <algorithm>

// Payoff (base class) methods implementation
Payoff::~Payoff(){}

// CallPayoff methods implementation
CallPayoff::CallPayoff(double strikePrice) : strikePrice(strikePrice){
    std::cout << "Call payoff created with strike price: $" << strikePrice << std::endl; 
}

double CallPayoff::evaluate(double spotPrice) const {
    double evaluation = std::max(spotPrice - strikePrice, 0.0);
    return evaluation;
}

// PutPayof methods implementation
PutPayoff::PutPayoff(double strikePrice) : strikePrice(strikePrice){
    std::cout << "Put payoff created with strike price: $" << strikePrice << std::endl; 
}

double PutPayoff::evaluate(double spotPrice) const {
    double evaluation = std::max(strikePrice - spotPrice, 0.0);
    return evaluation;
}