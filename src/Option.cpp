#include "Option.h"
#include "Payoff.h"
#include <iostream>
#include <memory>

Option::~Option(){}

Option::Option(double maturity, std::shared_ptr<Payoff> payoff) : maturity(maturity), payoff(payoff) {
    std::cout << "Option created with maturity: " << maturity << std::endl;
}

double Option::get_maturity() const {
    return maturity;
}


std::shared_ptr<Payoff> Option::get_payoff() const {
    return payoff;
}