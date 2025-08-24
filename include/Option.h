#ifndef OPTION_H
#define OPTION_H

#include <memory>
#include "Payoff.h"


// General class: Option
class Option {
    private:
        double maturity; // Time to expiration in years
        std::shared_ptr<Payoff> payoff; // Put or Call

    public:
        // Constructor: takes maturity and Payoff pointer
        Option(double maturity, std::shared_ptr<Payoff> payoff);

        // Virtual destructor
        virtual ~Option();

        // Getter for maturity
        double get_maturity() const; 

        // Getter for payoff
        const std::shared_ptr<Payoff> get_payoff() const; 
};

#endif // OPTION_H