#ifndef BINOMIALTREEENGINE_H
#define BINOMIALTREEENGINE_H

#include "Option.h"
#include <cmath>

class BinomialTreeEngine {
    private:
        double spot;
        double rate;
        double volatility;
        int steps;

    public:
        BinomialTreeEngine(double spot, double rate, double volatility, int steps);

        double price(const Option& option) const;

};

#endif // BINOMIALTREEENGINE_H