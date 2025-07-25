#include <memory>
#include "Payoff.h"

#ifndef OPTION_H
#define OPTION_H

// General class: Option
class Option {
    private:
        double maturity; // Time to expiration in years
        std::shared_ptr<Payoff> payoff; // Time to expiration in years

    public:
        // Constructor: takes maturity and Payoff pointer
        Option(double maturity, std::shared_ptr<Payoff> payoff);

        // Virtual deconstructor
        virtual ~Option();

        // Getter for maturity
        double get_maturity() const; 

        // Getter for payoff
        std::shared_ptr<Payoff> get_payoff() const; 
};

#endif // OPTION_H