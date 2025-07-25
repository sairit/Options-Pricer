#include <memory>
#include "Payoff.h"

#ifndef OPTION_H
#define OPTION_H

class Option {
    private:
        double maturity;
        std::shared_ptr<Payoff> payoff;

    public:
        Option(double maturity, std::shared_ptr<Payoff> payoff);

        double get_maturity() const; 
        std::shared_ptr<Payoff> get_payoff() const; 

        virtual ~Option();
};


#endif // OPTION_H