#include "Option.h"
#include "Payoff.h"
#include <iostream>
#include <memory>

// Option methods implementation
Option::~Option(){}

Option::Option(double maturity, std::shared_ptr<Payoff> payoff) : maturity(maturity), payoff(payoff) {
    std::cout << "Option created with time to expiration: " << maturity << " years" << std::endl;
}

double Option::get_maturity() const {
    return maturity;
}

std::shared_ptr<Payoff> Option::get_payoff() const {
    return payoff;
}